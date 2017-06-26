#include "keyboard.h"

#include <string>
#include <SDL.h>

namespace chaigame {
	namespace keyboard {
		Uint8* keys;

		bool isKeyDown(int key) {
			return (bool)keys[key];
		}

		bool isDown(std::string key) {
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
		}

		void setKeyRepeat(int delay, int interval) {
			SDL_EnableKeyRepeat(delay, interval);
		}

		bool load() {
			SDL_EnableUNICODE(1);
		}

		void update() {
			keys = SDL_GetKeyState(NULL);
		}

	}
}
