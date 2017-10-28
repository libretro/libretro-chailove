#ifndef CHAILOVE_WINDOW_H
#define CHAILOVE_WINDOW_H

#include <string>
#include "system/Config.h"

namespace chailove {
	class window {
	public:
		bool load(Config& config);
		bool unload();

		std::string getTitle();
		void setTitle(std::string title);
	};
}

#endif
