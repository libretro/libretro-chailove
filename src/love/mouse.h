#ifndef SRC_LOVE_MOUSE_H_
#define SRC_LOVE_MOUSE_H_

#include <SDL.h>
#include <string>
#include "Types/Graphics/Point.h"

namespace love {

/**
 * @brief Provides an interface to the user's mouse.
 */
class mouse {
	public:
	bool load();
	/**
	 * @brief Sets the current visibility of the cursor.
	 *
	 * @param visible True to set the cursor to visible, false to hide the cursor.
	 *
	 * @see love.mouse.getVisible
	 */
	mouse& setVisible(bool visible);

	/**
	 * @brief Checks if the cursor is visible.
	 *
	 * @return True if the cursor to visible, false if the cursor is hidden.
	 *
	 * @see love.mouse.setVisible
	 */
	bool isVisible();

	/**
	 * @brief Sets the current X position of the mouse.
	 *
	 * @param x The new position of the mouse along the x-axis.
	 *
	 * @return The mouse module.
	 */
	mouse& setX(int x);

	/**
	 * @brief Sets the current Y position of the mouse.
	 *
	 * @param y The new position of the mouse along the y-axis.
	 *
	 * @return The mouse module.
	 */
	mouse& setY(int y);

	/**
	 * @brief Returns the current x-position of the mouse.
	 *
	 * @return The position of the mouse along the x-axis.
	 */
	int getX();

	/**
	 * @brief Returns the current y-position of the mouse.
	 *
	 * @return The position of the mouse along the y-axis.
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

	int getButtonKey(const std::string& button);
	std::string getButtonName(int button);

	int m_x, m_y;
	int buttonState[20];

	void moveEvent(SDL_MouseMotionEvent event);
	void buttonEvent(SDL_MouseButtonEvent event);
};

}  // namespace love

#endif  // SRC_LOVE_MOUSE_H_
