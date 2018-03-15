#ifndef SRC_LOVE_CONFIG_H_
#define SRC_LOVE_CONFIG_H_

#include <map>
#include <string>

#include "Types/Config/ModuleConfig.h"
#include "Types/Config/WindowConfig.h"

using love::Types::Config::ModuleConfig;
using love::Types::Config::WindowConfig;

namespace love {

/**
 * @brief The configuration object for ChaiLove.
 *
 * This is set through the `conf` callback:
 *
 * @code
 * def conf(t) {
 *   t.identity = "mygame"
 *   t.window.width = 1024
 *   t.window.height = 768
 *   t.console = false
 * }
 * @endcode
 */
class config {
	public:
	config();

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
	WindowConfig window;

	/**
	 * @brief Enable or disable modules.
	 */
	ModuleConfig modules;

	/**
	 * @brief Generic map of boolean configuration options.
	 *
	 * Available options:
	 * - "alphablending": true
	 * - "highquality": true
	 */
	std::map<std::string, bool> options;

	/**
	 * @brief Attach the in-game console.
	 *
	 * When `t.console = true`, will allow use of the in-game console. Use the tilde key to show.
	 *
	 * @see love.console
	 */
	bool console = false;
};

}  // namespace love

#endif  // SRC_LOVE_CONFIG_H_
