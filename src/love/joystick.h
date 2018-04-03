#ifndef SRC_LOVE_JOYSTICK_H_
#define SRC_LOVE_JOYSTICK_H_

#include "Types/Input/Joystick.h"
#include "SDL.h"
#include <string>

using love::Types::Input::Joystick;

namespace love {

/**
 * Provides an interface to connected joysticks.
 */
class joystick {
	public:
	void load();
	void update();

	/**
	 * Gets a list of connected Joysticks.
	 */
	Joystick* getJoysticks();
	Joystick* joysticks;

	/**
	 * Gets the number of connected joysticks.
	 */
	int getJoystickCount();
	int numJoysticks = 0;

	/**
	 * Checks if the joystick is open.
	 */
	bool isOpen(int index);

	void clearCache();

	/**
	 * Closes a joystick.
	 */
	void close(int index);

	void unload();
	/**
	 * Checks if a button number is pressed on a joystick.
	 */
	bool isDown(int index, int button);

	/**
	 * Checks if a button is pressed on a joystick.
	 */
	bool isDown(int index, const std::string& button);

	int getButtonKey(const std::string& name);
	std::string getButtonName(int key);
	int16_t joystick_cache[4][14];

	/**
	 * Retrieve the given joystick.
	 *
	 * @code
	 * if (love.joystick[0].isDown("left")) {
	 *   love.graphics.print("Joystick is pushed LEFT", 100, 100)
	 * }
	 * @endcode
	 *
	 * @param player The number of which player's joystick you would like to retrieve.
	 *
	 * @return The joystick of the given player number.
	 */
	Joystick& operator[](int i);
};

}  // namespace love

#endif  // SRC_LOVE_JOYSTICK_H_
