#ifndef CHAIGAME_UTILITY_CONFIG_H
#define CHAIGAME_UTILITY_CONFIG_H

#include <string>

namespace chaigame {
	struct windowConfig {
		int width = 800;
		int height = 600;
		int bbp = 32;
		std::string title = "ChaiGame";
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
		windowConfig window;
		moduleConfig modules;
	};
}

#endif
