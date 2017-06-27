#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <SDL.h>
#include <physfs.h>

namespace chaigame {
	class filesystem {
	public:
		bool load(std::string file);
		bool load();
		bool unload();
		SDL_RWops* openRW(std::string filename);
	};
}

#endif
