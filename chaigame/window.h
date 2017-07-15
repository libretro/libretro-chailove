#ifndef CHAIGAME_WINDOW_H
#define CHAIGAME_WINDOW_H

#include <string>
#include "src/Config.h"

namespace chaigame {
	class window {
	public:
		bool load(Config& config);
		bool unload();

		std::string getTitle();
		void setTitle(std::string title);
	};
}

#endif
