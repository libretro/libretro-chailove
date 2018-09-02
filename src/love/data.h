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
	 *
	 * @code
	 * var message = "Hello World!"
	 * var compressed = love.data.compress(message)
	 * print(compressed)
	 * var decompressed = love.data.decompress(compressed)
	 * print(decompressed)
	 * @endcode
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
	 * Encode Data or a string to a Data or string in one of the EncodeFormats.
	 *
	 * @param containerType What type to return the encoded data as. Can be either "data", or "string".
	 * @param format The format of the output data. Can be "base64" or "hex".
	 * @param sourceString The raw data to encode.
	 *
	 * @return String which contains the encoded version of source.
	 *
	 * @see love.data.decode
	 */
	std::string encode(const std::string& containerType, const std::string& format, const std::string& sourceString);

	/**
	 * Decode Data or a string to a Data or string in one of the EncodeFormats.
	 *
	 * @param containerType What type to return the decoded data as. Can be either "data", or "string".
	 * @param format The format of the input data. Can be "base64" or "hex".
	 * @param sourceString The raw (encoded) data to decode.
	 *
	 * @return String which contains the decoded version of source.
	 *
	 * @see love.data.encode
	 */
	std::string decode(const std::string& containerType, const std::string& format, const std::string& sourceString);

	/**
	 * Compute the message digest of specified string with specified algorithm.
	 *
	 * @param hashFunction Hash algorithm to use (md5, sha1).
	 * @param data String to hash.
	 *
	 * @todo Add sha256, sha512, etc.
	 *
	 * @return Raw message digest string.
	 *
	 * @code
	 * var message = "Hello World!"
	 * var hash = love.data.hash("md5", message)
	 * print(hash)
	 * @endcode
	 */
	std::string hash(const std::string& hashFunction, const std::string& data);

	private:
	std::string hash_md5(const std::string& data);
	std::string hash_sha1(const std::string& data);
};

}  // namespace love

#endif  // SRC_LOVE_DATA_H_
