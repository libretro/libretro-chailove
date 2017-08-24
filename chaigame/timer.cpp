#include "timer.h"
//#include "SDL.h"

namespace chaigame {

	bool timer::load() {
		current = last = 0;//SDL_GetTicks();

		return true;
	}

	void timer::step() {
		last = current;
		current = 0;//SDL_GetTicks();
		delta = (float)current - (float)last;
	}

	float timer::getDelta() {
		return delta;
	}
}
