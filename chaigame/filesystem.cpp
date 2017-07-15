#include "physfs.h"
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
		PHYSFS_sint64 size = -1;
		if (openfile) {
			size = getSize(openfile);
			PHYSFS_close(openfile);
		}
		return (int)size;
	}

	PHYSFS_sint64 filesystem::getSize(PHYSFS_File* file) {
		PHYSFS_sint64 size = -1;
		if (file) {
			size = PHYSFS_fileLength(file);
			if (size < 0) {
				log()->error("Could not get size of file: {}", PHYSFS_getLastError());
				return -1;
			}
		}
		else {
			log()->error("The file is not open: {}", PHYSFS_getLastError());
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
			log()->error("Error loading file {}: {} {}", filename.c_str(), PHYSFS_getLastError(), SDL_GetError());
		}
		return rw;
	}

	char* filesystem::readChar(const std::string& filename) {
		char* output = NULL;
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		if (myfile == NULL) {
			log()->error("Error opening file {}: {}", filename.c_str(), PHYSFS_getLastError());
			return NULL;
		}

		PHYSFS_sint64 file_size = getSize(myfile);
		if (file_size > 0) {
			output = new char[file_size + 1];
			int length_read = PHYSFS_readBytes(myfile, output, file_size);
			if (length_read != file_size) {
				log()->error("File System error while reading from file {}: {}", filename.c_str(), PHYSFS_getLastError());
				output = NULL;
			}
			// Make sure there is a null terminating character at the end of the string.
			output[file_size] = '\0';
		}
		else {
			log()->error("Error getting filesize of {}: {}", filename.c_str(), PHYSFS_getLastError());
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
