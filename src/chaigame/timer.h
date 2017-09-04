#ifndef CHAIGAME_TIMER_H
#define CHAIGAME_TIMER_H

namespace chaigame {
	class timer {
	public:
		timer();
		void step(float delta);
		float getDelta();

		int getFPS();
		float m_delta;
		float m_deltaCounter;
		int m_frameCounter;
		int m_fps;
	};
}

#endif
