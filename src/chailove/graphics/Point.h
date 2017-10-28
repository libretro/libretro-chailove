#ifndef CHAILOVE_UTILITY_POINT_H
#define CHAILOVE_UTILITY_POINT_H

namespace chailove {
	struct Point {
		Point() : x(0), y(0) {}
		Point(int val) : x(val), y(val) {}
		Point(int xPoint, int yPoint) : x(xPoint), y(yPoint) {}
		int x, y;
	};
}

#endif
