/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _WORKMAN 0
#define _QWERTY 1
#define _NUMBERS 2
#define _SYMBOLS 3
#define _ADJUST 4

// for uk kemap KC_HASH is the £ symbol
// for uk kemap KC_BSLS is the # symbol
// for uk kemap KC_PIPE is the ~ symbol
// ¬ is KC_TILD
// " is KC_AT
// @ is KC_DQUO

// clang-format off
// Tap Dance declarations
enum {
    TD_1_ALT1,
    TD_2_ALT2,
    TD_3_ALT3,
    TD_4_ALT4,
    TD_5_ALT5,
    TD_6_ALT6,
    TD_7_ALT7,
    TD_8_ALT8,
    TD_9_ALT9,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_1_ALT1] = ACTION_TAP_DANCE_DOUBLE(KC_1, LALT(KC_1)),
    [TD_2_ALT2] = ACTION_TAP_DANCE_DOUBLE(KC_2, LALT(KC_2)),
    [TD_3_ALT3] = ACTION_TAP_DANCE_DOUBLE(KC_3, LALT(KC_3)),
    [TD_4_ALT4] = ACTION_TAP_DANCE_DOUBLE(KC_4, LALT(KC_4)),
    [TD_5_ALT5] = ACTION_TAP_DANCE_DOUBLE(KC_5, LALT(KC_5)),
    [TD_6_ALT6] = ACTION_TAP_DANCE_DOUBLE(KC_6, LALT(KC_6)),
    [TD_7_ALT7] = ACTION_TAP_DANCE_DOUBLE(KC_7, LALT(KC_7)),
    [TD_8_ALT8] = ACTION_TAP_DANCE_DOUBLE(KC_8, LALT(KC_8)),
    [TD_9_ALT9] = ACTION_TAP_DANCE_DOUBLE(KC_9, LALT(KC_9)),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = LAYOUT_split_3x6_3(
        KC_PLUS, KC_Q, KC_D, KC_R, KC_W, KC_B,                                                                               KC_J, KC_F, KC_U, KC_P, KC_SCLN, KC_UNDS, 
        KC_ESC, LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_H), LGUI_T(KC_T), KC_G,                                                KC_Y, RGUI_T(KC_N), RCTL_T(KC_E), LALT_T(KC_O), RSFT_T(KC_I), KC_EQL, 
        KC_MINS, KC_Z, KC_X, KC_M, KC_C, KC_V,                                                                               KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, KC_NUBS, 
        KC_CAPS, LT(_NUMBERS, KC_TAB), LSFT_T(KC_ENT),                                                                       RSFT_T(KC_SPC), LT(_SYMBOLS, KC_BSPC), KC_DEL
    ),

    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_T, KC_TAB,  KC_Q, KC_W, KC_E, KC_R,                                                                               KC_Y, KC_U, KC_I, KC_O, KC_P,KC_BSPC, 
        KC_G, KC_LCTL, KC_A, KC_S, KC_D, KC_F,                                                                               KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NO, 
        KC_B, KC_LSFT, KC_Z, KC_X, KC_C, KC_V,                                                                               KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
        KC_LALT, LT(_NUMBERS, KC_ESC), KC_SPC,                                                                               KC_ENT, LT(_SYMBOLS, KC_HOME), KC_INS
    ),

    [_NUMBERS] = LAYOUT_split_3x6_3(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                                                            KC_F7, KC_F8,KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_NO, TD(TD_1_ALT1), TD(TD_2_ALT2), TD(TD_3_ALT3), TD(TD_4_ALT4), TD(TD_5_ALT5),                                    TD(TD_6_ALT6), TD(TD_7_ALT7), TD(TD_8_ALT8), TD(TD_9_ALT9), KC_0, KC_NO, 
        KC_HOME, KC_PGUP, KC_PGDN, KC_INS, KC_LALT, KC_END,                                                                  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_INS, KC_END,
                       KC_TRNS, KC_TRNS, KC_TRNS,                                                                            KC_NO, KC_TRNS, KC_HOME
    ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_NO, KC_BSLS, KC_UNDS, KC_EXLM, KC_QUES, KC_PERC,                                                                  KC_CIRC, KC_COLN, KC_EQL, KC_DLR, KC_HASH, KC_BSPC, 
        KC_NO, KC_LT, KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS,                                                                    KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT, KC_NO, 
        KC_NUHS, KC_NUBS, KC_PIPE, KC_NO, KC_AMPR, KC_SLSH,                                                                  KC_ASTR, KC_AT, KC_QUOT, KC_GRV, KC_EQL, KC_TILD, 
                               KC_TRNS, KC_TRNS, KC_TRNS,                                                                    KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ADJUST] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP,                                                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, TO(_QWERTY),                                                            TO(_WORKMAN), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_VOLD, KC_VOLU,                                                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS,                                                                                           KC_TRNS, KC_TRNS, KC_TRNS),
};

/* status variables */
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LALT_T(KC_S):
  case LCTL_T(KC_H):
  case LGUI_T(KC_T):
  case RGUI_T(KC_N):
  case RCTL_T(KC_E):
  case LALT_T(KC_O):
    return TAPPING_TERM + 100;
  case RSFT_T(KC_I):
  case LSFT_T(KC_A):
    return TAPPING_TERM + 200;
  default:
    return TAPPING_TERM;
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUMBERS, _SYMBOLS, _ADJUST);
}
