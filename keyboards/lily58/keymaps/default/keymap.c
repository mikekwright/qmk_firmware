#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};


//
//  For the lily58 I am going to try a couple of different things, the first thing to really try
//     is to get the keyboard configured in a way that would let me use hold keys in different
//     orders (that is in initial).  I am going to try to use the modes instead since I think
//     the is going to be the more useful longterm if I can figure out how to get my brain to work
//     in that style.
//

//
//  Notes:
//   * MO() -> Move to a different layer
//   * TO() -> Use a layer while the button is pressed
//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TAB  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|   ~   |    |   /   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *                   | LAlt | Win  | FUNC | / Enter /      \ Space \  |BackSP |_SYMBO| RAlt |
 *                   |      |      |      |/       /        \       \ |       |      |      |
 *                   `----------------------------'          '-------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_TAB,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRAVE,
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_DQT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_TILDE,  KC_SLSH,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                  KC_LALT, KC_LGUI,MO(_LOWER), KC_ENT,           KC_SPC, KC_BSPC, MO(_RAISE), KC_RALT
),



/* SYMBOL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   `  |   ~  |   ?  |   <  |   >  |-------.    ,-------|   :  |   -  |   +  |   [  |   ]  |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      | CAPS | Enter|-------|    |-------| Enter|   _  |   =  |   {  |   }  |RShift|
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *                  | LAlt |  Win |FUNCS  | / Enter /      \ Space \  |BackSP |_QWERTY| RAlt |
 *                  |      |      |       |/       /        \       \ |       |       |      |
 *                  `-----------------------------'          '-------''----------------------'
 */
[_RAISE] = LAYOUT(
  KC_TAB,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_ESC,  KC_EXLM,    KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
 KC_LCTL, KC_GRAVE, KC_TILDE, KC_QUES,   KC_LT,   KC_GT,                  KC_COLON, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,
 KC_LSFT,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_CAPS,  KC_ENT, XXXXXXX, XXXXXXX,  KC_ENT, KC_UNDS,  KC_EQL, KC_LCBR, KC_RCBR, KC_RSFT,
                           KC_LALT, KC_LGUI, MO(_LOWER), KC_ENT,          KC_SPC, KC_BSPC, TO(_QWERTY), KC_RALT
),




/* FUNCS
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |      |  RGB  |RGBMOD|      |      |      |                    |      |      |      |      |      |      |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1   |   2  |   3  |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |      |
 * |------+-------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Left | Down |  Up  |Right | Win  |-------.    ,-------| Left | Down |  Up  |Right | Enter|      |
 * |------+-------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  F1  |  F2   |  F3  |  F4  |  F5  |  F6  |-------|    |-------|  F7  |  F8  |  F9  | F10  |  F11 | F12  |
 * `------------------------------------------/      /     \       \-----------------------------------------'
 *                 | LAlt | Win   | QWERTY| / Enter /       \ Space \  |BackSP | SYMBOL| RAlt |
 *                 |      |       |       |/       /         \       \ |       |       |      |
 *                 `------------------------------'           '-------''----------------------'
 */
[_LOWER] = LAYOUT(
 XXXXXXX, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
 XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,     KC_9,    KC_0, XXXXXXX,
 KC_LCTL, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX,                    KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT,  KC_ENT, XXXXXXX,
   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, XXXXXXX,  XXXXXXX,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                    KC_LALT, KC_LGUI, MO(_QWERTY), KC_ENT,    KC_SPC, KC_BSPC, MO(_RAISE), XXXXXXX
),




/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
