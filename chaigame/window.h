#ifndef _WINDOW_H_INCLUDED_
#define _WINDOW_H_INCLUDED_

#include <string>

namespace chaigame {
	class window {
	public:
		bool load();
		bool unload();

		std::string getTitle();
		void setTitle(std::string title);
	};
}

#endif
