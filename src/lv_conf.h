#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 1        // ← 이 줄 추가!

#define LV_HOR_RES_MAX 240
#define LV_VER_RES_MAX 320
#define LV_MEM_SIZE (48U * 1024U)

#define LV_TICK_CUSTOM 1
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())

#define LV_FONT_MONTSERRAT_14 1
#define LV_USE_LOG 1

#endif
