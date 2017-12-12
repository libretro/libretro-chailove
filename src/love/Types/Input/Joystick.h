#ifndef SRC_LOVE_TYPES_INPUT_JOYSTICK_H_
#define SRC_LOVE_TYPES_INPUT_JOYSTICK_H_

#include <string>

namespace love {
namespace Types {
namespace Input {

/**
 * @brief Represents a physical joystick.
 */
class Joystick {
	public:
	Joystick();
	Joystick(int index);

	/**
	 * @brief Gets the name of the joystick.
	 *
	 * @return string The name of the Joystick.
	 */
	std::string getName();
	bool isOpen();
	void close();

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

	int index = 0;
	std::string name;
	int xaxis;
	int yaxis;
};

}  // namespace Input
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_INPUT_JOYSTICK_H_
