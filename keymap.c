#include QMK_KEYBOARD_H
#include "oled.c"
#include "audio.h"

#define RGB_COLOR_RED    RGB(255, 0, 0)
#define RGB_COLOR_GREEN  RGB(0, 255, 0)
#define RGB_COLOR_BLUE   RGB(0, 0, 255)
#define BACKSPACE_SOUND { NOTE_A5, 50 }

enum layers {
  _QWERTY,
  _NUMBERS,
  _SYMBOLS,
  _FUNCTION,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ESC,
                             MO(_FUNCTION), KC_LGUI, KC_SPC,          KC_ENT,  KC_LALT, MO(_NUMBERS)
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3(
    KC_TRNS,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,        KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
    KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_NO,   KC_NO,
    KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_BSLS, KC_TILD, KC_QUOT, KC_DQUO, KC_LCBR, KC_RCBR,
    KC_LT,     KC_GT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_PIPE, KC_COLN, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                             KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO
  ),

  [_FUNCTION] = LAYOUT_split_3x6_3(
    QK_BOOT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       RGB_VAI, RGB_HUI, RGB_SAI, RGB_MOD, RGB_TOG, KC_TRNS,
    EE_CLR,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       RGB_VAD, RGB_HUD, RGB_SAD, RGB_RMOD, ANY(CK_TOGG), KC_TRNS,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS
  ),
};


const rgblight_config_t rgblight_config = {
    .enable = true,
    .rgb_arrangement = RGB_MATRIX_CORNE,
    .hsv = {.h = 160, .s = 255, .v = 128},
};

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("QWERTY"), true);
    } else {
        oled_write_P(PSTR("MIRROR"), true);
    }

    oled_draw_smiley();
}

void keyboard_post_init_user(void) {
    rgblight_enable();
    rgblight_setrgb(0, 0, 0);
    rgblight_set_color_for_key(0, 0, RGB_COLOR_RED);
    rgblight_set_color_for_key(0, 1, RGB_COLOR_GREEN);
    rgblight_set_color_for_key(0, 2, RGB_COLOR_BLUE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_BSPC:
                PLAY_SONG(BACKSPACE_SOUND);
                break;
        }
    }
    return true;
}

void layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
        case 0:
            rgblight_set_color_for_key(0, 0, RGB_COLOR_RED);
            break;
        case 1:
            rgblight_set_color_for_key(0, 0, RGB_COLOR_GREEN);
            break;
        case 2:
            rgblight_set_color_for_key(0, 0, RGB_COLOR_BLUE);
            break;
        default:
            rgblight_disable();
            break;
    }
}
