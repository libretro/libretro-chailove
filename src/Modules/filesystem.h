#ifndef CHAILOVE_FILESYSTEM_H
#define CHAILOVE_FILESYSTEM_H

#include <string>
#include <vector>
#include "SDL.h"
#include "physfs.h"

namespace Modules {
	/**
	 * @brief Provides an interface to the user's filesystem.
	 */
	class filesystem {
	public:
		/**
		 * @brief Loads and runs a .chai file.
		 */
		bool load(const std::string& file);
		bool init(const std::string& file);
		bool unload();
		SDL_RWops* openRW(const std::string& filename);
		char* readChar(const std::string& filename);
		/**
		 * @brief Read the contents of a file.
		 */
		std::string read(const std::string& filename);
		/**
		 * @brief Check whether a file or directory exists.
		 */
		bool exists(const std::string& file);
		/**
		 * @brief Get the size in bytes of a file.
		 */
		int getSize(const std::string& file);

		/**
		 * @brief Unmounts a zip file or folder previously mounted with filesystem::unmount.
		 */
		bool unmount(const std::string& archive);
		/**
		 * @brief Mounts a zip file or folder in the game's save directory for reading.
		 */
		bool mount(const std::string& archive, const std::string& mountpoint);
		PHYSFS_sint64 getSize(PHYSFS_File* file);
		PHYSFS_file* openFile(const std::string& filename);

		/**
		 * @brief Returns all files and subdirectories in the directory.
		 */
		std::vector<std::string> getDirectoryItems(const std::string& dir);
		/**
		 * @brief Check whether something is a directory.
		 */
		bool isDirectory(const std::string& filename);
		/**
		 * @brief Checks whether something is a file.
		 */
		bool isFile(const std::string& filename);
		/**
		 * @brief Iterate over the lines in a file.
		 */
		std::vector<std::string> lines(const std::string& filename);
		/**
		 * @brief Iterate over the lines in a file, with the given delimiter.
		 */
		std::vector<std::string> lines(const std::string& filename, const std::string& delimiter);
	};
}

#endif
