#include <physfs.h>
#include <string>

#include "filesystem.h"
#include "vendor/physfs/extras/physfsrwops.h"
#include "vendor/filesystem/filesystem/path.h"
#include "../Application.h"

#include <iostream>

using namespace filesystem;

namespace chaigame {

	bool filesystem::init(const std::string& file) {
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

	bool filesystem::load(const std::string& file) {
		Application* app = Application::getInstance();
		return app->script->loadModule(file);
	}

	bool filesystem::exists(const std::string& file) {
		return PHYSFS_exists(file.c_str()) != 0;
	}

	int filesystem::getSize(const std::string& file) {
		PHYSFS_File* openfile = PHYSFS_openRead(file.c_str());
		int size = -1;
		if (openfile) {
			size = PHYSFS_fileLength(openfile);
			PHYSFS_close(openfile);
		}
		return size;
	}

	bool filesystem::unload() {
		PHYSFS_deinit();
		return true;
	}

	SDL_RWops* filesystem::openRW(const std::string& filename) {
		SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
		if (rw != NULL) {
			return rw;
		}
		printf("Error loading file: %s", filename.c_str());
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
		char* myBuf = readChar(filename);
		// Construct a new string with the correct size.
		std::string contents(myBuf, strlen(myBuf));
		std::cout << contents;
		return contents;
	}

	bool filesystem::mount(const std::string& archive, const std::string& mountpoint) {
		int returnValue = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), 0);
		return returnValue != 0;
	}
}
