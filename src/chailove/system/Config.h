#ifndef CHAILOVE_UTILITY_CONFIG_H
#define CHAILOVE_UTILITY_CONFIG_H

#include <string>
#include <map>

namespace chailove {
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

	class Config {
	public:
		Config();
		std::string identity = "chailove";
		std::string version;
		windowConfig window;
		moduleConfig modules;
		std::map<std::string, bool> options;
	};
}

#endif
