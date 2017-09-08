#ifndef CHAIGAME_UTILITY_POINT_H
#define CHAIGAME_UTILITY_POINT_H

namespace chaigame {
	struct Point {
		Point() : x(0), y(0) {}
		Point(float val) : x(val), y(val) {}
		Point(float xPoint, float yPoint) : x(xPoint), y(yPoint) {}
		float x, y;
	};
}

#endif
