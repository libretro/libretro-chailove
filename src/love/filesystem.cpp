#include <string>
#include <iostream>

#include "libretro.h"
#include "physfs.h"
#include "filesystem.h"
#include "physfsrwops.h"
#include "filesystem/path.h"
#include "../ChaiLove.h"
#include "Types/FileSystem/FileInfo.h"

using love::Types::FileSystem::FileInfo;

namespace love {

/**
 * Initialize the file system.
 */
bool filesystem::init(const std::string& file) {
	if (PHYSFS_isInit() == 0) {
		// Initialize PhysFS
		if (PHYSFS_init(NULL) == 0) {
			std::cout << "[ChaiLove] [filesystem] Error loading PhysFS - " << getLastError() << std::endl;
			return false;
		}
	}

	// Check if we are simply running ChaiLove.
	if (file.empty()) {
		return mount(".", "/");
	}

	// Find the parent and extension of the given file.
	::filesystem::path p(file.c_str());
	std::string extension(p.extension());
	::filesystem::path parent(p.parent_path());
	std::string parentPath(parent.str());

	// Allow loading from an Archive.
	if (extension == "chaigame" || extension == "chailove" || extension == "zip") {
		return mount(file.c_str(), "/");
	}

	// If we are just running the cour, load the base path.
	if (parentPath.empty()) {
		return mount(".", "/");
	}

	// Otherwise, we are loading a .chai file directly. Load it.
	return mount(parentPath.c_str(), "/");
}

void filesystem::mountlibretro() {
	// Mount some of the libretro directories.
	const char *system_dir = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir) {
		mount(system_dir, "libretro/system");
	}
	const char *content_dir = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_CORE_ASSETS_DIRECTORY, &content_dir) && content_dir) {
		mount(content_dir, "libretro/assets");
	}
	const char *save_dir = NULL;
	if (ChaiLove::environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir) {
		save_dir = *save_dir ? save_dir : system_dir;
		mount(save_dir, "libretro/saves");
	} else {
		mount(save_dir = system_dir, "libretro/saves");
	}

	// Ensure the write directory is set to the Save Directory.
	PHYSFS_setWriteDir(save_dir);
}

bool filesystem::load(const std::string& file) {
	return ChaiLove::getInstance()->script->loadModule(file);
}

bool filesystem::exists(const std::string& file) {
	return PHYSFS_exists(file.c_str()) > 0;
}

int filesystem::getSize(const std::string& file) {
	PHYSFS_File* openfile = PHYSFS_openRead(file.c_str());
	PHYSFS_sint64 size = -1;
	if (openfile) {
		size = getSize(openfile);
		PHYSFS_close(openfile);
	}
	return static_cast<int>(size);
}

PHYSFS_sint64 filesystem::getSize(PHYSFS_File* file) {
	PHYSFS_sint64 size = -1;
	if (file) {
		size = PHYSFS_fileLength(file);
		if (size < 0) {
			std::cout << "[ChaiLove] [filesystem] Could not get size of file " << getLastError() << std::endl;
			return -1;
		}
	} else {
		std::cout << "[ChaiLove] [filesystem] The file is not currently open." << std::endl;
	}
	return size;
}

bool filesystem::unload() {
	if (PHYSFS_isInit() != 0) {
		PHYSFS_deinit();
	}
	return true;
}

SDL_RWops* filesystem::openRW(const std::string& filename) {
	SDL_RWops* rw = PHYSFSRWOPS_openRead(filename.c_str());
	if (rw == NULL) {
		const char* errorChar = SDL_GetError();
		std::string sdlErr("");
		if (errorChar != NULL) {
			sdlErr = errorChar;
		}

		std::cout << "[ChaiLove] [filesystem] Error loading file " << filename << getLastError() << sdlErr << std::endl;
	}
	return rw;
}

