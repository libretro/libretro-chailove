#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <SDL.h>

namespace chaigame {
	class filesystem {
	public:
		bool load(const std::string& file);
		bool unload();
		SDL_RWops* openRW(const std::string& filename);
		char* readChar(const std::string& filename);
		std::string read(const std::string& filename);

		bool mount(const char* archive, const char* mountpoint);
	};
}

#endif
