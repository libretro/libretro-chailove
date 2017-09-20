#include "Color.h"

#include "SDL.h"

namespace chaigame {
	Color::Color() : r(0), g(0), b(0), a(0) {
		// Nothing.
	}
	Color::Color(Uint8 t_r, Uint8 t_g, Uint8 t_b, Uint8 t_a)
		: r(t_r), g(t_g), b(t_b), a(t_a) {
		// Nothing.
	}
	Color::Color(Uint8 t_r, Uint8 t_g, Uint8 t_b)
		: r(t_r), g(t_g), b(t_b), a(0) {
		// Nothing.
	}

	SDL_Color Color::toSDLColor() {
		SDL_Color c = SDL_Color();
		c.r = r;
		c.g = g;
		c.b = b;
		c.unused = a;
		return c;
	}
}
