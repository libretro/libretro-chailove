#ifndef SRC_TYPES_GRAPHICS_COLOR_H_
#define SRC_TYPES_GRAPHICS_COLOR_H_

#include "SDL.h"

namespace Types {
namespace Graphics {

/**
 * @brief A color.
 */
struct Color {
	Color() : r(0), g(0), b(0), a(0) {
		// Nothing.
	}

	Color(int rValue, int gValue, int bValue, int aValue) : r(rValue), g(gValue), b(bValue), a(aValue) {
		// Nothing.
	}

	Color(int rValue, int gValue, int bValue) : r(rValue), g(gValue), b(bValue) {
		// Nothing.
	}

	int r;
	int g;
	int b;
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

#endif  // SRC_TYPES_GRAPHICS_COLOR_H_
