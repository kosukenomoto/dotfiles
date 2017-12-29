/*
 * SpaceFN
 * http://geekhack.org/index.php?topic=51069.0
 */
#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  `|BSp|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * `-----------------------------------------------------------'
     *       |Gui|Alt  |         SpaceFN       |Alt  |Gui|
     *       `-------------------------------------------'
     */
    KEYMAP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS, GRV,  \
           TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC, DEL,       \
           LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,             \
           LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN0,             \
                LGUI,LALT,          FN1,                RALT,RGUI),

    /* Layer 1: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */ 
    KEYMAP(PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,   \
           CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS, UP, TRNS, BSPC,      \
           TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,PENT,            \
           TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS,TRNS,            \
                TRNS,TRNS,          SPC,                TRNS,TRNS),

    /* Layer 2: SpaceFN
     * ,-----------------------------------------------------------.
     * |`  | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |Del|
     * |-----------------------------------------------------------|
     * |     |   |   |Esc|   |   |   |Hom|Up |End|Psc|Slk|Pau|Ins  |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |PgU|Lef|Dow|Rig|   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |Spc|PgD|`  |~  |   |   |      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */
    KEYMAP(GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,DEL,   \
           TRNS,TRNS,TRNS, ESC,TRNS,TRNS,HOME, DEL,BSPC,TRNS,FN13, FN2, FN3,TRNS,       \
           TRNS, FN5,TRNS, DEL,BSPC,TRNS, FN9,FN10,FN11,FN12, ENT,TRNS,TRNS,            \
           TRNS, FN6,TRNS, FN7, FN8, SPC, TAB, FN4,TRNS,TRNS,TRNS,TRNS,NO,              \
                TRNS,TRNS,          TRNS,               TRNS,TRNS),
};


/*
 * user defined action function
 */
enum function_id {
    CTRL_SPACE_H,       // Ctrl + Left(SpaceFN) -> HOME
    CTRL_SPACE_J,       // Ctrl + Down(SpaceFN) -> Pgdown
    CTRL_SPACE_K,       // Ctrl + Up(SpaceFN) -> Pgup
    CTRL_SPACE_L,       // Ctrl + Right(SpaceFN) -> END
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
#   define MODS_CTRL_MASK   (MOD_BIT(KC_LCTRL)|MOD_BIT(KC_RCTRL))
    static uint8_t ctrl_space_h_prev_ctrl;
    static uint8_t ctrl_space_j_prev_ctrl;
    static uint8_t ctrl_space_k_prev_ctrl;
    static uint8_t ctrl_space_l_prev_ctrl;

    switch (id) {
	// KC_CTRL + Left(SpaceFN) -> HOME
        case CTRL_SPACE_H:
            ctrl_space_h_prev_ctrl = get_mods()&MODS_CTRL_MASK;
            if (record->event.pressed) {
                if (ctrl_space_h_prev_ctrl) {
                    del_mods(ctrl_space_h_prev_ctrl);   // remove Ctrl
                    add_key(KC_HOME);
                    send_keyboard_report(); // send key without Ctrl
                    add_mods(ctrl_space_h_prev_ctrl);   // return Ctrl but not sent
                } else {
                    add_key(KC_LEFT);
                    send_keyboard_report();
                }
            } else {
                if (ctrl_space_h_prev_ctrl) {
                    del_key(KC_HOME);
                    send_keyboard_report();
		} else {
                    del_key(KC_LEFT);
                    send_keyboard_report();
                }
            }
            break;

        case CTRL_SPACE_J:
            ctrl_space_j_prev_ctrl = get_mods()&MODS_CTRL_MASK;
            if (record->event.pressed) {
                if (ctrl_space_j_prev_ctrl) {
                    del_mods(ctrl_space_j_prev_ctrl);   // remove Ctrl
                    add_key(KC_PGDN);
                    send_keyboard_report(); // send key without Ctrl
                    add_mods(ctrl_space_j_prev_ctrl);   // return Ctrl but not sent
                } else {
                    add_key(KC_DOWN);
                    send_keyboard_report();
                }
            } else {
                if (ctrl_space_j_prev_ctrl) {
                    del_key(KC_PGDN);
                    send_keyboard_report();
                } else {
                    del_key(KC_DOWN);
                    send_keyboard_report();
                }
            }
            break;

        case CTRL_SPACE_K:
            ctrl_space_k_prev_ctrl = get_mods()&MODS_CTRL_MASK;
            if (record->event.pressed) {
                if (ctrl_space_k_prev_ctrl) {
                    del_mods(ctrl_space_k_prev_ctrl);   // remove Ctrl
                    add_key(KC_PGUP);
                    send_keyboard_report(); // send key without Ctrl
                    add_mods(ctrl_space_k_prev_ctrl);   // return Ctrl but not sent
                } else {
                    add_key(KC_UP);
                    send_keyboard_report();
                }
            } else {
                if (ctrl_space_k_prev_ctrl) {
                    del_key(KC_PGUP);
                    send_keyboard_report();
                } else {
                    del_key(KC_UP);
                    send_keyboard_report();
                }
            }
            break;

        case CTRL_SPACE_L:
            ctrl_space_l_prev_ctrl = get_mods()&MODS_CTRL_MASK;
            if (record->event.pressed) {
                if (ctrl_space_l_prev_ctrl) {
                    del_mods(ctrl_space_l_prev_ctrl);   // remove Ctrl
                    add_key(KC_END);
                    send_keyboard_report(); // send key without Ctrl
                    add_mods(ctrl_space_l_prev_ctrl);   // return Ctrl but not sent
                } else {
                    add_key(KC_RGHT);
                    send_keyboard_report();
                }
            } else {
                if (ctrl_space_l_prev_ctrl) {
                    del_key(KC_END);
                    send_keyboard_report();
                } else {
                    del_key(KC_RGHT);
                    send_keyboard_report();
                }
            }
            break;
    }
}


/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
    [1] = ACTION_LAYER_TAP_KEY(2, KC_SPACE),
    [2] = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_LEFT),    // Display left 
    [3] = ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_RGHT),    // Display right 
    [4] = ACTION_KEY(MOD_LALT | KC_GRV),    // WindowsIMEONOFF
    [5] = ACTION_MODS_KEY(MOD_LCTL , KC_A),      // Ctrl + A 
    [6] = ACTION_MODS_KEY(MOD_LCTL , KC_X),      // Ctrl + X 
    [7] = ACTION_MODS_KEY(MOD_LCTL , KC_C),      // Ctrl + C 
    [8] = ACTION_MODS_KEY(MOD_LCTL , KC_V),      // Ctrl + V 
    [9] = ACTION_FUNCTION(CTRL_SPACE_H),        // HOME 
    [10] = ACTION_FUNCTION(CTRL_SPACE_J),        // PGDN
    [11] = ACTION_FUNCTION(CTRL_SPACE_K),        // PGUP 
    [12] = ACTION_FUNCTION(CTRL_SPACE_L),        // END
    [13] = ACTION_MODS_KEY(MOD_LGUI , KC_TAB),    // Display left 
};
