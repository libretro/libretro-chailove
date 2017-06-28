#include <physfs.h>
#include <string>

#include "filesystem.h"
#include "vendor/physfs/extras/physfsrwops.h"
#include "vendor/filesystem/filesystem/path.h"

using namespace filesystem;

namespace chaigame {

	bool filesystem::load(const std::string& file) {
		PHYSFS_init(NULL);

		// Check if we are simply running the application.
		if (file.empty()) {
			return mount(".", "/");
		}

		// Find the parent and extension of the given file.
		path p(file.c_str());
		std::string extension(p.extension());
		path parent(p.parent_path());
		std::string parentPath(parent.str());

		// Allow loading from an Archive.
		if (extension == "chaigame") {
			return mount(file.c_str(), "/");
		}

		if (parentPath.empty()) {
			return mount(".", "/");
		}

		return mount(parentPath.c_str(), "/");
	}

	bool filesystem::unload() {
		PHYSFS_deinit();
	}

	SDL_RWops* filesystem::openRW(const std::string& filename) {
		SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
		if (rw != NULL) {
			return rw;
		}
		// TODO: Add error reporting.
		return NULL;
	}

	char* filesystem::readChar(const std::string& filename) {
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);

		char *myBuf = new char[file_size];
		int length_read = PHYSFS_readBytes(myfile, myBuf, file_size);
		PHYSFS_close(myfile);
		return myBuf;
	}

	std::string filesystem::read(const std::string& filename) {
		char *myBuf = readChar(filename);
		std::string contents(myBuf);
		return contents;
	}

	bool filesystem::mount(const std::string& archive, const std::string& mountpoint) {
		int returnValue = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), 0);
		return returnValue != 0;
	}
}
