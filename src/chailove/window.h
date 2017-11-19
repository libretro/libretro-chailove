#ifndef CHAILOVE_WINDOW_H
#define CHAILOVE_WINDOW_H

#include <string>
#include "system/Config.h"

namespace chailove {
	/**
	 * @brief Provides an interface for modifying and retrieving information about the program's window.
	 */
	class window {
	public:
		bool load(Config& config);
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
}

#endif
