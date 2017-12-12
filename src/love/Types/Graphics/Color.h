#ifndef SRC_LOVE_TYPES_GRAPHICS_COLOR_H_
#define SRC_LOVE_TYPES_GRAPHICS_COLOR_H_

#include "SDL.h"

namespace love {
namespace Types {
namespace Graphics {

/**
 * @brief A color, holding red, green, blue and alpha values.
 */
struct Color {
	/**
	 * @brief Create a color with the value of 0, 0, 0, 0.
	 */
	Color() : r(0), g(0), b(0), a(0) {
		// Nothing.
	}

	/**
	 * @brief Create a new color.
	 */
	Color(int rValue, int gValue, int bValue, int aValue) : r(rValue), g(gValue), b(bValue), a(aValue) {
		// Nothing.
	}

	/**
	 * @brief Create a new color.
	 */
	Color(int rValue, int gValue, int bValue) : r(rValue), g(gValue), b(bValue) {
		// Nothing.
	}

	/**
	 * @brief The amount of red.
	 */
	int r;

	/**
	 * @brief The amount of green.
	 */
	int g;

	/**
	 * @brief The amount of blue.
	 */
	int b;

	/**
	 * @brief The amount of alpha.
	 */
	int a;

	SDL_Color toSDLColor() {
		SDL_Color c;
		c.r = r;
		c.g = g;
		c.b = b;
		c.unused = a;
		return c;
	}
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_COLOR_H_
