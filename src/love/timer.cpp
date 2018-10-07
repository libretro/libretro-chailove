#include "timer.h"

namespace love {

timer::timer() {
	// Nothing.
}

float timer::getDelta() {
	return m_delta;
}

float timer::step(float delta) {
	m_delta = delta;
	m_deltaCounter += delta;
	m_frameCounter++;

	if (m_deltaCounter >= 1.0f) {
		m_fps = m_frameCounter;
		m_frameCounter = 0;
		m_deltaCounter = 0;
	}

	return m_delta;
}

int timer::getFPS() {
	return m_fps;
}

}  // namespace love
