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

#define LEFT_SCROLL_SCALE 512
#define RIGHT_CURSOR_SCALE ((1280 * MIKEKWRIGHT_MOUSE_SPEED) / 10)
#define LEFT_SCROLL_DIVISOR_H (16 * 10)
#define LEFT_SCROLL_DIVISOR_V (16 * 10)
#define RIGHT_CURSOR_ROTATION_SCALE 1024
#define RIGHT_CURSOR_ROTATION_COS 989
#define RIGHT_CURSOR_ROTATION_SIN 265

static int32_t left_scroll_remainder_h = 0;
static int32_t left_scroll_remainder_v = 0;

static int16_t div_round_nearest(int32_t value, int16_t divisor) {
    if (value >= 0) {
        return (value + (divisor / 2)) / divisor;
    }

    return (value - (divisor / 2)) / divisor;
}

static report_mouse_t rotate_right_report(report_mouse_t report) {
    int16_t x = report.x;
    int16_t y = report.y;

    report.x = div_round_nearest((int32_t)x * RIGHT_CURSOR_ROTATION_COS - (int32_t)y * RIGHT_CURSOR_ROTATION_SIN, RIGHT_CURSOR_ROTATION_SCALE);
    report.y = div_round_nearest((int32_t)x * RIGHT_CURSOR_ROTATION_SIN + (int32_t)y * RIGHT_CURSOR_ROTATION_COS, RIGHT_CURSOR_ROTATION_SCALE);

    return report;
}

void keyboard_post_init_user(void) {
    pointing_device_set_cpi_on_side(true, LEFT_SCROLL_SCALE);
    pointing_device_set_cpi_on_side(false, RIGHT_CURSOR_SCALE);
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    int16_t left_scroll_h;
    int16_t left_scroll_v;

    right_report = rotate_right_report(right_report);

    left_scroll_remainder_h += (int32_t)left_report.x * MIKEKWRIGHT_SCROLL_SPEED;
    left_scroll_remainder_v += (int32_t)left_report.y * MIKEKWRIGHT_SCROLL_SPEED;

    left_scroll_h = left_scroll_remainder_h / LEFT_SCROLL_DIVISOR_H;
    left_scroll_v = left_scroll_remainder_v / LEFT_SCROLL_DIVISOR_V;

    left_scroll_remainder_h -= left_scroll_h * LEFT_SCROLL_DIVISOR_H;
    left_scroll_remainder_v -= left_scroll_v * LEFT_SCROLL_DIVISOR_V;

    left_report.h = left_scroll_h;
    left_report.v = left_scroll_v;
    left_report.buttons = 0;
    left_report.x = 0;
    left_report.y = 0;

    return pointing_device_combine_reports(left_report, right_report);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_DQT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_ENT,     KC_SPC, KC_BSPC,   MO(2)
                                      //`--------------------------'  `--------------------------'

  ),

// Tab, 1, 2, 3, 4, 5,                   6, 7, 8, 9, 0, Tab
// ?, Left, Down, Up, Right, ?,       Left, Down, Up, Right, Ent, "
//


    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_TAB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   MO(3), MS_BTN1, MS_BTN3, MS_BTN2,   MO(3),                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_ENT,  KC_DQT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ENT,     KC_SPC, KC_BSPC,   MO(2)
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_GRV, KC_TILD, KC_QUES,   KC_LT,   KC_GT,                      KC_COLN, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS, KC_UNDS,  KC_EQL, KC_LCBR, KC_RCBR, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_ENT,     KC_SPC, KC_BSPC, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, MS_WHLL, MS_WHLU, MS_WHLR, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, MS_BTN1, MS_WHLD, MS_BTN2, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif
