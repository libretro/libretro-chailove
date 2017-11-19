#ifndef CHAILOVE_UTILITY_POINT_H
#define CHAILOVE_UTILITY_POINT_H

namespace chailove {
	struct Point {
		Point() : x(0), y(0) {}
		Point(float val) : x(val), y(val) {}
		Point(float xValue, float yValue) : x(xValue), y(yValue) {}
		float x, y;
	};
}

#endif
