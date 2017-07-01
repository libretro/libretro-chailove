#ifndef _SRCJOYSTICK_H_INCLUDED_
#define _SRCJOYSTICK_H_INCLUDED_

#include <SDL.h>
#include <string>

namespace chaigame {
	class Joystick {
	public:
		Joystick(int num, SDL_Joystick* joystick);
		Joystick(SDL_Joystick* joystick);
		Joystick();
		~Joystick();
		std::string getName();
		bool isOpen();
		void close();
		bool open(int index);

		bool isDown(int button);
		bool isDown(std::string button);

		int num = 0;

		SDL_Joystick* joy = NULL;
		int index = 0;
		std::string name;
	};
}

#endif
