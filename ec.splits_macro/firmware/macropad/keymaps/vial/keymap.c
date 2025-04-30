#include <wctype.h>
#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#include "oled_driver.h"
#include "dvd/dvd.c"
#endif
#define _BASE 0 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
    [_BASE] = LAYOUT_ortho_4x4(
        KC_NO,   KC_MPLY,   KC_MSTP,   KC_MPRV, KC_MNXT,
        KC_F13,   KC_F14,   KC_NO,     KC_NO,   KC_NO,
        KC_NO,   KC_NO,     KC_NO,     KC_NO,   KC_NO,
        KC_NO,   KC_NO,     KC_NO,     KC_NO,   KC_NO
    )
};
#if defined(ENCODER_MAP_ENABLE) 
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
     [0] = { ENCODER_CCW_CW(KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN)  }
};
#endif

#ifdef OLED_ENABLE



bool oled_task_user(void) {
        render_dvd();
        return false;
    }

#endif
