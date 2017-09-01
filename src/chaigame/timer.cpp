#include "timer.h"
#include "SDL.h"

namespace chaigame {

	float timer::getDelta() {
		return m_delta;
	}

	void timer::step(float delta) {
		m_delta = delta;
	}
}
