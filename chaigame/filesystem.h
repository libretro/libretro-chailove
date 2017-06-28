#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <SDL.h>

namespace chaigame {
	class filesystem {
	public:
		bool load(std::string file);
		bool unload();
		SDL_RWops* openRW(std::string filename);
		char* readChar(std::string filename);
		std::string read(std::string filename);

		bool mount(const char* archive, const char* mountpoint);
	};
}

#endif
