#ifndef SRC_LOVE_WINDOW_H_
#define SRC_LOVE_WINDOW_H_

#include <string>
#include "Types/System/Config.h"

namespace love {

/**
 * @brief Provides an interface for modifying and retrieving information about the program's window.
 */
class window {
	public:
	bool load(const Types::System::Config& config);
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
};

}  // namespace love

#endif  // SRC_LOVE_WINDOW_H_
