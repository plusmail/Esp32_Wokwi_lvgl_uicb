/**
 * @file main.cpp
 * @brief ESP32 + TFT_eSPI + FT6206 터치 + LVGL 8 + SquareLine Studio UI 통합 메인 파일
 *
 * ■ 동작 흐름
 *   1. TFT 디스플레이(ILI9341, 240×320) 와 FT6206 정전식 터치 컨트롤러를 초기화한다.
 *   2. LVGL 그래픽 라이브러리를 초기화하고 디스플레이·터치 드라이버를 등록한다.
 *   3. SquareLine Studio가 자동 생성한 ui_init() 을 호출해 화면을 구성한다.
 *   4. loop() 에서 lv_timer_handler() 를 주기적으로 호출해 LVGL 이벤트를 처리한다.
 *
 * ■ 하드웨어 연결 (diagram.json 기준)
 *   - SPI  : MOSI=23, SCK=18, MISO=19, CS=5, D/C=15
 *   - I2C  : SDA=21, SCL=22  (FT6206 터치 컨트롤러)
 *   - LED  : GPIO 16
 *   - 화면 크기: 240 × 320 px
 */

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 헤더 인클루드
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
#include <Arduino.h>        // pinMode, digitalWrite, delay, Serial 등 기본 Arduino API
#include <SPI.h>            // SPI 버스 초기화 (TFT 디스플레이가 SPI를 사용)
#include <Wire.h>           // I2C 버스 초기화 (FT6206 터치 컨트롤러가 I2C를 사용)
#include <TFT_eSPI.h>       // Bodmer 의 TFT 드라이버 라이브러리 — 픽셀 전송 담당
#include <Adafruit_FT6206.h>// FT6206 정전식 터치 컨트롤러 드라이버
#include <lvgl.h>           // LVGL 8 그래픽 라이브러리 (위젯·이벤트·렌더링)
#include "ui/ui.h"          // SquareLine Studio 자동 생성 UI 헤더
                            //   → ui_init(), ui_LedSwitch, ui_SpeedBar 등 선언 포함

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 전역 객체
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/**
 * TFT_eSPI 디스플레이 객체
 * - 핀 설정은 라이브러리의 User_Setup.h 또는 platformio.ini build_flags 에서 지정
 * - 주요 메서드: init(), setAddrWindow(), pushColors(), startWrite(), endWrite()
 */
TFT_eSPI tft = TFT_eSPI();

/**
 * FT6206 터치 컨트롤러 객체
 * - I2C 주소 0x38 로 통신 (Wire 버스 사용)
 * - 주요 메서드: begin(), touched(), getPoint()
 */
Adafruit_FT6206 ts;

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 상수 정의
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/**
 * LED 가 연결된 GPIO 핀 번호
 * ui_events.c 의 ledSwitchCB() 에서도 동일한 값(16)을 사용한다.
 * 두 파일을 동기화하려면 공용 헤더로 분리하는 것을 권장한다.
 */
#define LED_PIN 16

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * LVGL 렌더링 버퍼
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/**
 * lv_disp_draw_buf_t : LVGL 이 내부적으로 픽셀을 렌더링할 때 사용하는 버퍼 메타데이터.
 * 실제 픽셀 데이터는 아래 buf[] 배열에 저장된다.
 */
static lv_disp_draw_buf_t draw_buf;

/**
 * 픽셀 컬러 버퍼 (240 × 10 = 2 400 픽셀)
 *
 * - lv_color_t : lv_conf.h 의 LV_COLOR_DEPTH(=16) 에 따라 RGB565 형식의 2바이트 구조체
 * - 크기 선택 기준: 화면 너비(240) × N 줄(10) — 클수록 렌더링 효율이 높아지지만 RAM 을 더 차지함
 * - 이 버퍼는 LVGL 이 한 번에 최대 10줄씩 디스플레이로 전송하는 DMA 전송 단위가 된다.
 */