PHYSFS_file* filesystem::openFile(const std::string& filename) {
	PHYSFS_file* myfile = PHYSFS_openRead(filename.c_str());
	if (myfile == NULL) {
		std::cout << "[ChaiLove] [filesystem] Error opening file " << filename << getLastError() << std::endl;
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
			std::cout << "[ChaiLove] [filesystem] File System error while reading from file " << filename << getLastError() << std::endl;
			output = NULL;
		} else {
			// Make sure there is a null terminating character at the end of the string.
			output[file_size] = '\0';
		}
	} else {
		std::cout << "[ChaiLove] [filesystem] Error getting filesize of " << filename << getLastError() << std::endl;
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


bool filesystem::unmount(const std::string& archive) {
	std::cout << "[filesystem] Unmounting " << archive << std::endl;
	int returnValue = PHYSFS_unmount(archive.c_str());
	if (returnValue == 0) {
		std::cout << "[ChaiLove] [filesystem] Error unmounting: " << getLastError() << std::endl;
		return false;
	}
	return true;
}

bool filesystem::mount(const std::string& archive, const std::string& mountpoint) {
	std::cout << "[ChaiLove] [filesystem] Mounting " << archive << " as " << mountpoint << std::endl;
	int returnValue = PHYSFS_mount(archive.c_str(), mountpoint.c_str(), 0);
	if (returnValue == 0) {
		std::cout << "[ChaiLove] [filesystem] Error mounting: " << getLastError() << std::endl;
		return false;
	}
	return true;
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
	} else {
		std::cout << "[ChaiLove] [filesystem] Error enumerating files from " << dir << std::endl;
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

bool filesystem::isSymlink(const std::string& filename) {
	PHYSFS_Stat stat;
	if (PHYSFS_stat(filename.c_str(), &stat) == 0) {
		return false;
	}
	return stat.filetype == PHYSFS_FILETYPE_SYMLINK;
}

std::vector<std::string> filesystem::lines(const std::string& filename) {
	return lines(filename, "\n");
}

std::vector<std::string> filesystem::lines(const std::string& filename, const std::string& delimiter) {
	std::string str = read(filename);
	std::vector<std::string> strings;

	if (!str.empty()) {
		std::string::size_type pos = 0;
		std::string::size_type prev = 0;
		while ((pos = str.find(delimiter, prev)) != std::string::npos) {
			strings.push_back(str.substr(prev, pos - prev));
			prev = pos + 1;
		}

		// To get the last substring (or only, if delimiter is not found)
		strings.push_back(str.substr(prev));
	}

	return strings;
}

FileInfo filesystem::getInfo(const std::string& path) {
	FileInfo fileInfo;
	PHYSFS_Stat stat;
	if (PHYSFS_stat(path.c_str(), &stat) == 0) {
		return fileInfo;
	}
	switch(stat.filetype) {
		case PHYSFS_FILETYPE_REGULAR:
			fileInfo.type = "file";
			break;
		case PHYSFS_FILETYPE_DIRECTORY:
			fileInfo.type = "directory";
			break;
		case PHYSFS_FILETYPE_SYMLINK:
			fileInfo.type = "symlink";
			break;
		default:
			fileInfo.type = "other";
			break;
	}

	fileInfo.modtime = stat.modtime;
	fileInfo.size = stat.filesize;
	return fileInfo;
}

bool filesystem::createDirectory(const std::string& name) {
	int ret = PHYSFS_mkdir(name.c_str());
	if (ret == 0) {
		std::cout << "[ChaiLove] [filesystem] Failed to create directory: " << getLastError() << std::endl;
		return false;
	}
	return true;
}

bool filesystem::write(const std::string& name, const std::string& data) {
	PHYSFS_File* file = PHYSFS_openWrite(name.c_str());
	if (file == NULL) {
		std::cout << "[ChaiLove] [filesystem] Error opening file for writing: " << getLastError() << std::endl;
		return false;
	}
	const char* buffer = data.c_str();
	int bytesWritten = PHYSFS_writeBytes(file, (const void*)buffer, data.size());
	return bytesWritten >= 0;
}

std::string filesystem::getLastError() {
	const char* charErr = PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
	if (charErr) {
		return std::string(charErr);
	}
	return "";
}

}  // namespace love
