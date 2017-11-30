#include "timer.h"

namespace Modules {

timer::timer() {
	m_delta = 0;
	m_deltaCounter = 0;
	m_frameCounter = 0;
}

float timer::getDelta() {
	return m_delta;
}

void timer::step(float delta) {
	m_delta = delta;
	m_deltaCounter += delta;
	m_frameCounter++;

	if (m_deltaCounter >= 1.0f) {
		m_fps = m_frameCounter;
		m_frameCounter = 0;
		m_deltaCounter = 0;
	}
}

int timer::getFPS() {
	return m_fps;
}

}  // namespace Modules
