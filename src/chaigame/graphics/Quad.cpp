#include "Quad.h"

#include "SDL.h"
#include "SDL_gpu.h"

namespace chaigame {
	Quad::Quad(int t_x, int t_y, int t_width, int t_height, int t_sw, int t_sh)
		: x(t_x), y(t_y), width(t_width), height(t_height), sw(t_sw), sh(t_sh) {
		// Nothing.
	}
	Quad::Quad(int t_x, int t_y, int t_width, int t_height)
		: x(t_x), y(t_y), width(t_width), height(t_height) {
		// Nothing.
	}

	Quad::Quad() {
		// Nothing.
	}

	GPU_Rect* Quad::toRect() {
		GPU_Rect* rect = new GPU_Rect();
		rect->x = x;
		rect->y = y;
		rect->w = width;
		rect->h = height;
		return rect;
	}
}
