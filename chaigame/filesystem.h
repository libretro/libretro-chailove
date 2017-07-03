#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <SDL.h>

namespace chaigame {
	class filesystem {
	public:
		bool init(const std::string& file);
		bool unload();
		SDL_RWops* openRW(const std::string& filename);
		char* readChar(const std::string& filename);
		std::string read(const std::string& filename);
		bool exists(const std::string& file);
		int getSize(const std::string& file);
		bool mount(const std::string& archive, const std::string& mountpoint);
	};
}

#endif
