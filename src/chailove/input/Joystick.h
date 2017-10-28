#ifndef CHAILOVE_UTILITY_JOYSTICK_H
#define CHAILOVE_UTILITY_JOYSTICK_H

//#include "SDL.h"
#include <string>

namespace chailove {
	class Joystick {
	public:
		//Joystick(int num, SDL_Joystick* joystick);
		//Joystick(SDL_Joystick* joystick);
		Joystick();
		std::string getName();
		bool isOpen();
		void close();
		bool open(int index);

		bool isDown(int button);
		bool isDown(const std::string& button);

		//L_Joystick* joy = NULL;
		int index = 0;
		std::string name;
		int xaxis;
		int yaxis;
	};
}

#endif
