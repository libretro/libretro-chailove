#ifndef SRC_LOVE_KEYBOARD_H_
#define SRC_LOVE_KEYBOARD_H_

#include <string>
#include <map>
#include "SDL.h"

namespace love {
/**
 * @brief Provides an interface to the user's keyboard.
 */
class keyboard {
	public:
	Uint8* keys = NULL;
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

	/**
	 * @brief Retrieve a scancode from the given key.
	 */
	int getScancodeFromKey(const std::string& key);

	/**
	 * @brief Retrieve a key from the given scancode.
	 */
	std::string getKeyFromScancode(int scancode);

	std::map<std::string, int> keyCodes;

	void eventKeyPressed(SDLKey key);
	void eventKeyReleased(SDLKey key);
};

}  // namespace love

#endif  // SRC_LOVE_KEYBOARD_H_
