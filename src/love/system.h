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
	 *
	 * @return The current operating system. "OS X", "Windows", "Linux", "Android" or "iOS".
	 */
	std::string getOS();

	/**
	 * @brief Retreves the running ChaiLove version information.
	 *
	 * @return A vector, with the major being the first element, minor being the second, and patch being the third.
	 *
	 * @see love.system.getVersionString
	 */
	std::vector<int> getVersion();

	/**
	 * @brief Retreves the running ChaiLove version, as a string.
	 *
	 * @return A string representing ChaiLove's version. Example: 1.3.2
	 *
	 * @see love.system.getVersion
	 */
	std::string getVersionString();

	/**
	 * @brief Display a message for a certain amount of frames.
	 *
	 * @param msg The message text to be displayed.
	 * @param frames (3000) The amount of frames to display the message.
	 */
	void message(const std::string& msg, int frames);
	void message(const std::string& msg);
};

}  // namespace love

#endif  // SRC_LOVE_SYSTEM_H_
