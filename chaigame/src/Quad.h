#ifndef _SRCQUAD_H_INCLUDED_
#define _SRCQUAD_H_INCLUDED_

#include "SDL.h"

namespace chaigame {
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
