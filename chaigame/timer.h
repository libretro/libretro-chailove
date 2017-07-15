#ifndef CHAIGAME_TIMER_H
#define CHAIGAME_TIMER_H

#include "SDL.h"

namespace chaigame {
	class timer {
	public:
		bool load();
		void step();
		float getDelta();
		Uint32 last;
		Uint32 current;
		float delta;
	};
}

#endif
