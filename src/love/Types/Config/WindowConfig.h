#ifndef SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_
#define SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_

#include <string>

namespace love {
namespace Types {
namespace Config {

/**
 * @brief Configuration for how the application is set up.
 */
struct WindowConfig {
	/**
	 * @brief The width of the screen.
	 */
	int width = 800;

	/**
	 * @brief The height of the screen.
	 */
	int height = 600;

	/**
	 * @brief The number of bits used to represent each pixel in a surface.
	 */
	int bbp = 32;

	/**
	 * @brief The name of the application. Defaults to "ChaiLove".
	 */
	std::string title = "ChaiLove";
	bool asyncblit = true;
	bool hwsurface = true;
	bool doublebuffering = true;
};

}  // namespace Config
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_
