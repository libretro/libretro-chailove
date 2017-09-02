#ifndef CHAIGAME_TIMER_H
#define CHAIGAME_TIMER_H

namespace chaigame {
	class timer {
	public:
		timer();
		void step(double delta);
		double getDelta();

		int getFPS();
		double m_delta;
		double m_deltaCounter;
		int m_frameCounter;
		int m_fps;
	};
}

#endif
