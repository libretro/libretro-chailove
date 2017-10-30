#ifndef CHAILOVE_TIMER_H
#define CHAILOVE_TIMER_H

namespace chailove {
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
