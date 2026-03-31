/**
 * @file ui_events.c
 * @brief SquareLine Studio UI 이벤트 콜백 구현 파일
 *
 * SquareLine Studio 가 자동 생성한 ui_events.h 의 함수 원형에 대한
 * 실제 동작을 사용자가 직접 구현하는 파일이다.
 *
 * ■ 포함된 콜백 함수
 *   - ledSwitchCB()   : UI 스위치(ui_LedSwitch) ON/OFF → GPIO16 LED 제어
 *   - motorSpeedCB()  : UI 슬라이더(ui_SpeedBar) 값 변경 → 모터 속도 출력
 *
 * ■ 이벤트 등록 위치
 *   - ledSwitchCB  : main.cpp setup() 에서 lv_obj_add_event_cb() 로 수동 등록
 *   - motorSpeedCB : ui_MainScreen.c 의 ui_event_SpeedBar() 가 자동으로 호출
 *
 * ■ 이 파일은 순수 C(.c) 로 컴파일되므로 Arduino C++ API(digitalWrite 등)를
 *   직접 사용할 수 없다. GPIO 제어는 ESP-IDF C API(driver/gpio.h) 를 사용한다.
 */

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 헤더 인클루드
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
#include "ui.h"             // LVGL + SquareLine 전체 UI 헤더 (위젯 포인터, 폰트, 이벤트 선언)
#include "driver/gpio.h"    // ESP-IDF GPIO C API: gpio_set_level() 사용을 위해 포함
#include <stdio.h>          // printf() 사용을 위해 포함 (ESP32 Arduino에서 UART로 출력됨)

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 상수 정의
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */
/**
 * LED 가 연결된 GPIO 핀 번호
 *
 * main.cpp 의 pinMode(LED_PIN, OUTPUT) 으로 이미 출력 방향이 설정되어 있으므로
 * 이 파일에서는 gpio_set_level() 로 HIGH/LOW 만 설정하면 된다.
 *
 * @warning main.cpp 의 #define LED_PIN 16 과 반드시 동일해야 한다.
 *          불일치 시 엉뚱한 핀이 제어된다.
 */
#define LED_PIN 16

/* ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * 콜백 함수 구현
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ */

/**
 * @brief LED 스위치 토글 콜백
 *
 * ui_LedSwitch(LVGL lv_switch 위젯)의 상태가 변경될 때마다 호출된다.
 * 스위치가 ON 이면 GPIO16 을 HIGH 로, OFF 이면 LOW 로 설정해 LED 를 제어한다.
 *
 * ■ 등록 위치
 *   main.cpp setup() 에서 수동 등록:
 *     lv_obj_add_event_cb(ui_LedSwitch, ledSwitchCB, LV_EVENT_VALUE_CHANGED, NULL);
 *
 * ■ 호출 흐름
 *   사용자가 스위치 터치
 *     → LVGL 이 LV_EVENT_VALUE_CHANGED 발생
 *       → ledSwitchCB() 호출
 *         → lv_obj_has_state() 로 현재 ON/OFF 확인
 *           → gpio_set_level() 로 LED 제어
 *
 * @param e  LVGL 이벤트 객체 포인터
 *           - lv_event_get_target(e)  : 이벤트를 발생시킨 위젯(= ui_LedSwitch) 반환
 *           - lv_event_get_code(e)    : 이벤트 종류 반환 (여기서는 LV_EVENT_VALUE_CHANGED)
 *           - lv_event_get_user_data(e): 등록 시 전달한 사용자 데이터 반환 (여기서는 NULL)
 */
void ledSwitchCB(lv_event_t * e)
{
    /*
     * lv_event_get_target(e)
     *   이벤트를 발생시킨 LVGL 객체(lv_obj_t *)를 반환한다.
     *   여기서는 ui_LedSwitch 스위치 위젯과 동일한 포인터다.
     */
    lv_obj_t * sw = lv_event_get_target(e);

    /*
     * lv_obj_has_state(sw, LV_STATE_CHECKED)
     *   위젯이 LV_STATE_CHECKED 상태인지 확인한다.
     *   lv_switch 는 ON 일 때 LV_STATE_CHECKED 플래그가 설정된다.
     *   반환값: true = 스위치 ON, false = 스위치 OFF
     */
    bool isOn = lv_obj_has_state(sw, LV_STATE_CHECKED);

    /*
     * gpio_set_level(gpio_num, level)   ← ESP-IDF C API
     *   지정한 GPIO 핀의 출력 레벨을 설정한다.
     *   level: 1 = HIGH(3.3 V) → LED 켜짐
     *          0 = LOW (0 V)   → LED 꺼짐
     *
     *   ※ Arduino 의 digitalWrite() 와 동일한 역할이지만
     *     C 파일에서 사용 가능한 ESP-IDF 함수다.
     */
    gpio_set_level(LED_PIN, isOn ? 1 : 0);

    // 디버그: 시리얼 모니터에 현재 LED 상태 출력
    printf("[LED] %s\n", isOn ? "ON" : "OFF");
}

