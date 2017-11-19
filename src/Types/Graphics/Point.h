#ifndef CHAILOVE_UTILITY_POINT_H
#define CHAILOVE_UTILITY_POINT_H

namespace Types {
	namespace Graphics {
	/**
	 * @brief An x and y coordinate.
	 */
	struct Point {
		Point() : x(0), y(0) {}
		Point(float val) : x(val), y(val) {}
		Point(float xValue, float yValue) : x(xValue), y(yValue) {}
		/**
		 * @brief The x coordinate.
		 */
		float x;

		/**
		 * @brief The y coordinate.
		 */
		float y;
	};
}
}
#endif
