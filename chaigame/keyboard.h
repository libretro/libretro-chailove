#ifndef CHAIGAME_KEYBOARD_H
#define CHAIGAME_KEYBOARD_H

#include <string>
#include <map>
#include "SDL.h"

namespace chaigame {
	class keyboard {
	public:
		Uint8* keys;
		bool load();
		bool isDown(const std::string& key);
		bool isDown(int key);
		void setKeyRepeat(int delay = 400, int interval = 30);
		bool update();
		int getKeyCodeFromName(const std::string& name);

		std::map<std::string, int> keyCodes;
	};
}

#endif
