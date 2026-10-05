// Copyright 2022 Viatly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 *         ,-----------------------------------------.                    ,-----------------------------------------.
 *         | Tab  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 *         |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *         | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '   |
 * ,-------|------+------+------+------+------+------|                    |------+------+------+------+------+------|-------.
 * | Caps  |LCTRL |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  "   | Del   |
 * `-------|------+------+------+------+------+------|-------.    ,-------|------+------+------+------+------+------|-------'
 *         |LShift|   Z  |   X  |   C  |   V  |   B  | Home  |    | PgDn  |   N  |   M  |   ,  |   .  |   /  |RShift|
 *         `-----------------------------------------| End   |    | PgUp  |-----------------------------------------'
 *                 | Play | LAlt | LGUI |LOWER | Enter|-------'    `-------| Space| BSPC |RAISE | RAlt | Mute |
 *                 `----------------------------------'                    `----------------------------------'
 */
 [_QWERTY] = LAYOUT(
           KC_TAB,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
           KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
  KC_CAPS, KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DQT,  KC_DEL,
           KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_HOME, KC_END,  KC_PGDN, KC_PGUP, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                              KC_MPLY, KC_LALT, KC_LGUI, MO(_LOWER), KC_ENT,  KC_SPC,  KC_BSPC, MO(_RAISE), KC_RALT, KC_MUTE
),
/* LOWER
 *         ,-----------------------------------------.                    ,-----------------------------------------.
 *         | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |                    | TRNS | TRNS | TRNS | TRNS | TRNS | TRNS |
 *         |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *         | Tab  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | VolU |
 * ,-------|------+------+------+------+------+------|                    |------+------+------+------+------+------|-------.
 * | TRNS  |LCTRL |  NO  |  NO  |  NO  |  NO  |  NO  |                    | Left | Down |  Up  |Right | Enter| VolD | TRNS  |
 * `-------|------+------+------+------+------+------|-------.    ,-------|------+------+------+------+------+------|-------'
 *         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | TRNS  |    | TRNS  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 *         `-----------------------------------------| TRNS  |    | TRNS  |-----------------------------------------'
 *                 | TRNS | TRNS | TRNS | TRNS | TRNS |-------'    `-------| TRNS | TRNS | TRNS | TRNS | TRNS |
 *                 `----------------------------------'                    `----------------------------------'
 */
[_LOWER] = LAYOUT(
           _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
           KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
  _______, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  KC_VOLD, _______,
           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* RAISE
 *         ,-----------------------------------------.                    ,-----------------------------------------.
 *         |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |                    |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
 *         |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *         | Esc  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |   \  |
 * ,-------|------+------+------+------+------+------|                    |------+------+------+------+------+------|-------.
 * | TRNS  | Caps |   `  |   ~  |   ?  |   <  |   >  |                    |   :  |   -  |   +  |   [  |   ]  |   |  | TRNS  |
 * `-------|------+------+------+------+------+------|-------.    ,-------|------+------+------+------+------+------|-------'
 *         |LShift|  NO  |  NO  | Prev | Play | Next | TRNS  |    | TRNS  |   -  |   _  |   =  |   {  |   }  |  NO  |
 *         `-----------------------------------------| TRNS  |    | TRNS  |-----------------------------------------'
 *                 | TRNS | TRNS | TRNS | TRNS | TRNS |-------'    `-------| TRNS | TRNS | TRNS | TRNS | TRNS |
 *                 `----------------------------------'                    `----------------------------------'
 */
[_RAISE] = LAYOUT(
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
  _______, KC_CAPS, KC_GRV,  KC_TILD, KC_QUES, KC_LT,   KC_GT,                                       KC_COLN, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE, _______,
           KC_LSFT, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, KC_MINS, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, XXXXXXX,
                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* ADJUST
 *         ,-----------------------------------------.                    ,-----------------------------------------.
 *         | Boot |  NO  |  NO  |  NO  |  NO  |  NO  |                    |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
 *         |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *         |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |                    |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
 * ,-------|------+------+------+------+------+------|                    |------+------+------+------+------+------|-------.
 * |  NO   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |                    |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO   |
 * `-------|------+------+------+------+------+------|-------.    ,-------|------+------+------+------+------+------|-------'
 *         |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO   |    |  NO   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
 *         `-----------------------------------------|  NO   |    |  NO   |-----------------------------------------'
 *                 | TRNS | TRNS | TRNS | TRNS | TRNS |-------'    `-------| TRNS | TRNS | TRNS | TRNS | TRNS |
 *                 `----------------------------------'                    `----------------------------------'
 */
[_ADJUST] = LAYOUT(
           QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
