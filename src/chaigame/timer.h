#ifndef CHAIGAME_TIMER_H
#define CHAIGAME_TIMER_H

namespace chaigame {
	class timer {
	public:
		bool load();
		void step();
		float getDelta();
		int last;
		int current;
		float delta;
	};
}

#endif