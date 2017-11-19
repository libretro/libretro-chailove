#ifndef CHAILOVE_SYSTEM_H
#define CHAILOVE_SYSTEM_H

#include <string>

namespace chailove {
	/**
	 * @brief Provides access to information about the user's system.
	 */
	class system {
	public:
		/**
		 * @brief Gets the current operating system.
		 */
		std::string getOS();
	};
}

#endif
