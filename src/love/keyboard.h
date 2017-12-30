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
	 *
	 * @param key The key to check.
	 *
	 * @return True if the key is down, false if not.
	 */
	bool isDown(const std::string& key);

	/**
	 * @brief Checks whether a certain key is down.
	 *
	 * @param key The key scancode to check.
	 *
	 * @return True if the key is down, false if not.
	 */
	bool isDown(int key);

	/**
	 * @brief Enables or disables key repeat for love.keypressed.
	 *
	 * @param delay Specifies how long the key must be pressed before it begins repeating.
	 * @param interval Once the key is repeating, it is repeated by the given interval.
	 *
	 * @return The keyboard module.
	 */
	keyboard& setKeyRepeat(int delay = 400, int interval = 30);
	bool update();

	/**
	 * @brief Retrieve a scancode from the given key.
	 *
	 * @see love.keyboard.getKeyFromScancode
	 */
	int getScancodeFromKey(const std::string& key);

	/**
	 * @brief Retrieve a key from the given scancode.
	 *
	 * @see love.keyboard.getScancodeFromKey
	 */
	std::string getKeyFromScancode(int scancode);

	std::map<std::string, int> keyCodes;

	void eventKeyPressed(SDLKey key);
	void eventKeyReleased(SDLKey key);
};

}  // namespace love

#endif  // SRC_LOVE_KEYBOARD_H_
