#ifndef CHAILOVE_KEYBOARD_H
#define CHAILOVE_KEYBOARD_H

#include <string>
#include <map>
#include "SDL.h"

namespace chailove {
	/**
	 * @brief Provides an interface to the user's keyboard.
	 */
	class keyboard {
	public:
		Uint8* keys;
		bool load();
		/**
		 * @brief Checks whether a certain key is down.
		 */
		bool isDown(const std::string& key);
		/**
		 * @brief Checks whether a certain key is down.
		 */
		bool isDown(int key);
		/**
		 * @brief Enables or disables key repeat for love.keypressed.
		 */
		void setKeyRepeat(int delay = 400, int interval = 30);
		bool update();
		int getKeyCodeFromName(const std::string& name);

		std::map<std::string, int> keyCodes;
	};
}

#endif
