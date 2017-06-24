
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "graphics.h"
#include "../Application.h"

namespace chaigame {
	namespace graphics {
		void rectangle(Sint16 x, Sint16 y, Sint16 width, Sint16 height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
			rectangleRGBA(Application::getInstance()->screen, x, y, x + width, y + height, r, g, b, a);
		}
	}
}
