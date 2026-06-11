/* Copyright (C) 2023 jonylee@hfd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum __layers {
    WIN_B,
    WIN_FN,
};

enum __custom_keycodes {
  RGB_SLD = SAFE_RANGE,
  KVM_1,
  KVM_2
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_all( /* Base Layer */
        KC_ESC,  KVM_1,   KVM_2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_PSCR,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS,          KC_END,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_NUHS,  KC_ENT,           KC_PGUP,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RGUI, MO(WIN_FN),KC_RALT,        KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_FN] = LAYOUT_all( /* Function Layer */
        _______, KC_F1,   KC_F2,   KC_WSCH, KC_WHOM, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, _______, KC_DEL,            RM_NEXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_SPDU, _______,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  _______, _______, _______, _______, RM_NEXT,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_TOGG, _______, _______, RM_NEXT, RM_HUEU,           _______,
        _______, _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,  RM_VALU, _______,
        _______, GU_TOGG, _______,                   _______,                            _______, _______, _______,          RM_SATD,  RM_VALD, RM_SATU)

};

// clang-format off
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [WIN_B] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_FN] = { ENCODER_CCW_CW(RM_VALU, RM_VALD) }
};
#endif

// clang-format on
// Switch to KVM input 1
void ctrl_ctrl_1(void) {
    keymap_config.nkro = false;
    tap_code(KC_SCRL);
    tap_code(KC_SCRL);
    tap_code(KC_1);
    keymap_config.nkro = true;
}

// Switch to KVM input 2
void ctrl_ctrl_2(void) {
    keymap_config.nkro = false;
    tap_code(KC_SCRL);
    tap_code(KC_SCRL);
    tap_code(KC_2);
    keymap_config.nkro = true;
}

// Record KVM switching
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KVM_1:
            if (record->event.pressed) {
                ctrl_ctrl_1();
            }
            return false;

        case KVM_2:
            if (record->event.pressed) {
                ctrl_ctrl_2();
            }
            return false;
    }
    return true;
}
