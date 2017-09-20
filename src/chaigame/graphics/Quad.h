#ifndef CHAIGAME_UTILITY_QUAD_H
#define CHAIGAME_UTILITY_QUAD_H

#include "SDL.h"
#include "SDL_gpu.h"

namespace chaigame {
	class Quad {
	public:
		int x, y, width, height, sw, sh;
		Quad();
		Quad(int x, int y, int width, int height, int sw, int sh);
		Quad(int x, int y, int width, int height);
		GPU_Rect* toRect();
	};
}

#endif
