#ifndef CHAILOVE_UTILITY_CONFIG_H
#define CHAILOVE_UTILITY_CONFIG_H

#include <string>
#include <map>

namespace Types {
	namespace System {
	struct windowConfig {
		int width = 800;
		int height = 600;
		int bbp = 32;
		std::string title = "ChaiLove";
		bool asyncblit = true;
		bool hwsurface = true;
		bool doublebuffering = true;
	};

	struct moduleConfig {
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
}
}
#endif
