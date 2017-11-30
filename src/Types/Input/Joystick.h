#ifndef CHAILOVE_UTILITY_JOYSTICK_H
#define CHAILOVE_UTILITY_JOYSTICK_H

//#include "SDL.h"
#include <string>

namespace Types {
	namespace Input {
	/**
	 * @brief Represents a physical joystick.
	 */
	class Joystick {
	public:
		//Joystick(int num, SDL_Joystick* joystick);
		//Joystick(SDL_Joystick* joystick);
		Joystick();
		/**
		 * @brief Gets the name of the joystick.
		 *
		 * @return string The name of the Joystick.
		 */
		std::string getName();
		bool isOpen();
		void close();
		bool open(int index);

		/**
		 * @brief Checks if a button on the Joystick is pressed.
		 *
		 * @param button The index of the button to be checked
		 *
		 * @return bool Whether or not the given button is down.
		 */
		bool isDown(int button);
		/**
		 * @brief Checks if a button on the Joystick is pressed.
		 *
		 * @param button The button to be checked
		 *
		 * @return bool Whether or not the given button is down.
		 */
		bool isDown(const std::string& button);

		//L_Joystick* joy = NULL;
		int index = 0;
		std::string name;
		int xaxis;
		int yaxis;
	};
}
}
#endif
