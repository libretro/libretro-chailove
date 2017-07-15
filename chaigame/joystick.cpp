#include "joystick.h"
#include "SDL.h"
#include <string>
#include <vector>
#include <libretro.h>
#include "src/Joystick.h"
#include "../Game.h"

#include <iostream>

namespace chaigame {
	Joystick* joystick::getJoysticks() {
		return joysticks;
	}

	void joystick::load() {
		// TODO: Switch joystick callbacks from libretro to SDL.

		// Initialize the joystick system.
		//SDL_JoystickEventState(SDL_ENABLE);

		//numJoysticks = SDL_NumJoysticks();
		numJoysticks = 4;

		// Create the joystick handlers.
		joysticks = new Joystick[numJoysticks];
		for (int i = 0; i < numJoysticks; i++) {
			joysticks[i].open(i);
		}
	}

	void joystick::unload() {
		for (int i = 0; i < numJoysticks; i++) {
			close(i);
		}
	}

	int joystick::getJoystickCount() {
		return numJoysticks;
	}

	void joystick::close(int index) {
		if (isOpen(index)) {
			joysticks[index].close();
		}
	}

	bool joystick::isOpen(int index) {
		return joysticks[index].isOpen();
	}

	bool joystick::isDown(int index, int button) {
		return joysticks[index].isDown(button);
	}

	bool joystick::isDown(int index, const std::string& button) {
		return joysticks[index].isDown(button);
	}

	void joystick::update() {
		//SDL_JoystickUpdate();
		int i, u;
		int16_t state;

		// Loop through each joystick.
		for (i = 0; i < 4; i++) {
			// Loop through each button.
			for (u = 0; u < 14; u++) {
				// Retrieve the state of the button.
				state = Game::input_state_cb(i, RETRO_DEVICE_JOYPAD, 0, u);

				// Check if there's a change of state.
				if (joystick_cache[i][u] != state) {
					joystick_cache[i][u] = state;

					// TODO: Invoke an event.
					if (state == 1) {
						Game::getInstance()->script->joystickpressed(i, u);
					}
					else if (state == 0) {
						Game::getInstance()->script->joystickreleased(i, u);
					}
				}
			}
		}
	}

	Joystick& joystick::operator[](int i) {
		if (i < 0 || i >= numJoysticks) {
			i = 0;
		}
		return joysticks[i];
	}

	int joystick::getButtonKey(const std::string& name) {
		if (name == "a") {
			return RETRO_DEVICE_ID_JOYPAD_A;
		}
		if (name == "b") {
			return RETRO_DEVICE_ID_JOYPAD_B;
		}
		if (name == "x") {
			return RETRO_DEVICE_ID_JOYPAD_X;
		}
		if (name == "y") {
			return RETRO_DEVICE_ID_JOYPAD_Y;
		}
		if (name == "select" || name == "back") {
			return RETRO_DEVICE_ID_JOYPAD_SELECT;
		}
		if (name == "start") {
			return RETRO_DEVICE_ID_JOYPAD_START;
		}
		if (name == "l1" || name == "leftshoulder") {
			return RETRO_DEVICE_ID_JOYPAD_L;
		}
		if (name == "r1" || name == "rightshoulder") {
			return RETRO_DEVICE_ID_JOYPAD_R;
		}
		if (name == "l2") {
			return RETRO_DEVICE_ID_JOYPAD_L2;
		}
		if (name == "r2") {
			return RETRO_DEVICE_ID_JOYPAD_R2;
		}
		if (name == "l3") {
			return RETRO_DEVICE_ID_JOYPAD_L3;
		}
		if (name == "r3") {
			return RETRO_DEVICE_ID_JOYPAD_R3;
		}
		if (name == "up" || name == "dpup") {
			return RETRO_DEVICE_ID_JOYPAD_UP;
		}
		if (name == "down" || name == "dpdown") {
			return RETRO_DEVICE_ID_JOYPAD_DOWN;
		}
		if (name == "left" || name == "dpleft") {
			return RETRO_DEVICE_ID_JOYPAD_LEFT;
		}
		if (name == "right" || name == "dpriht") {
			return RETRO_DEVICE_ID_JOYPAD_RIGHT;
		}
		return -1;
	}
}
