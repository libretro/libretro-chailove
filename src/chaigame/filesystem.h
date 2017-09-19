#ifndef CHAIGAME_FILESYSTEM_H
#define CHAIGAME_FILESYSTEM_H

#include <string>
#include <vector>
#include "SDL.h"
#include "physfs.h"

namespace chaigame {
	class filesystem {
	public:
		bool load(const std::string& file);
		bool init(const std::string& file);
		bool unload();
		SDL_RWops* openRW(const std::string& filename);
		char* readChar(const std::string& filename);
		std::string read(const std::string& filename);
		bool exists(const std::string& file);
		int getSize(const std::string& file);
		bool mount(const std::string& archive, const std::string& mountpoint);
		PHYSFS_sint64 getSize(PHYSFS_File* file);
		PHYSFS_file* openFile(const std::string& filename);
		std::vector<std::string> getDirectoryItems(const std::string& dir);
		bool isDirectory(const std::string& filename);
		bool isFile(const std::string& filename);
	};
}

#endif
