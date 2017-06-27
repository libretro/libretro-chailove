#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

namespace chaigame {
	class graphics {
	public:
		void rectangle(Sint16 x, Sint16 y, Sint16 width, Sint16 height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	};
}

#endif
