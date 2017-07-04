#include "timer.h"
#include <SDL.h>

namespace chaigame {

	bool timer::load() {
		current = last = SDL_GetTicks();
	}

	void timer::step() {
		last = current;
		current = SDL_GetTicks();
		delta = (float)current - (float)last;
	}

	float timer::getDelta() {
		return delta;
	}
}
