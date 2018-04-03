#ifndef SRC_LOVE_WINDOW_H_
#define SRC_LOVE_WINDOW_H_

#include <string>
#include "config.h"
#include "Types/Graphics/Point.h"

using love::Types::Graphics::Point;

namespace love {

/**
 * @brief Provides an interface for modifying and retrieving information about the program's window.
 */
class window {
	public:
	bool load(const config& conf);
	bool unload();

	/**
	 * @brief Gets the window title.
	 *
	 * @return The current window title.
	 *
	 * @see love.window.setTitle
	 */
	std::string getTitle();

	/**
	 * @brief Sets the window title.
	 *
	 * @param title The new window title.
	 *
	 * @see love.window.getTitle
	 */
	window& setTitle(std::string title);

	/**
	 * @brief Display a simple message for a certain amount of frames.
	 *
	 * @param msg The message text to be displayed.
	 * @param frames (4000) The amount of frames to display the message.
	 */
	void showMessageBox(const std::string& msg, int frames);
	void showMessageBox(const std::string& msg);
};

}  // namespace love

#endif  // SRC_LOVE_WINDOW_H_
