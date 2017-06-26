#ifndef _KEYBOARD_H_INCLUDED_
#define _KEYBOARD_H_INCLUDED_

#include <string>
#include <SDL/SDL.h>

namespace chaigame {
namespace keyboard {

	bool load();
	bool isDown(std::string key);
	bool isDown(int key);
	void setKeyRepeat(int delay = 400, int interval = 30);
	void update();

}
}

#endif
