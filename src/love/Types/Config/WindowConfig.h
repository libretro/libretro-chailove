#ifndef SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_
#define SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_

#include <string>

namespace love {
namespace Types {
namespace Config {

/**
 * Configuration for how the application is set up.
 */
struct WindowConfig {
	/**
	 * The width of the screen.
	 */
	int width = 800;

	/**
	 * The height of the screen.
	 */
	int height = 600;

	/**
	 * The number of bits used to represent each pixel in a surface.
	 */
	int bbp = 32;

	/**
	 * The name of the application. Defaults to "ChaiLove".
	 */
	std::string title = "ChaiLove";
	bool asyncblit = true;
	bool hwsurface = true;
	bool doublebuffering = true;
	bool console = false;
};

}  // namespace Config
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_CONFIG_WINDOWCONFIG_H_
