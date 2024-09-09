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
// for uk kemap KC_NUHS is the # symbol
// ¬ is KC_TILD
// " is KC_AT
// @ is KC_DQUO

const uint16_t PROGMEM commadot_semicolon[]    = {KC_COMM, KC_DOT, COMBO_END};
combo_t key_combos[] = {
    COMBO(commadot_semicolon, KC_SCLN),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WORKMAN] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, KC_SCLN,
        KC_EQL, KC_LCTL, KC_A, LALT_T(KC_S), LCTL_T(KC_H), LGUI_T(KC_T), KC_G,
        KC_Y, RGUI_T(KC_N), RCTL_T(KC_E), LALT_T(KC_O), KC_I, KC_QUOT, KC_LSFT,
        KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH,
        KC_ENT, KC_CAPS, LT(_NUMBERS, KC_TAB), LSFT_T(KC_ENT),
        RSFT_T(KC_SPC), LT(_SYMBOLS, KC_BSPC), KC_DEL),

    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_BSPC, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,
        KC_SCLN, KC_NO, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,
        KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_RALT, KC_SPC, LT(_NUMBERS, KC_ESC), KC_ENT,
        TO(_WORKMAN), MO(_SYMBOLS)),

    [_NUMBERS] = LAYOUT_split_3x6_3(
        KC_F1, KC_F2, KC_F3, KC_F4,
        KC_F5, KC_F6, KC_F7, KC_F8,
        KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_INS, KC_END, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_NO, KC_BSLS, KC_UNDS, KC_EXLM, KC_QUES, KC_PERC, KC_CIRC, KC_COLN,
        KC_EQL, KC_DLR, KC_NO, KC_BSPC, KC_NO, KC_LT, KC_LBRC, KC_LCBR, KC_LPRN,
        KC_MINS, KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_GT, KC_NO, KC_NO,
        KC_NUBS, KC_PIPE, KC_NO, KC_AMPR, KC_SLSH, KC_ASTR, KC_AT, KC_QUOT,
        KC_GRV, KC_EQL, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS),

    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP,                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, 
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, TO(_QWERTY),         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_VOLD, KC_VOLU,             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS,                                        KC_TRNS, KC_TRNS, KC_TRNS),

};

/* status variables */
led_t led_usb_state;

bool isCtrl = false;
bool isAlt = false;
bool isCaps = false;
bool isShft = false;

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  /*if (!is_keyboard_master()) {*/
  /*  return OLED_ROTATION_180; // flips the display 180 degrees if offhand*/
  /*}*/
  return OLED_ROTATION_270;
}

// void oled_render_logo(void);

static void print_status_narrow(void) {
  /* Print current mode */
  oled_set_cursor(0, 1);

  /* Print current layer */
  oled_write("LAYER", false);

  oled_set_cursor(0, 2);

  switch (get_highest_layer(layer_state)) {
  case _WORKMAN:
    oled_write("WORK ", false);
    break;
  case _QWERTY:
    oled_write("QWERT", false);
    break;
  case _NUMBERS:
    oled_write("NUMS ", false);
    break;
  case _SYMBOLS:
    oled_write("SYMB ", false);
    break;
  case _ADJUST:
    oled_write("AJUST", false);
    break;
  default:
    oled_write("Undef", false);
  }
  // mods

  oled_set_cursor(0, 4);
  oled_write("Mods:", false);

  oled_set_cursor(0, 6);
  oled_write(led_usb_state.caps_lock ? "caps+" : "caps-", false);

  oled_set_cursor(0, 7);
  oled_write(isCtrl ? "ctrl+" : "ctrl-", false);

  oled_set_cursor(0, 8);
  oled_write(isAlt ? "alt +" : "alt -", false);

  oled_set_cursor(0, 9);
  oled_write(isShft ? "shft+" : "shft-", false);

  oled_set_cursor(0, 10);
  oled_write(led_usb_state.num_lock ? "num +" : "num -", false);
}

static void print_right_status(void) {


}

bool oled_task_user(void) {
  led_usb_state = host_keyboard_led_state();

  if (is_keyboard_master()) {
    print_status_narrow();
  } else {
    /*oled_render_logo();*/
    print_right_status();
  }
  return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LCTL:
  case KC_RCTL:
  case LCTL_T(KC_H):
  case RCTL_T(KC_E):
    if (record->event.pressed) {
      isCtrl = true;
    } else if (record->tap.count == 0) {
      isCtrl = true;
    } else {
      isCtrl = false;
    }
    break;
  case KC_CAPS:
    if (record->event.pressed) {
      isCaps = true;
    } else if (record->tap.count == 0) {
      isCaps = true;
    } else {
      isCaps = false;
    }
    break;

  case KC_LALT:
  case KC_RALT:
  case LALT_T(KC_S):
  case LALT_T(KC_O):
    if (record->event.pressed) {
      isAlt = true;
    } else if (record->tap.count == 0) {
      isAlt = true;
    } else {
      isAlt = false;
    }
    break;
  case KC_RSFT:
  case KC_LSFT:
  case LSFT_T(KC_ENT):
    if (record->event.pressed) {
      isShft = true;
    } else if (record->tap.count == 0) {
      isShft = true;
    } else {
      isShft = false;
    }
    break;
  default:
    isCtrl = false;
    isAlt = false;
    isCaps = false;
    isShft = false;
    break;
  }
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LALT_T(KC_S):
  case LCTL_T(KC_H):
  case LGUI_T(KC_T):
  case RGUI_T(KC_N):
  case RCTL_T(KC_E):
  case LALT_T(KC_O):
    return TAPPING_TERM + 150;
  default:
    return TAPPING_TERM;
  }
}
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NUMBERS, _SYMBOLS, _ADJUST);
}
