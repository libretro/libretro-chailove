#ifndef SRC_TYPES_GRAPHICS_QUAD_H_
#define SRC_TYPES_GRAPHICS_QUAD_H_

#include "SDL.h"

namespace Types {
namespace Graphics {

/**
 * @brief An x, y, width, height, source width and source height.
 */
class Quad {
	public:
	int x, y, width, height, sw, sh;
	Quad();
	Quad(int x, int y, int width, int height, int sw, int sh);
	Quad(int x, int y, int width, int height);
	SDL_Rect* toRect();
};

}  // namespace Graphics
}  // namespace Types

#endif  // SRC_TYPES_GRAPHICS_QUAD_H_
