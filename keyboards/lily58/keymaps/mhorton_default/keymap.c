#include QMK_KEYBOARD_H
#include "version.h"

enum layer_number {
  _QWERTY = 0,
  _NUMPAD,
  _MEDIA,
  _LEFTGOD,
};

#include QMK_KEYBOARD_H


#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

enum tap_dance_codes {
  DANCE_LAYER_MEDIA,
  DANCE_LAYER_LEFTY,
  DANCE_LAYER_NUMPAD,
};

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;
static tap dance_state[1];
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tab   |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Enter|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  |   ]  |
 * |------+------+------+------+------+------| L1     |    | [     |------+------+------+------+------+------|
 * |BackSP| 1/F1 | 2/F2 | 3/F3 | 4/F4 | 5/F5  |-------|    |-------| 6/F6 | 7/F7 | 8/F8 | 9/F9 | 0/F10|  -   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |L1    |L2    | L3   | /Space  /       \Enter \  |L1    |L2    | L3   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_GRV,   \
  KC_TAB,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  KC_SCLN,   KC_QUOT,  \
  KC_SFTENT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,   KC_RBRC,  \
  KC_LCTL,  KC_LALT,  KC_LGUI,  KC_3,  KC_4,  TT(_LEFTGOD), TD(DANCE_LAYER_MEDIA),  KC_LBRC,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS,  \
                        TT(1),   TT(2),  TT(_NUMPAD),   KC_SPACE,   KC_SFTENT,  TT(1),   TT(2),  TT(3) \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |  7   |   8  |   9  |   +  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |      |   4  |   5  |   6  |   ,  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Enter |      |   1  |   2  |   3  |   0  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|Delete |    |       |------+------+------+------+------+------|
 * |LCtrl |      |   /  |   *  |  -   |   =  |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LShft | /Space  /       \Enter \  |L0    |L2    |  L3  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUMPAD] = LAYOUT( \
  KC_TRNS, KC_NO,   KC_7,    KC_8,    KC_9,    KC_PPLS,               KC_1,   KC_2,      KC_3,    KC_PMNS, KC_PMNS, KC_NO, \
  KC_TRNS, KC_NO,   KC_4,    KC_5,    KC_6,    KC_PCMM,               KC_NO,  KC_4,      KC_6,    KC_3,    KC_PPLS, KC_NO, \
  KC_TRNS, KC_0,   KC_1,    KC_2,    KC_3,     KC_PEQL,                 KC_NO,  KC_7,      KC_8,    KC_9,    KC_PCMM, KC_NO, \
  KC_TRNS, KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PEQL, KC_NO, KC_NO, KC_NO,  KC_PSLS,   KC_PAST, KC_PMNS, KC_PEQL, KC_PIPE, \
                             TO(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(0), KC_TRNS, KC_TRNS\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |      |  Up  |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tab   |      | Left | Down |Right |Delete|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Enter |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LShft | /Space  /       \Enter \  |L1    |L0    | L3   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_MEDIA] = LAYOUT( \
  KC_TRNS, _______, _______, KC_UP, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  KC_TRNS, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,                     _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, \
  KC_TRNS, _______, _______, _______, _______, _______,                    _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,_______,
  KC_TRNS, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______, _______, _______, \
                             KC_TRNS, TO(0), KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, TO(0), KC_TRNS \
),
/* LEFTY GOD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   Y  |  U   |  I   |   O  |   P  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  H   |  J   |  K   |  L   |   ;  |   '  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  N   |  M   |   ,  |   .  |   /  |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_LEFTGOD] = LAYOUT( \
  KC_TRNS, KC_P, KC_O, KC_I, KC_U, KC_Y,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_QUOT, KC_SCLN, KC_L, KC_K, KC_J, KC_H,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_TRNS, KC_SLSH, KC_DOT, KC_COMM, KC_M, KC_N,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, TO(0), _______, _______,  _______, _______, TO(0) \
  )
};

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

void oled_task_user(void) {
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

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void dance_advanced_start(qk_tap_dance_state_t *state, void *user_data, uint16_t kc);
void dance_advanced_finish(qk_tap_dance_state_t *state, void *user_data, uint16_t kc, uint8_t layer);
void dance_advanced_reset(qk_tap_dance_state_t *state, void *user_data, uint16_t kc, uint8_t layer);

void dance_advanced_start(qk_tap_dance_state_t *state, void *user_data, uint16_t kc) {
    if(state->count == 3) {
        tap_code16(kc);
        tap_code16(kc);
        tap_code16(kc);
    }
    if(state->count > 3) {
        tap_code16(kc);
    }
}

void dance_advanced_finish(qk_tap_dance_state_t *state, void *user_data, uint16_t kc, uint8_t layer) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(kc); break;
        case SINGLE_HOLD: register_code16(kc); break;
        case DOUBLE_TAP: tap_code16(kc); register_code16(kc); break;
        case DOUBLE_HOLD: layer_on(layer); break;
        case DOUBLE_SINGLE_TAP: tap_code16(kc); register_code16(kc);
    }
}

void dance_advanced_reset(qk_tap_dance_state_t *state, void *user_data, uint16_t kc, uint8_t layer) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(kc); break;
        case SINGLE_HOLD: unregister_code16(kc); break;
        case DOUBLE_TAP: unregister_code16(kc); break;
        case DOUBLE_HOLD: layer_off(layer); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(kc); break;
    }
    dance_state[0].step = 0;
}

void dance1_start(qk_tap_dance_state_t *state, void *user_data);
void dance1_finish(qk_tap_dance_state_t *state, void *user_data);
void dance1_reset(qk_tap_dance_state_t *state, void *user_data);

void dance1_start(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_start(state, user_data, KC_BSPACE);
}
void dance1_finish(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_finish(state, user_data, KC_BSPACE, _MEDIA);
}
void dance1_reset(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_reset(state, user_data, KC_BSPACE, _MEDIA);
}

void dance2_start(qk_tap_dance_state_t *state, void *user_data);
void dance2_finish(qk_tap_dance_state_t *state, void *user_data);
void dance2_reset(qk_tap_dance_state_t *state, void *user_data);

void dance2_start(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_start(state, user_data, KC_SPACE);
}
void dance2_finish(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_finish(state, user_data, KC_SPACE,_LEFTGOD);
}
void dance2_reset(qk_tap_dance_state_t *state, void *user_data)
{
  dance_advanced_reset(state, user_data, KC_SPACE,_LEFTGOD);
}



qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_LAYER_MEDIA] = ACTION_TAP_DANCE_FN_ADVANCED(dance1_start, dance1_finish, dance1_reset),
        [DANCE_LAYER_LEFTY] = ACTION_TAP_DANCE_FN_ADVANCED(dance2_start, dance2_finish, dance2_reset),
};