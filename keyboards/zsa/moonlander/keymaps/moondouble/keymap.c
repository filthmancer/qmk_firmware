#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE


enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_CONSOLE,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_NONUS_BACKSLASH,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_ESC,                              KC_RIGHT,       KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_UP,                                          TG(1),          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,        
    KC_ENTER,       KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_DOWN,                                        KC_MEH,         KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOTE,       
    KC_LEFT_SHIFT,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RIGHT_SHIFT, 
    KC_LEFT_CTRL,   KC_LEFT_GUI,    KC_RIGHT_ALT,   KC_LEFT,        KC_RIGHT,       OSL(1),                                                         MT(MOD_LCTL, KC_ESCAPE),KC_UP,          KC_DOWN,        KC_LBRC,        KC_RBRC,        MO(1),          
    
    KC_SPACE,       KC_LEFT_SHIFT, TD(DANCE_CONSOLE),                                                                                                          KC_LEFT_ALT,    KC_TAB,         KC_ENTER
  ),
  [1] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          TD(DANCE_2),                                    KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_TRANSPARENT, KC_KP_PLUS,     KC_KP_MINUS,    KC_KP_ASTERISK, KC_KP_SLASH,    KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_UP,          KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_F12,         
    KC_TRANSPARENT, KC_HASH,        KC_AT,          KC_BSPC,        KC_DELETE,      KC_DLR,          KC_TRANSPARENT,                                KC_TRANSPARENT, KC_DOWN,        KC_4,           KC_5,           KC_6,           KC_KP_PLUS,     KC_TRANSPARENT, 
    KC_EXLM,        KC_AT,          KC_HASH,        TD(DANCE_0),    TD(DANCE_1),    KC_DLR,                                                         KC_AMPR,        KC_1,           KC_2,           KC_3,           KC_BSLS,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        TO(0),                                                 KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT, KC_DOT,         KC_0,           KC_EQUAL,       KC_TRANSPARENT, 
    
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_AUDIO_VOL_DOWN,KC_MEDIA_STOP,  KC_AUDIO_VOL_UP
  ),
  [2] = LAYOUT_moonlander(
    KC_TRANSPARENT,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,                          QK_UNDERGLOW_TOGGLE, QK_UNDERGLOW_MODE_NEXT, QK_UNDERGLOW_VALUE_UP, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    MU_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_UP,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    MU_NEXT,        KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,
    KC_AUDIO_MUTE, KC_TRANSPARENT, KC_TRANSPARENT,  KC_MS_BTN1,     KC_MS_BTN2,     KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_BTN2,     KC_TRANSPARENT,                                                 KC_TRANSPARENT, KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, 

    KC_MEDIA_PLAY_PAUSE, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
  ),
};


#define ACTION_TAP_DANCE_OVERRIDE(tap, held) \
    { .fn = {on_dance(tap, held), dance_finished(tap, held), dance_reset(tap, held), NULL}, .user_data = NULL, }


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  }
  return true;
}


typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
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



void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data); 
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRC);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_LBRC); break;
        case SINGLE_HOLD: register_code16(KC_LCBR); break;
        case DOUBLE_TAP: register_code16(KC_LBRC); register_code16(KC_LBRC); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); register_code16(KC_LBRC);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code16(KC_LCBR); break;
        case DOUBLE_TAP: unregister_code16(KC_LBRC); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRC);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_RBRC); break;
        case SINGLE_HOLD: register_code16(KC_RCBR); break;
        case DOUBLE_TAP: register_code16(KC_RBRC); register_code16(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); register_code16(KC_RBRC);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code16(KC_RCBR); break;
        case DOUBLE_TAP: unregister_code16(KC_RBRC); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
    }
    dance_state[1].step = 0;
}


void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
    }
    if(state->count > 3) {
        tap_code16(KC_GRAVE);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_GRAVE); break;
        case SINGLE_HOLD: register_code16(C(KC_GRAVE)); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); register_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_GRAVE); register_code16(KC_GRAVE);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_GRAVE); break;
        case SINGLE_HOLD: unregister_code16(C(KC_GRAVE)); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
    }
    dance_state[1].step = 0;
}

void on_dance_console(tap_dance_state_t *state, void *user_data);
void dance_console_finished(tap_dance_state_t *state, void *user_data);
void dance_console_reset(tap_dance_state_t *state, void *user_data);

void on_dance_console(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(MEH(KC_GRAVE));
        tap_code16(MEH(KC_GRAVE));
        tap_code16(MEH(KC_GRAVE));
    }
    if(state->count > 3) {
        tap_code16(MEH(KC_GRAVE));
    }
}

void dance_console_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(MEH(KC_GRAVE)); break;
        case SINGLE_HOLD: layer_on(2); break;
        case DOUBLE_TAP: register_code16(MEH(KC_GRAVE)); register_code16(MEH(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(MEH(KC_GRAVE)); register_code16(MEH(KC_GRAVE));
    }
}

void dance_console_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(MEH(KC_GRAVE)); break;
        case SINGLE_HOLD: layer_off(2); break;
        case DOUBLE_TAP: unregister_code16(MEH(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(MEH(KC_GRAVE)); break;
    }
    dance_state[1].step = 0;
}



tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_CONSOLE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_console, dance_console_finished, dance_console_reset),
};
