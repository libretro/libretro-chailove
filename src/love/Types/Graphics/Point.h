#ifndef SRC_LOVE_TYPES_GRAPHICS_POINT_H_
#define SRC_LOVE_TYPES_GRAPHICS_POINT_H_

namespace love {
namespace Types {
namespace Graphics {

/**
 * An x and y coordinate.
 */
struct Point {
	Point() : x(0), y(0) {
		// Nothing.
	}

	Point(float val) : x(val), y(val) {
		// Nothing.
	}

	Point(float xValue, float yValue) : x(xValue), y(yValue) {
		// Nothing.
	}
	/**
	 * The x coordinate.
	 */
	float x;

	/**
	 * The y coordinate.
	 */
	float y;
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_POINT_H_
