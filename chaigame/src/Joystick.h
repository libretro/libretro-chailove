#ifndef _SRCJOYSTICK_H_INCLUDED_
#define _SRCJOYSTICK_H_INCLUDED_

#include "SDL.h"
#include <string>

namespace chaigame {
	class Joystick {
	public:
		Joystick(int num, SDL_Joystick* joystick);
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
		Sint16 xaxis;
		Sint16 yaxis;
	};
}

#endif
