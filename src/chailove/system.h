#ifndef CHAILOVE_SYSTEM_H
#define CHAILOVE_SYSTEM_H

#include <vector>
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

		/**
		 * @brief Retreves the running ChaiLove version information.
		 */
		std::vector<int> getVersion();

		/**
		 * @brief Retreves the running ChaiLove version, as a string.
		 */
		std::string getVersionString();
	};
}

#endif
