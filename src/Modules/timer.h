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
	float m_delta;
	float m_deltaCounter;
	int m_frameCounter;
	int m_fps;
};

}  // namespace Modules

#endif  // namespace SRC_MODULES_TIMER_H_
