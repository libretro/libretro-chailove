#ifndef _POSITIONH_INCLUDED_
#define _POSITIONH_INCLUDED_

namespace chaigame {
	struct Point {
		Point() : x(0), y(0) {}
		Point(int val) : x(val), y(val) {}
		Point(int xPoint, int yPoint) : x(xPoint), y(yPoint) {}
		int x, y;
	};
}

#endif
