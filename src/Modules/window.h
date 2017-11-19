#ifndef CHAILOVE_WINDOW_H
#define CHAILOVE_WINDOW_H

#include <string>
#include "../Types/System/Config.h"

using Types::System::Config;
using std::string;

namespace Modules {
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
		string getTitle();

		/**
		 * @brief Sets the window title.
		 */
		void setTitle(string title);
	};
}

#endif
