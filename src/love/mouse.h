#ifndef SRC_LOVE_MOUSE_H_
#define SRC_LOVE_MOUSE_H_

#include <string>
#include "Types/Graphics/Point.h"
#include "libretro.h"

namespace love {

/**
 * @brief Provides an interface to the user's mouse.
 */
class mouse {
	public:
	bool load();

	/**
	 * @brief Returns the current x-position of the mouse.
	 *
	 * @return The position of the mouse along the x-axis.
	 *
	 * @see love.mouse.setX
	 */
	int getX();

	/**
	 * @brief Returns the current y-position of the mouse.
	 *
	 * @return The position of the mouse along the y-axis.
	 *
	 * @see love.mouse.setY
	 */
	int getY();

	/**
	 * @brief Returns the current position of the mouse.
	 */
	Types::Graphics::Point getPosition();

	/**
	 * @brief Checks whether a certain button is down.
	 *
	 * @param button The index of a button to check. 1 is the primary mouse button, 2 is the secondary mouse button and 3 is the middle button. Further buttons are mouse dependant.
	 *
	 * @return True if the specified button is down.
	 */
	bool isDown(int button);

	/**
	 * @brief Checks whether a certain button is down.
	 *
	 * @param button The mouse button to check. "left", "middle", "right", etc.
	 *
	 * @return True if the specified button is down.
	 */
	bool isDown(const std::string& button);

	void update();

	int getButtonKey(const std::string& button);
	std::string getButtonName(int button);

	int16_t m_x, m_y;
	int16_t buttonState[RETRO_DEVICE_ID_MOUSE_BUTTON_5];

	void mousemoved(int x, int y, int dx, int dy);
	void mousepressed(int x, int y, const std::string& button);
	void mousereleased(int x, int y, const std::string& button);
};

}  // namespace love

#endif  // SRC_LOVE_MOUSE_H_
