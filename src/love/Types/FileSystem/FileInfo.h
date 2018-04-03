#ifndef SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_
#define SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_

#include <string>

namespace love {
namespace Types {
namespace FileSystem {

/**
 * @brief Information about a file.
 */
struct FileInfo {
	/**
	 * @brief Creates a basic FileInfo object, with no values set.
	 */
	FileInfo() : type(""), size(-1), modtime(-1) {
		// Nothing.
	}

	FileInfo(const std::string& theType) : type(theType), size(-1), modtime(-1) {
		// Nothing.
	}

	FileInfo(const std::string& theType, int theSize) : type(theType), size(theSize), modtime(-1) {
		// Nothing.
	}

	FileInfo(const std::string& theType, int theSize, int theModtime) : type(theType), size(theSize), modtime(theModtime) {
		// Nothing.
	}

	/**
	 * @brief The type of the object at the path (file, directory, symlink, empty, etc.).
	 */
	std::string type;

	/**
	 * @brief The size in bytes of the file, or -1 if it can't be determined.
	 */
	int size;

	/**
	 * @brief The file's last modification time in seconds since the unix epoch, or nil if it can't be determined.
	 */
	int modtime;
};

}  // namespace FileSystem
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_
