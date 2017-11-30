#ifndef SRC_MODULES_MOUSE_H_
#define SRC_MODULES_MOUSE_H_

#include <SDL.h>
#include <string>
#include "../Types/Graphics/Point.h"

namespace Modules {

/**
 * @brief Provides an interface to the user's mouse.
 */
class mouse {
public:
	bool load();
	/**
	 * @brief Sets the current visibility of the cursor.
	 */
	void setVisible(bool enable);
	/**
	 * @brief Checks if the cursor is visible.
	 */
	bool isVisible();

	/**
	 * @brief Sets the current X position of the mouse.
	 */
	void setX(int x);
	/**
	 * @brief Sets the current Y position of the mouse.
	 */
	void setY(int y);
	/**
	 * @brief Returns the current x-position of the mouse.
	 */
	int getX();
	/**
	 * @brief Returns the current y-position of the mouse.
	 */
	int getY();
	/**
	 * @brief Returns the current position of the mouse.
	 */
	Types::Graphics::Point getPosition();

	/**
	 * @brief Checks whether a certain button is down.
	 */
	bool isDown(int button);
	/**
	 * @brief Checks whether a certain button is down.
	 */
	bool isDown(const std::string& button);
	int getButtonKey(const std::string& button);
	std::string getButtonName(int button);

	int m_x, m_y;
	int buttonState[20];

	void moveEvent(SDL_MouseMotionEvent event);
	void buttonEvent(SDL_MouseButtonEvent event);
};

}  // namespace Modules

#endif  // SRC_MODULES_MOUSE_H_
