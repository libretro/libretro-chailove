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
		else {
			printf("Error getting size of file %s: %s", file.c_str(), PHYSFS_getLastError());
		}
		return size;
	}

	bool filesystem::unload() {
		PHYSFS_deinit();
		return true;
	}

	SDL_RWops* filesystem::openRW(const std::string& filename) {
		SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
		if (rw == NULL) {
			printf("Error loading file %s: %s", filename.c_str(), PHYSFS_getLastError());
		}
		return rw;
	}

	char* filesystem::readChar(const std::string& filename) {
		std::cout << "script file: " << filename << std::endl;
		char *output = NULL;
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		if (myfile == NULL) {
			printf("Error opening file %s: %s\n", filename.c_str(), PHYSFS_getLastError());
			return NULL;
		}

		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);
		if (file_size > 0) {
			output = new char[file_size + 1];
			int length_read = PHYSFS_readBytes(myfile, output, file_size);
			if (length_read != file_size) {
				printf("File System error while reading from file %s: %s\n", filename.c_str(), PHYSFS_getLastError());
			}
		}
		else {
			printf("Error getting filesize of %s: %s\n", filename.c_str(), PHYSFS_getLastError());
		}

		PHYSFS_close(myfile);
		return output;
	}

	std::string filesystem::read(const std::string& filename) {
		// Retrieve a character buffer.
		char* myBuf = readChar(filename);
		if (myBuf == NULL) {
			return std::string("");
		}
		return std::string(myBuf);
	}

	bool filesystem::mount(const std::string& archive, const std::string& mountpoint) {
		int returnValue = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), 0);
		return returnValue != 0;
	}
}
