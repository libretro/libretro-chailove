#ifndef CHAIGAME_TIMER_H
#define CHAIGAME_TIMER_H

namespace chaigame {
	class timer {
	public:
		void step(float delta);
		float getDelta();
		float m_delta;
	};
}

#endif
