#ifndef _WINDOW_H_INCLUDED_
#define _WINDOW_H_INCLUDED_

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
