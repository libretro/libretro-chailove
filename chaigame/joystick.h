#ifndef _JOYSTICK_H_INCLUDED_
#define _JOYSTICK_H_INCLUDED_

#include "src/Joystick.h"
#include <SDL.h>

namespace chaigame {
	class joystick {
	public:
		void load();
		void update();
		Joystick* getJoysticks();
		Joystick* joysticks;
		int getNumJoysticks();
		int numJoysticks = 0;
		bool isOpen(int index);
		void close(int index);
		void unload();
		bool isDown(int index, int button);
		int getButtonKey(std::string name);
	};
}

#endif
