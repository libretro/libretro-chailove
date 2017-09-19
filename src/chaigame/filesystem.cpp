#include "physfs.h"
#include <string>

#include "filesystem.h"
#include "vendor/physfs/extras/physfsrwops.h"
#include "vendor/filesystem/filesystem/path.h"
#include "../Game.h"
#include "log.h"

#include <iostream>

using namespace filesystem;

namespace chaigame {

	bool filesystem::init(const std::string& file) {
		PHYSFS_init(NULL);

		// Check if we are simply running the Game.
		if (file.empty()) {
			return mount(".", "/");
		}

		// Find the parent and extension of the given file.
		path p(file.c_str());
		std::string extension(p.extension());
		path parent(p.parent_path());
		std::string parentPath(parent.str());

		// Allow loading from an Archive.
		if (extension == "chaigame" || extension == "zip") {
			return mount(file.c_str(), "/");
		}

		if (parentPath.empty()) {
			return mount(".", "/");
		}

		return mount(parentPath.c_str(), "/");
	}

	bool filesystem::load(const std::string& file) {
		Game* app = Game::getInstance();
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
				const char* errorChar = PHYSFS_getLastError();
				std::string physErr("");
				if (errorChar != NULL) {
					physErr = errorChar;
				}
				log()->error("Could not get size of file: {}", physErr);
				return -1;
			}
		}
		else {
			log()->error("The file is not open.");
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
			const char* errorChar = PHYSFS_getLastError();
			std::string physErr("");
			if (errorChar != NULL) {
				physErr = errorChar;
			}

			errorChar = SDL_GetError();
			std::string sdlErr("");
			if (errorChar != NULL) {
				sdlErr = errorChar;
			}

			log()->error("Error loading file {}: {} {}", filename, physErr, sdlErr);
		}
		return rw;
	}

	PHYSFS_file* filesystem::openFile(const std::string& filename) {
		PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
		if (myfile == NULL) {
			const char* errorChar = PHYSFS_getLastError();
			std::string physErr("");
			if (errorChar != NULL) {
				physErr = errorChar;
			}
			log()->error("Error opening file {}: {}", filename, physErr);
			return NULL;
		}
		return myfile;
	}

	char* filesystem::readChar(const std::string& filename) {
		char* output = NULL;
		PHYSFS_file* myfile = openFile(filename);
		if (myfile == NULL) {
			return NULL;
		}

		PHYSFS_sint64 file_size = getSize(myfile);
		if (file_size > 0) {
			output = new char[file_size + 1];
			int length_read = PHYSFS_readBytes(myfile, output, file_size);
			if (length_read != file_size) {
				const char* errorChar = PHYSFS_getLastError();
				std::string physErr("");
				if (errorChar != NULL) {
					physErr = errorChar;
				}
				log()->error("File System error while reading from file {}: {}", filename, physErr);
				output = NULL;
			}
			// Make sure there is a null terminating character at the end of the string.
			output[file_size] = '\0';
		}
		else {
			std::string physErr = PHYSFS_getLastError();
			log()->error("Error getting filesize of {}: {}", filename, physErr);
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

	/**
	 * Lists all items in the given directory.
	 */
	std::vector<std::string> filesystem::getDirectoryItems(const std::string& dir) {
		// Construct the list of files that will result.
		std::vector<std::string> result;

		// Ask PhysFS for the enumerated files.
		char** rc = PHYSFS_enumerateFiles(dir.c_str());
		if (rc != NULL) {
			char **i;
			for (i = rc; *i != NULL; i++) {
				// Build the file string.
				std::string thefile(*i);
				result.push_back(thefile);
			}
			PHYSFS_freeList(rc);
		}
		else {
			log()->warn("Error enumerating files from {}", dir);
		}

		return result;
	}

	bool filesystem::isDirectory(const std::string& filename) {
		PHYSFS_Stat stat;
		if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
			return false;
		}
		return stat.filetype == PHYSFS_FILETYPE_DIRECTORY;
	}

	bool filesystem::isFile(const std::string& filename) {
		PHYSFS_Stat stat;
		if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
			return false;
		}
		return stat.filetype == PHYSFS_FILETYPE_REGULAR;
	}
}
