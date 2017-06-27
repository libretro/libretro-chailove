#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <SDL.h>

namespace chaigame {
	class filesystem {
	public:
		bool load(std::string file);
		bool load();
		bool unload();
		SDL_RWops* openRW(std::string filename);
		char* openChar(std::string filename);
		std::string openString(std::string filename);
	};
}

#endif
