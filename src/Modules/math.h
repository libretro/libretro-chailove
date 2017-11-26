#ifndef CHAILOVE_MATH_H
#define CHAILOVE_MATH_H

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
		 */
		int random(int min, int max);
		/**
		 * @brief Get uniformly distributed pseudo-random number, from 0 to the given max value.
		 */
		int random(int max);
		/**
		 * @brief Get uniformly distributed pseudo-random number, between 0 and 1.
		 */
		double random();
		/**
		 * @brief Sets the seed of the random number generator.
		 */
		void setRandomSeed(int seed);
		/**
		 * @brief Sets the seed of the random number generator.
		 */
		void setRandomSeed(int low, int high);
		/**
		 * @brief Gets the seed of the random number generator.
		 */
		int getRandomSeed();

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
		 * @brief Pi
		 */
		const float pi = 3.14159265358979323846f;
		/**
		 * @brief e
		 */
		const float e = 2.718281828459045f;
		int m_seed;
	};
}

#endif
