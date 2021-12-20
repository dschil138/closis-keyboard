/* Copyright 2020 Fidel Coria
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
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"

/*#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#endif*/

enum pteron_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  /*BALL_LC = SAFE_RANGE,
  BALL_SCR,*/
};

/*
enum custom_keycodes {
  BALL_LC = SAFE_RANGE,
  BALL_SCR,
}
*/

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +------------------------------------------------+      +-----------------------------------------------+
 * | Tab   |   Q   |   W   |   F   |   P   |   B    |      |   J   |   L   |   U   |   Y   |   ;   |   +   |
 * |-------+-------+-------+-------+-------+--------|      |-------+-------+-------+-------+-------+-------|
 * | BKSP  |   A   |   R   |   S   |   T   |   G    |      |   M   |   N   |   E   |   I   |   O   |  "    |
 * |-------+-------+-------+-------+-------+--------|      |-------+-------+-------+-------+-------+-------|
 * | Shift |   Z   |   X   |   C   |   D   |   V    |      |   K   |   H   |   ,   |   .   |   /   |Enter  |
 * |-------+-------+-------+-------+-------+--------|      |-------+-------+-------+-------+-------+-------|
 *                 | ALT   |  SPC  |  GUI  |LOWER   |      | RAISE |  GUI  |  SPC  |  CTRL |
 *                 +--------------------------------+      +-------------------------------+
 */
[_QWERTY] = LAYOUT(
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,            KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                     KC_LALT, LSFT(KC_SPC), KC_LGUI, LOWER,       RAISE, KC_RGUI, RSFT(KC_SPC), KC_RCTL
),

/* Lower                                            |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * +-----------------------------------------+      +-----------------------------------------+
 * |  Esc |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   _  |   +  |   {  |   }  |  Bksp|
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |      |   ^  |   &  |   *  |   (  |   )  |   =  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO ~ |ISO | |      |      |      |
 * +-------------+------+------+------+------|      |------+------+------+------+-------------+
 *               |      | Space| Shift|      |      |      | Vol- | Vol+ |      |
 *               +---------------------------+      +---------------------------+
 */
[_LOWER] = LAYOUT(
  KC_ESC,  KC_F1,   KC_BRID, KC_BRIU,   KC_F4,   KC_F5,           KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSPC,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END, _______,
                    _______, KC_SPC, KC_RSFT, _______,         _______, KC_VOLD, KC_VOLU, _______

),

/* Raise
 * +-----------------------------------------+      +-----------------------------------------+
 * |  `   |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   -  |   =  |   [  |   ]  |Bksp  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * | Bspc |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO # |ISO / |      |      |      |
 * +-------------+------+------+------+------|      |------+------+------+------+-------------+
 *               |      | Next | Play |      |      |      | Vol- | Vol+ |      |
 *               +---------------------------+      +---------------------------+
 */
[_RAISE] = LAYOUT(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSPC,
  KC_BSPC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F11,          KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
                    _______, KC_SPC, KC_SPC, _______,         _______, KC_VOLD, KC_VOLU, _______
),

/* Adjust (Lower + Raise)
 * +-----------------------------------------+      +-----------------------------------------+
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |Brght-|Brght+|      | Debug| Reset|
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 * |      |      |      |      | Debug| Reset|      |      | Vol- | Vol+ |      |      |      |
 * |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *               |      |      |      |      |      |      |      |      |      |
 *               +---------------------------+      +---------------------------+
 */
[_ADJUST] = LAYOUT(
  KC_F1,   KC_F2,   KC_BTN2,   _______, KC_BTN1, KC_WH_U,           KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, KC_MS_L, KC_MS_U, KC_MS_R, KC_WH_D,         _______, KC_BRID, KC_BRIU, _______, DEBUG, RESET,
  _______, _______, _______, KC_MS_D, KC_BTN2, _______,           _______, KC_VOLD, KC_VOLU, _______, _______, _______,
                    _______, _______, KC_SPC, _______,         _______, KC_SPC, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

enum combos {
  E_I_ENT,
  N_O_MUTE,
  R_S_BSPC,
  HIGHLIGHT,

};

const uint16_t PROGMEM e_i_ent[] = { KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM n_o_mute[] = { KC_N, KC_O, COMBO_END};
const uint16_t PROGMEM r_s_bspc[] = { KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM highlight[] = { KC_P, KC_B, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
  [E_I_ENT] = COMBO(e_i_ent, KC_ENT),
  [N_O_MUTE] = COMBO(n_o_mute, KC_MUTE),
  [R_S_BSPC] = COMBO(r_s_bspc, KC_BSPC),
  [HIGHLIGHT] = COMBO(highlight, LSFT(KC_BTN1)),

};

/* bool process_record_user(uint16_t keycode, keyrecord_t *record){
  switch (keycode){
#ifdef PIMORONI_TRACKBALL_ENABLE
  case BALL_LC:
     record->event.pressed?register_code(KC_BTN1):unregister_code(KC_BTN1);
     break;
  case BALL_SCR:
    if(record->event.pressed){
      trackball_set_scrolling(true);
    } else{
      trackball_set_scrolling(false);
    }
    break;
#endif
  default:
#ifdef OLED_ENABLE
    if (record->event.pressed) {
      set_keylog(keycode, record);
    }
#endif
    break;
  }
  return true;
} */
