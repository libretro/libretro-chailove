#ifndef SRC_LOVE_DATA_H_
#define SRC_LOVE_DATA_H_

#include <string>

namespace love {
/**
 * Provides functionality for creating and transforming data.
 */
class data {
	public:
	/**
	 * Compresses a string or data using a specific compression level.
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
	 * Decompresses a compressed string.
	 *
	 * @param str A string containing data previously compressed with math.compress().
	 *
	 * @return A string containing the raw decompressed data.
	 *
	 * @see love.data.compress
	 */
	std::string decompress(const std::string& str);

	/**
	 * Compute the message digest of specified string with specified algorithm.
	 *
	 * @param hashFunction Hash algorithm to use (md5, sha1).
	 * @param data String to hash.
	 *
	 * @todo Add sha256, sha512, etc.
	 *
	 * @return Raw message digest string.
	 */
	std::string hash(const std::string& hashFunction, const std::string& data);

	private:
	std::string hash_md5(const std::string& data);
	std::string hash_sha1(const std::string& data);
};

}  // namespace love

#endif  // SRC_LOVE_DATA_H_
