#include "keyboard.h"

#include <string>
#include <SDL/SDL.h>

namespace chaigame {
	namespace keyboard {
		Uint8* keys;

		bool isDown(int key) {
			return (bool)keys[key];
		}

		bool isDown(std::string key) {
			if (key == "down") {
				return isDown(SDLK_DOWN);
			}
			if (key == "up") {
				return isDown(SDLK_UP);
			}
			if (key == "left") {
				return isDown(SDLK_LEFT);
			}
			if (key == "right") {
				return isDown(SDLK_RIGHT);
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
