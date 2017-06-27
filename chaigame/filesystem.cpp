
#include <physfs.h>

#include "filesystem.h"
#include <string>
#include "../Application.h"

namespace chaigame {
	bool filesystem::load(std::string file) {
		PHYSFS_init(NULL);
	}
	bool filesystem::unload() {
		PHYSFS_deinit();
	}

	/**
	 * TODO: Add rwops API
		SDL_RWops* rw;
		if ((rw=PHYSFSRWOPS_openRead(filepath.c_str()) == NULL)
		{
		    return false; //file doesn't exist
		}

		SDL_Surface* surface = IMG_Load_RW(rw, 0);

		SDL_FreeRW(rw);
	*/
}
