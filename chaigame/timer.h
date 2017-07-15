#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_

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
