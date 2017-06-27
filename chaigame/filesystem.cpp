
#include <physfs.h>
#include <string>

#include "filesystem.h"
#include "vendor/physfs/extras/physfsrwops.h"

namespace chaigame {

	bool filesystem::load() {
		std::string file = "";
		return load(file);
	}

	bool filesystem::load(std::string file) {

		PHYSFS_init(NULL);

		// TODO: Load the actual file's directory.
		mount(".", "/");
	}

	bool filesystem::unload() {
		PHYSFS_deinit();
	}

	SDL_RWops* filesystem::openRW(std::string filename) {
		SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
		if (rw != NULL) {
			return rw;
		}
		// TODO: Add error reporting.
		return NULL;
	}

	char* filesystem::readChar(std::string filename) {
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);

		char *myBuf = new char[file_size];
		int length_read = PHYSFS_readBytes(myfile, myBuf, file_size);
		PHYSFS_close(myfile);
		return myBuf;
	}

	std::string filesystem::read(std::string filename) {
		char *myBuf = readChar(filename);
		std::string contents(myBuf);
		return contents;
	}

	bool filesystem::mount(const char* archive, const char* mountpoint) {
		int returnValue = PHYSFS_mount(archive, mountpoint, 1);
		return returnValue != 0;
	}
}
