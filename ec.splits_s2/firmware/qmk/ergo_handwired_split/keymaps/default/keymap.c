#include QMK_KEYBOARD_H
#define _BASE 0 
#define _LAYER_1 1 
#define _LAYER_2 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   
    [_BASE] = LAYOUT_ortho_8x5(
        KC_Q,   KC_W,   KC_E,   KC_R,  KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
        KC_A,   KC_S,   KC_D,   KC_F,  KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_M,
        LT(_LAYER_1, KC_ESC),   KC_BSPC,KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_ENT,   KC_RALT,
           KC_LSFT,KC_SPC,KC_LCTL,KC_RCTL,KC_SPC, KC_RSFT
    ),

    [_LAYER_1] =  LAYOUT_ortho_8x5(
        KC_1,   KC_2,   KC_3,   KC_4,  KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
        LT(_LAYER_2, KC_GRV),   KC_NO,   KC_CAPS,   KC_UP,  KC_TAB,   KC_SCLN,   KC_QUOT,   KC_BSLS,   KC_LBRC,   KC_RBRC,
        KC_NO,   KC_LGUI,   KC_LEFT,   KC_DOWN,  KC_RGHT,   KC_COMM,   KC_DOT,   KC_SLSH,   KC_MINS,   KC_EQL,
           KC_LSFT,   KC_SPC, KC_LCTL, KC_RCTL,  KC_SPC,   KC_RSFT
    ),

    [_LAYER_2] =  LAYOUT_ortho_8x5(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_NO,   KC_NO,   KC_PSCR,   KC_SCRL,  KC_PAUS,   KC_INS,   KC_HOME,   KC_PGUP,   KC_F11,   KC_F12,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_DEL,   KC_END,   KC_PGDN,   KC_NO,   KC_LALT,
                           KC_LSFT,   KC_SPC, KC_LCTL, KC_RCTL,  KC_SPC,   KC_RSFT
    ),
};
