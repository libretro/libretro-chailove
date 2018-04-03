#ifndef SRC_LOVE_DATA_H_
#define SRC_LOVE_DATA_H_

#include <string>

namespace love {
/**
 * @brief Provides access to information about the user's system.
 */
class data {
	public:

	/**
	 * @brief Compresses a string or data using a specific compression level.
	 *
	 * @param str The raw (un-compressed) string to compress.
	 * @param level (-1) The level of compression to use, between 0 and 9. -1 indicates the default level.
	 *
	 * @return Compressed data in the form of a string.
	 *
	 * @see love.data.decompress
	 */
	std::string compress(const std::string& str, int level);
	std::string compress(const std::string& str);

	/**
	 * @brief Decompresses a compressed string.
	 *
	 * @param str A string containing data previously compressed with math.compress().
	 *
	 * @return A string containing the raw decompressed data.
	 *
	 * @see love.data.compress
	 */
	std::string decompress(const std::string& str);
};

}  // namespace love

#endif  // SRC_LOVE_DATA_H_