/**
 * @brief 모터 속도 슬라이더 이벤트 콜백
 *
 * ui_SpeedBar(LVGL lv_slider 위젯)의 값이 변경될 때마다 호출된다.
 * 슬라이더 값(0 ~ 100)을 읽어 모터 속도로 사용한다.
 *
 * ■ 등록 위치
 *   ui_MainScreen.c 의 ui_event_SpeedBar() 가 자동으로 이 함수를 호출한다.
 *     void ui_event_SpeedBar(lv_event_t * e) {
 *         if (event_code == LV_EVENT_VALUE_CHANGED) motorSpeedCB(e);
 *     }
 *
 * ■ 호출 흐름
 *   사용자가 슬라이더 드래그
 *     → LVGL 이 LV_EVENT_VALUE_CHANGED 발생
 *       → ui_event_SpeedBar() → motorSpeedCB() 호출
 *         → lv_slider_get_value() 로 현재 슬라이더 값 읽기
 *           → 모터 제어 (현재는 시리얼 출력만 구현)
 *
 * ■ PWM 모터 제어 확장 방법
 *   ESP-IDF ledc API 를 사용해 PWM 신호를 출력할 수 있다:
 *
 *     #include "driver/ledc.h"
 *     #define MOTOR_PIN    17           // 모터 드라이버 PWM 입력 핀
 *     #define MOTOR_CH     LEDC_CHANNEL_0
 *
 *     // setup() 에서 채널 초기화:
 *     ledc_timer_config_t timer = {
 *         .speed_mode      = LEDC_LOW_SPEED_MODE,
 *         .duty_resolution = LEDC_TIMER_8_BIT,   // 0 ~ 255
 *         .timer_num       = LEDC_TIMER_0,
 *         .freq_hz         = 5000,
 *         .clk_cfg         = LEDC_AUTO_CLK
 *     };
 *     ledc_timer_config(&timer);
 *     ledc_channel_config_t ch = {
 *         .gpio_num  = MOTOR_PIN,
 *         .speed_mode= LEDC_LOW_SPEED_MODE,
 *         .channel   = MOTOR_CH,
 *         .timer_sel = LEDC_TIMER_0,
 *         .duty      = 0,
 *         .hpoint    = 0
 *     };
 *     ledc_channel_config(&ch);
 *
 *     // motorSpeedCB() 안에서:
 *     uint32_t duty = (uint32_t)(value * 255 / 100);
 *     ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_CH, duty);
 *     ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_CH);
 *
 * @param e  LVGL 이벤트 객체 포인터
 */
void motorSpeedCB(lv_event_t * e)
{
    /*
     * lv_event_get_target(e)
     *   이벤트를 발생시킨 위젯 포인터를 반환한다.
     *   여기서는 ui_SpeedBar(lv_slider) 위젯과 동일하다.
     */
    lv_obj_t * slider = lv_event_get_target(e);

    /*
     * lv_slider_get_value(slider)
     *   슬라이더의 현재 값을 int32_t 로 반환한다.
     *   SquareLine 에서 별도 범위를 설정하지 않았으므로 기본값 0 ~ 100 이다.
     *   범위를 바꾸려면 ui_MainScreen.c 에서:
     *     lv_slider_set_range(ui_SpeedBar, 최솟값, 최댓값);
     */
    int value = (int)lv_slider_get_value(slider);   // 0 ~ 100 (%)

    // 디버그: 현재 슬라이더 값을 시리얼 모니터에 출력
    // %% : printf 에서 '%' 리터럴을 출력하려면 두 번 써야 한다
    printf("[MOTOR] Speed=%d%%\n", value);

    /*
     * ── 실제 모터 PWM 제어가 필요할 때 여기에 추가 ──────────
     * uint32_t duty = (uint32_t)(value * 255 / 100);   // 0~100 → 0~255 변환
     * ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_CH, duty);
     * ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_CH);
     * ─────────────────────────────────────────────────────── */
}
