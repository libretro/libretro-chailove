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
	 */
	std::map<std::string, bool> options;
};

}  // namespace love

#endif  // SRC_LOVE_CONFIG_H_
