#ifndef LIBRETRO_DATABASE_LIBRETRO_CHAILOVE_SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_
#define LIBRETRO_DATABASE_LIBRETRO_CHAILOVE_SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_

#include <string>

namespace love {
namespace Types {
namespace FileSystem {

/**
 * Information about a file.
 *
 * @see love.filesystem.getInfo
 */
struct FileInfo {
	/**
	 * Creates a basic FileInfo object, with no values set.
	 */
	FileInfo() : type(""), size(-1), modtime(-1) {
		// Nothing.
	}

	/**
	 * Creates a basic FileInfo object, with the given type.
	 */
	FileInfo(const std::string& theType) : type(theType), size(-1), modtime(-1) {
		// Nothing.
	}

	/**
	 * Creates a basic FileInfo object, with the type and size.
	 */
	FileInfo(const std::string& theType, int theSize) : type(theType), size(theSize), modtime(-1) {
		// Nothing.
	}

	/**
	 * Creates a basic FileInfo object, with the type, size and modtime.
	 */
	FileInfo(const std::string& theType, int theSize, int theModtime) : type(theType), size(theSize), modtime(theModtime) {
		// Nothing.
	}

	/**
	 * The type of the object at the path (file, directory, symlink, empty, etc.).
	 */
	std::string type;

	/**
	 * The size in bytes of the file, or -1 if it can't be determined.
	 */
	int size;

	/**
	 * The file's last modification time in seconds since the unix epoch, or -1 if it can't be determined.
	 */
	int modtime;
};

}  // namespace FileSystem
}  // namespace Types
}  // namespace love

#endif  // LIBRETRO_DATABASE_LIBRETRO_CHAILOVE_SRC_LOVE_TYPES_FILESYSTEM_FILEINFO_H_
