#include "Joystick.h"
#include "SDL.h"
#include "../../ChaiLove.h"
#include <string>

namespace chailove {
	std::string Joystick::getName() {
		return name;
	}

	/*Joystick::Joystick(SDL_Joystick* joystick) {
		joy = joystick;
	}*/

	/*Joystick::Joystick(int num, SDL_Joystick* joystick) {
		index = index;
		joy = joystick;
	}*/

	bool Joystick::isOpen() {
		//return joy != NULL;
		return true;
	}

	bool Joystick::open(int i) {
		//SDL_Joystick* sdlJoystick = SDL_JoystickOpen(i);
		//joy = sdlJoystick;
		index = i;
		name = "RetroPad";
		return true;
	}

	Joystick::Joystick() {
	}

	bool Joystick::isDown(int button) {
		return (bool)ChaiLove::getInstance()->joystick.joystick_cache[index][button];

		// TODO: Switch from libretro joysticks to SDL.
		/*if (joy) {
			Uint8 state = SDL_JoystickGetButton(joy, button);
			return state == 1;
		}
		return false;*/
	}

	bool Joystick::isDown(const std::string& button) {
		int key = ChaiLove::getInstance()->joystick.getButtonKey(button);
		return isDown(key);
	}

	void Joystick::close() {
		/*if (joy) {
	        //SDL_JoystickClose(joy);
		    joy = NULL;
		}*/
	}
}
