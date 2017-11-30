#ifndef SRC_MODULES_WINDOW_H_
#define SRC_MODULES_WINDOW_H_

#include <string>
#include "../Types/System/Config.h"

namespace Modules {

/**
 * @brief Provides an interface for modifying and retrieving information about the program's window.
 */
class window {
	public:
	bool load(Types::System::Config& config);
	bool unload();

	/**
	 * @brief Gets the window title.
	 */
	std::string getTitle();

	/**
	 * @brief Sets the window title.
	 */
	void setTitle(std::string title);
};

}  // namespace Modules

#endif  // SRC_MODULES_WINDOW_H_
