#ifndef SRC_MODULES_TIMER_H_
#define SRC_MODULES_TIMER_H_

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
	float m_delta = 0.0f;
	float m_deltaCounter = 0.0f;
	int m_frameCounter = 0;
	int m_fps = 0;
};

}  // namespace Modules

#endif  // SRC_MODULES_TIMER_H_
