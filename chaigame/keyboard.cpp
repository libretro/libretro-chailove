#include "keyboard.h"

#include <string>
#include <SDL.h>

namespace chaigame {

	bool keyboard::isKeyDown(int key) {
		return (bool)keys[key];
	}

	bool keyboard::isDown(const std::string& key) {
		if (key == "down") {
			return isKeyDown(SDLK_DOWN);
		}
		if (key == "up") {
			return isKeyDown(SDLK_UP);
		}
		if (key == "left") {
			return isKeyDown(SDLK_LEFT);
		}
		if (key == "right") {
			return isKeyDown(SDLK_RIGHT);
		}

		return false;
	}

	void keyboard::setKeyRepeat(int delay, int interval) {
		SDL_EnableKeyRepeat(delay, interval);
	}

	bool keyboard::load() {
		SDL_EnableUNICODE(1);
	}

	bool keyboard::update() {
		keys = SDL_GetKeyState(NULL);
		return true;
	}

}

