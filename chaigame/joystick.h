#ifndef _JOYSTICK_H_INCLUDED_
#define _JOYSTICK_H_INCLUDED_

#include "src/Joystick.h"
#include "SDL.h"
#include <string>

namespace chaigame {
	class joystick {
	public:
		void load();
		void update();
		Joystick* getJoysticks();
		Joystick* joysticks;
		int getJoystickCount();
		int numJoysticks = 0;
		bool isOpen(int index);
		void close(int index);
		void unload();
		bool isDown(int index, int button);
		bool isDown(int index, const std::string& button);
		int getButtonKey(const std::string& name);
		int16_t joystick_cache[4][14];

		Joystick& operator[](int i);
	};
}

#endif
