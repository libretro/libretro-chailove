#ifndef CHAILOVE_TIMER_H
#define CHAILOVE_TIMER_H

namespace Modules {
	/**
	 * @brief Provides high-resolution timing functionality.
	 */
	class timer {
	public:
		timer();
		void step(float delta);
		/**
		 * @brief Returns the time between the last two frames.
		 */
		float getDelta();

		/**
		 * @brief Returns the current frames per second.
		 */
		int getFPS();
		float m_delta;
		float m_deltaCounter;
		int m_frameCounter;
		int m_fps;
	};
}

#endif
