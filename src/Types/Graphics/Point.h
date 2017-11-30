#ifndef SRC_TYPES_GRAPHICS_POINT_H_
#define SRC_TYPES_GRAPHICS_POINT_H_

namespace Types {
namespace Graphics {

/**
 * @brief An x and y coordinate.
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
	 * @brief The x coordinate.
	 */
	float x;

	/**
	 * @brief The y coordinate.
	 */
	float y;
};

}  // namespace Graphics
}  // namespace Types

#endif  // SRC_TYPES_GRAPHICS_POINT_H_
