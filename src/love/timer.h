#ifndef SRC_LOVE_TIMER_H_
#define SRC_LOVE_TIMER_H_

namespace love {

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
	float m_delta = 0.0f;
	float m_deltaCounter = 0.0f;
	int m_frameCounter = 0;
	int m_fps = 0;
};

}  // namespace love

#endif  // SRC_LOVE_TIMER_H_
