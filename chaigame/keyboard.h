#ifndef _KEYBOARD_H_INCLUDED_
#define _KEYBOARD_H_INCLUDED_

#include <string>
#include <SDL.h>

namespace chaigame {
	class keyboard {
	public:
		Uint8* keys;
		bool load();
		bool isDown(std::string key);
		bool isKeyDown(int key);
		void setKeyRepeat(int delay = 400, int interval = 30);
		void update();

	};
}

#endif
