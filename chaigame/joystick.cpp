#include "joystick.h"
#include <SDL.h>
#include <string>
#include <vector>
#include "src/Joystick.h"

#include <iostream>

namespace chaigame {
	Joystick* joystick::getJoysticks() {
		return joysticks;
	}

	void joystick::load() {
		// Initialize the joystick system.
		SDL_JoystickEventState(SDL_ENABLE);
		numJoysticks = SDL_NumJoysticks();

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

	int joystick::getNumJoysticks() {
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

	bool joystick::isDown(int index, std::string button) {
		return joysticks[index].isDown(button);
	}

	void joystick::update() {
		//SDL_JoystickUpdate();
	}

	int joystick::getButtonKey(std::string name) {
		if (name == "a") {
			return SDL_CONTROLLER_BUTTON_A;
		}
		if (name == "b") {
			return SDL_CONTROLLER_BUTTON_B;
		}
		if (name == "x") {
			return SDL_CONTROLLER_BUTTON_X;
		}
		if (name = "y") {
			return SDL_CONTROLLER_BUTTON_Y;
		}
		if (name = "select") {
			return SDL_CONTROLLER_BUTTON_BACK;
		}
		if (name = "menu") {
			return SDL_CONTROLLER_BUTTON_GUIDE;
		}
		if (name = "start") {
			return SDL_CONTROLLER_BUTTON_START;
		}
		if (name = "left") {
			return SDL_CONTROLLER_BUTTON_LEFTSTICK;
		}
		if (name = "right") {
			return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
		}
		if (name = "l1") {
			return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
		}
		if (name = "r1") {
			return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
		}
		if (name = "up") {
			return SDL_CONTROLLER_BUTTON_DPAD_UP;
		}
		if (name = "down") {
			return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
		}
		if (name = "left") {
			return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
		}
		if (name = "right") {
			return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
		}
		if (name = "turbo") {
			return SDL_CONTROLLER_BUTTON_MAX;
		}
	}
	return SDL_CONTROLLER_BUTTON_INVALID;
}
