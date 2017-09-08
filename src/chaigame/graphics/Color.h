#ifndef CHAIGAME_UTILITY_COLOR_H
#define CHAIGAME_UTILITY_COLOR_H

#include "SDL.h"

namespace chaigame {
	class Color {
	public:
		Color();
		Color(Uint8 r, Uint8 g, Uint8 b);
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		Uint8 r, g, b, a;
		SDL_Color toSDLColor();
	};
}

#endif
