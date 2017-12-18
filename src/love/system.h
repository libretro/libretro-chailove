#ifndef SRC_LOVE_SYSTEM_H_
#define SRC_LOVE_SYSTEM_H_

#include <vector>
#include <string>

namespace love {
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
	 *
	 * @return A vector, with the major being the first element, minor being the second, and patch being the third.
	 */
	std::vector<int> getVersion();

	/**
	 * @brief Retreves the running ChaiLove version, as a string.
	 *
	 * @return A string representing ChaiLove's version. Example: 1.3.2
	 */
	std::string getVersionString();
};

}  // namespace love

#endif  // SRC_LOVE_SYSTEM_H_
