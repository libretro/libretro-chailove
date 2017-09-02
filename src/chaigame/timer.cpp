#include "timer.h"
#include "SDL.h"

namespace chaigame {

	timer::timer() {
		m_delta = 0;
		m_deltaCounter = 0;
		m_frameCounter = 0;
	}

	double timer::getDelta() {
		return m_delta;
	}

	void timer::step(double delta) {
		m_delta = delta;
		m_deltaCounter += delta;
		m_frameCounter++;

		if (m_deltaCounter >= 1.0) {
			m_fps = m_frameCounter;
			m_frameCounter = 0;
			m_deltaCounter = 0;
		}
	}

	int timer::getFPS() {
		return m_fps;
	}
}