static lv_color_t buf[240 * 10];

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * LVGL 콜백 함수 구현
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/**
 * @brief LVGL 디스플레이 플러시 콜백 (필수)
 *
 * LVGL 이 화면 일부를 다시 그려야 할 때 자동으로 호출된다.
 * 렌더링된 픽셀 데이터를 TFT_eSPI 를 통해 실제 디스플레이로 전송하는 역할을 한다.
 *
 * 호출 흐름:
 *   LVGL 내부 렌더러 → my_disp_flush() → TFT_eSPI::pushColors() → ILI9341 하드웨어
 *
 * @param disp     LVGL 디스플레이 드라이버 포인터 (등록 시 설정한 disp_drv 와 동일)
 * @param area     이번 플러시에서 업데이트할 화면 영역 (x1,y1 ~ x2,y2 좌표)
 * @param color_p  해당 영역의 픽셀 컬러 배열 포인터 (buf[] 와 동일한 메모리)
 *
 * @note 함수 끝에서 반드시 lv_disp_flush_ready() 를 호출해야 한다.
 *       호출하지 않으면 LVGL 이 다음 프레임을 그리지 않고 무한 대기한다.
 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    // 업데이트 영역의 픽셀 수 계산
    uint32_t w = area->x2 - area->x1 + 1;  // 가로 픽셀 수
    uint32_t h = area->y2 - area->y1 + 1;  // 세로 픽셀 수

    tft.startWrite();   // SPI CS 를 LOW 로 내려 전송 시작 (다른 SPI 장치 잠금)

    // ILI9341 에 쓸 화면 영역을 지정한다 (시작점 x1,y1 / 크기 w×h)
    tft.setAddrWindow(area->x1, area->y1, w, h);

    // color_p->full : lv_color_t 공용체에서 16비트 RGB565 값에 접근하는 멤버
    // w * h         : 전송할 총 픽셀 개수
    // true          : 빅·리틀 엔디언 스왑 여부 (lv_conf.h LV_COLOR_16_SWAP=1 이면 필요)
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);

    tft.endWrite();     // SPI CS 를 HIGH 로 올려 전송 완료

    // LVGL 에게 "이 플러시가 끝났다" 고 알린다 → 다음 렌더링을 시작할 수 있게 됨
    lv_disp_flush_ready(disp);
}

/**
 * @brief LVGL 터치 입력 읽기 콜백 (필수)
 *
 * LVGL 이 매 틱(tick)마다 자동으로 호출해 터치 상태를 가져간다.
 * FT6206 라이브러리로 터치 좌표를 읽은 뒤 data 구조체를 채워 반환한다.
 *
 * 호출 흐름:
 *   lv_timer_handler() → LVGL indev 처리 → my_touch_read() → FT6206::getPoint()
 *
 * @param indev_drv 등록된 입력 장치 드라이버 포인터 (현재 함수에서는 사용하지 않음)
 * @param data      LVGL 에 전달할 터치 데이터 구조체 포인터
 *                    data->point.x  : 터치 X 좌표 (0 ~ 239)
 *                    data->point.y  : 터치 Y 좌표 (0 ~ 319)
 *                    data->state    : LV_INDEV_STATE_PRESSED / LV_INDEV_STATE_RELEASED
 *
 * @note FT6206 원시 좌표는 화면과 반전된 방향으로 나오므로
 *       (239 - p.x), (319 - p.y) 로 변환한다.
 */
void my_touch_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (ts.touched()) {
        // FT6206 에서 첫 번째 터치 포인트를 읽는다 (멀티 터치 미사용)
        TS_Point p = ts.getPoint();

        // 하드웨어 마운트 방향에 따른 좌표 반전 보정
        data->point.x = 239 - p.x;
        data->point.y = 319 - p.y;
        data->state   = LV_INDEV_STATE_PRESSED;    // 손가락이 화면에 닿은 상태
    } else {
        data->state = LV_INDEV_STATE_RELEASED;      // 손가락이 떨어진 상태
        // 릴리즈 시에는 좌표를 갱신하지 않아도 된다 (LVGL 이 마지막 좌표를 유지)
    }
}

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * Arduino 진입점
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/**
 * @brief 초기화 함수 — 전원 인가 또는 리셋 직후 1회 실행된다.
 *
 * 실행 순서:
 *   1. GPIO 방향 설정
 *   2. 시리얼 / I2C / SPI 버스 초기화
 *   3. TFT 디스플레이 초기화
 *   4. FT6206 터치 컨트롤러 초기화
 *   5. LVGL 초기화 + 디스플레이 드라이버 등록
 *   6. LVGL 터치 입력(indev) 드라이버 등록
 *   7. SquareLine UI 초기화 (ui_init)
 *   8. LED 스위치 이벤트 콜백 추가 등록
 */
