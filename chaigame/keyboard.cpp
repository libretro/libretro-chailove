#include "keyboard.h"

#include <string>
//#include "SDL.h"
#include "log.h"

namespace chaigame {

	bool keyboard::isDown(int key) {
		return (bool)keys[key];
	}

	bool keyboard::isDown(const std::string& key) {
		int keycode = getKeyCodeFromName(key);
		return isDown(keycode);
	}

	int keyboard::getKeyCodeFromName(const std::string& name) {
		return keyCodes[name];
	}

	void keyboard::setKeyRepeat(int delay, int interval) {
		/*if (SDL_EnableKeyRepeat(delay, interval) == -1) {
			log()->error("Error setting KeyRepeat.");
		}*/
	}

	bool keyboard::load() {
		//SDL_EnableUNICODE(1);

		// Construct the keycode map.
		//for (int i = 0; i < SDLK_LAST; i++) {
			/*std::string name(SDL_GetKeyName((SDLKey)i));
			if (!name.empty()) {
				keyCodes[name] = i;
			}*/
		//}

		return true;
	}

	bool keyboard::update() {
		//keys = SDL_GetKeyState(NULL);
		return true;
	}
}

