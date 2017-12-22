#ifndef SRC_LOVE_TYPES_SYSTEM_CONFIG_H_
#define SRC_LOVE_TYPES_SYSTEM_CONFIG_H_

#include <string>
#include <map>

namespace love {
namespace Types {
namespace System {

/**
 * @brief Configuration for how the application is set up.
 */
struct windowConfig {
	/**
	 * @brief The width of the screen.
	 */
	int width = 800;
	/**
	 * @brief The height of the screen.
	 */
	int height = 600;
	int bbp = 32;
	/**
	 * @brief The name of the application. Defaults to "ChaiLove".
	 */
	std::string title = "ChaiLove";
	bool asyncblit = true;
	bool hwsurface = true;
	bool doublebuffering = true;
};

/**
 * @brief Allows enabling or disiabling modules during initialization.
 */
struct moduleConfig {
	/**
	 * @brief Enable or disable the sound module.
	 */
	bool sound = true;
};

/**
 * @brief The configuration object for ChaiLove.
 */
class Config {
	public:
	Config();
	/**
	 * @brief The machine name of the project.
	 */
	std::string identity = "chailove";

	/**
	 * @brief The ChaiLove version the game was made on.
	 */
	std::string version;

	/**
	 * @brief The window configuration.
	 */
	windowConfig window;

	/**
	 * @brief Enable or disable modules.
	 */
	moduleConfig modules;

	/**
	 * @brief Generic map of boolean configuration options.
	 */
	std::map<std::string, bool> options;
};

}  // namespace System
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_SYSTEM_CONFIG_H_
