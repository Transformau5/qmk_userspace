/* Copyright (C) 2022 jonylee@hfd
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
    WIN_WASD,
    WIN_FN,
    MAC_B,
    MAC_WASD,
    MAC_FN
};

void keyboard_post_init_user(void)
{
	rgb_matrix_enable_noeeprom();
	rgb_matrix_set_speed_noeeprom(147);
	rgb_matrix_sethsv_noeeprom(15, 255, 255);
	rgb_matrix_mode_noeeprom(RGB_MATRIX_ALPHAS_MODS);
}

bool rgb_matrix_indicators_user(void) {
	//Set the modifier keys to a certain colour because doing so the usual way is not a thing in userspaces it seems
	int modifiers[] = {0, 11, 12, 20, 33, 41, 54, 74, 78, 89, 95, 96, 97, 99, 100, 101, 102};
	for (int i=0; i<17; i++){
		rgb_matrix_set_color(modifiers[i], 255, 21, 0);
	}
	//Set the gradient of the numpad keys except the Num Lock
	int numpad_gradient_columns[4][6] = {{16, 58, 75, 91, 106, 106}, {17, 38, 59, 76, 92, 92}, {18, 39, 60, 77, 93, 107}, {19, 40, 61, 94, 94, 94}}; //Extremely ugly, repeating the last element of each sub-array just so that I can force a 2D array and call it a day
	int numpad_gradient_colours[4][3] = {{255, 0, 200}, {255, 0, 255}, {200, 0, 255}, {144, 0, 255}};
	for (int i=0; i<4; i++){
		for (int j=0; j<6; j++){
			rgb_matrix_set_color(numpad_gradient_columns[i][j], numpad_gradient_colours[i][0], numpad_gradient_colours[i][1], numpad_gradient_colours[i][2]);
		}
	}
	//Set the colour of the arrow keys
	int arrow_keys[4] = {90, 104, 103, 105};
	for (int m=0; m<4; m++){
		switch (m){
			case 0:
				rgb_matrix_set_color(arrow_keys[m], 255, 0, 89);
				break;
			case 1:
				rgb_matrix_set_color(arrow_keys[m], 255, 0, 89);
				break;
			case 2:
				rgb_matrix_set_color(arrow_keys[m], 255, 0, 34);
				break;
			case 3:
				rgb_matrix_set_color(arrow_keys[m], 255, 0, 145);
				break;
		}
	}
	/*Set the gradient of the Home cluster (Insert, Home, Page Up, etc.)*/
	int home_block[3][3] = {{13, 14, 15}, {34, 35, 36}, {55, 56, 57}};
	for (int n=0; n<3; n++){
		for (int o=0; o<3; o++){
			if(o==0){
				rgb_matrix_set_color(home_block[n][o], 255, 0, 34);
			}
			if(o==1){
				rgb_matrix_set_color(home_block[n][o], 255, 0, 89);
			}
			if(o==2){
				rgb_matrix_set_color(home_block[n][o], 255, 0, 145);
			}
		}
	}
	if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(62, 0, 182, 79); // Change the colour of Caps Lock upon activation
    } else {
        rgb_matrix_set_color(62, 255, 21, 0);
    }

	if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(37, 0, 182, 79); // Change the colour of Num Lock upon activation
    } else {
        rgb_matrix_set_color(37, 255, 0, 200);
    }
	return true;
}



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT( /* Base */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUS, KC_CALC, KC_MUTE, KC_VOLD, KC_VOLU,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI, MO(WIN_FN),       KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT,          KC_P0,   KC_PDOT),

    [WIN_WASD] = LAYOUT( /* Base */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          KC_W,             _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            _______, _______, MO(WIN_FN),       _______, KC_A,    KC_S,    KC_D,             _______, _______),


    [WIN_FN] = LAYOUT( /* FN */
	    _______, KC_MYCM, KC_MAIL, KC_WSCH, KC_WHOM, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, _______,_______,  _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______,TG(WIN_WASD),_______,_______,_______,_______, _______, _______, DF(MAC_B),_______,_______, _______, RGB_MOD, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______,          RGB_HUI,                                     _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          RGB_VAI,          _______, _______, _______, _______,
		_______, GU_TOGG, _______,                   _______,                            _______, _______, _______,          KC_F20, RGB_SAD, RGB_VAD, RGB_SAI,          _______, _______),

    [MAC_B] = LAYOUT( /* Base */
		KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,          KC_PSCR, KC_SCRL, KC_PAUS, KC_CALC, KC_MUTE, KC_VOLD, KC_VOLU,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, KC_RALT, MO(MAC_FN),       KC_RCTL, KC_LEFT, KC_DOWN,   KC_RGHT,        KC_P0,   KC_PDOT),

    [MAC_WASD] = LAYOUT( /* Base */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          KC_W,             _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            _______, _______, MO(MAC_FN),       _______, KC_A,    KC_S,    KC_D,             _______, _______),
    [MAC_FN] = LAYOUT( /* FN */
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______,  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______,TG(MAC_WASD),_______,_______,_______,_______, _______, _______, DF(WIN_B),_______,_______, _______, RGB_MOD, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______,          RGB_HUI,                                     _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          RGB_VAI,          _______, _______, _______, _______,
		_______, _______, _______,                   _______,                            _______, _______, _______,          _______, RGB_SAD, RGB_VAD, RGB_SAI,          _______, _______)
};
// clang-format on
