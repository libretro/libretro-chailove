#ifndef CHAILOVE_UTILITY_QUAD_H
#define CHAILOVE_UTILITY_QUAD_H

#include "SDL.h"

namespace chailove {
	class Quad {
	public:
		int x, y, width, height, sw, sh;
		Quad();
		Quad(int x, int y, int width, int height, int sw, int sh);
		Quad(int x, int y, int width, int height);
		SDL_Rect* toRect();
	};
}

#endif