void setup()
{
    /* ── 1. GPIO 초기 상태 설정 ───────────────────────────────── */
    // TFT_CS : TFT_eSPI 라이브러리가 SPI 통신 시작 전에 직접 제어하지만,
    //          초기에 HIGH(비활성)로 두어야 다른 SPI 장치와 충돌하지 않는다.
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);

    // LED_PIN : 출력 모드로 설정하고, 시작 시 꺼진 상태(LOW)로 초기화한다.
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    /* ── 2. 시리얼 / 버스 초기화 ─────────────────────────────── */
    Serial.begin(115200);   // 디버그 출력용 UART, 속도는 monitor_speed 와 맞춰야 한다
    delay(200);             // 시리얼 안정화 대기
    Serial.println("\n===== ESP32 LVGL UI =====");

    Wire.begin();   // I2C 버스 시작 (기본 핀: SDA=21, SCL=22)
    SPI.begin();    // SPI 버스 시작 (기본 핀: MOSI=23, MISO=19, SCK=18)

    /* ── 3. TFT 디스플레이 초기화 ────────────────────────────── */
    tft.init();             // ILI9341 초기화 시퀀스 전송 (리셋·클럭 설정 포함)
    tft.setRotation(0);     // 화면 방향: 0=세로(portrait) 기본, 1/2/3=90° 단위 회전
    Serial.println("TFT 초기화 완료");

    /* ── 4. FT6206 터치 컨트롤러 초기화 ─────────────────────── */
    // begin(threshold): 터치 감도 임계값 (40 = 기본값, 낮을수록 민감)
    // 반환값 false → I2C 에서 FT6206 을 찾지 못한 경우 (배선 확인 필요)
    if (!ts.begin(40)) {
        Serial.println("FT6206 초기화 실패 — 터치 없이 진행");
    } else {
        Serial.println("FT6206 초기화 완료");
    }

    /* ── 5. LVGL 초기화 및 디스플레이 드라이버 등록 ─────────── */

    // LVGL 내부 상태(힙, 타이머, 스타일 등)를 초기화한다.
    // 반드시 다른 lv_* 함수보다 먼저 호출해야 한다.
    lv_init();

    // 렌더링 버퍼를 LVGL 에 등록한다.
    //   &draw_buf : 버퍼 메타데이터 구조체 포인터
    //   buf       : 1차 픽셀 버퍼 (필수)
    //   NULL      : 2차 버퍼 (DMA 이중 버퍼링 시 사용, 현재 미사용)
    //   240 * 10  : 버퍼가 담을 수 있는 최대 픽셀 수
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, 240 * 10);

    // 디스플레이 드라이버 구조체를 설정하고 LVGL 에 등록한다.
    // static 선언: setup() 종료 후에도 메모리가 유지되어야 하므로 필수
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);           // 구조체 기본값 초기화
    disp_drv.hor_res  = 240;               // 화면 가로 해상도 (픽셀)
    disp_drv.ver_res  = 320;               // 화면 세로 해상도 (픽셀)
    disp_drv.flush_cb = my_disp_flush;     // 픽셀 전송 콜백 함수 연결
    disp_drv.draw_buf = &draw_buf;         // 위에서 초기화한 렌더링 버퍼 연결
    lv_disp_drv_register(&disp_drv);       // LVGL 에 드라이버 등록 완료

    /* ── 6. LVGL 터치 입력(indev) 드라이버 등록 ─────────────── */
    // static 선언 이유: disp_drv 와 동일 — setup() 종료 후에도 유효해야 함
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);                  // 구조체 기본값 초기화
    indev_drv.type    = LV_INDEV_TYPE_POINTER;      // 입력 장치 종류: 포인터(터치/마우스)
    indev_drv.read_cb = my_touch_read;              // 좌표 읽기 콜백 함수 연결
    lv_indev_drv_register(&indev_drv);              // LVGL 에 입력 드라이버 등록 완료

    /* ── 7. SquareLine Studio UI 초기화 ──────────────────────── */
    // ui/ui.c 에 정의된 함수로 MainScreen 을 생성하고 활성 화면으로 설정한다.
    // 내부적으로 ui_MainScreen_screen_init() 를 호출해 모든 위젯을 생성한다.
    ui_init();

    /* ── 8. LED 스위치 이벤트 콜백 추가 등록 ────────────────── */
    // SquareLine 은 ui_SpeedBar 에만 이벤트를 자동 연결하고
    // ui_LedSwitch 이벤트는 생략했으므로 여기서 수동으로 등록한다.
    //
    // lv_obj_add_event_cb(대상 객체, 콜백 함수, 이벤트 종류, 사용자 데이터)
    //   ui_LedSwitch        : screens/ui_MainScreen.h 에 extern 선언된 LVGL 스위치 위젯
    //   ledSwitchCB         : ui_events.c 에 구현된 콜백 (스위치 ON/OFF → GPIO 제어)
    //   LV_EVENT_VALUE_CHANGED : 스위치 상태가 바뀔 때만 콜백을 호출
    //   NULL                : 사용자 데이터 없음 (콜백 안에서 lv_event_get_user_data() 로 접근)
    // LedSwitch 이벤트는 ui_MainScreen.c 의 screen_init() 에서 자동 등록됨

    Serial.println("UI 초기화 완료!");
}

/**
 * @brief 메인 루프 — setup() 완료 후 무한 반복 실행된다.
 *
 * lv_timer_handler() 는 LVGL 의 심장부로, 아래 작업을 순서대로 처리한다.
 *   - 입력 장치(터치) 상태 갱신
 *   - 위젯 이벤트 디스패치 (클릭·드래그·값 변경 등)
 *   - 더티(dirty) 영역 계산 및 my_disp_flush() 호출
 *   - 내부 애니메이션·타이머 업데이트
 *
 * delay(5) : 약 5 ms 대기 → 최대 ~200 fps 로 실행된다.
 *            지연이 너무 짧으면 CPU 를 낭비하고, 너무 길면 터치 응답이 느려진다.
 *            일반적으로 5 ~ 10 ms 가 적당하다.
 */
void loop()
{
    lv_timer_handler();     // LVGL 이벤트·렌더링 처리 (이 한 줄이 모든 UI 동작을 구동)
    delay(5);               // CPU 과점유 방지 및 LVGL 타이밍 안정화
}
