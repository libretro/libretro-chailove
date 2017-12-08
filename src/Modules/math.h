#ifndef SRC_MODULES_MATH_H_
#define SRC_MODULES_MATH_H_

#include <string>

namespace Modules {
/**
 * @brief Provides system-independent mathematical functions.
 */
class math {
	public:
	bool load();
	/**
	 * @brief Get uniformly distributed pseudo-random number, between the given numbers.
	 *
	 * @param min (0.0f) The minimum value.
	 * @param max (1.0f) The max value.
	 *
	 * @return a number between the two given min and max values.
	 */
	float random(float min, float max);
	float random(float max);
	float random();

	/**
	 * @brief Sets the random seed to a random seed between the given min and max values.
	 */
	void setRandomSeed(int min, int max);

	/**
	 * @brief Sets the seed of the random number generator.
	 */
	void setRandomSeed(int seed);

	/**
	 * @brief Gets the seed of the random number generator.
	 */
	int getRandomSeed();

	/**
	 * @brief Converts from degrees to radians.
	 */
	float rad(float degrees);

	/**
	 * @brief Converts from radians to degrees.
	 */
	float degrees(float rad);

	std::string compress(const std::string& str);

	/**
	 * @brief Compresses a string or data using a specific compression level.
	 *
	 * @param str The raw (un-compressed) string to compress.
	 * @param level (-1) The level of compression to use, between 0 and 9. -1 indicates the default level.
	 *
	 * @return Compressed data in the form of a string.
	 */
	std::string compress(const std::string& str, int level);

	/**
	 * @brief Decompresses a compressed string.
	 *
	 * @param str A string containing data previously compressed with math.compress().
	 *
	 * @return A string containing the raw decompressed data.
	 */
	std::string decompress(const std::string& str);

	/**
	 *
	 @brief e
	 */
	const float e = 2.718281828459045f;

	/**
	 * @brief pi
	 */
	const float pi = 3.14159265358979323846f;

	int m_seed = 0;
};

}  // namespace Modules

#endif  // SRC_MODULES_MATH_H_
