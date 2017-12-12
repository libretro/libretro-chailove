#ifndef SRC_LOVE_EVENT_H_
#define SRC_LOVE_EVENT_H_

namespace love {
/**
 * @brief Manages events, like keypresses.
 */
class event {
	public:
	/**
	 * @brief Exits ChaiLove.
	 */
	void quit();
	bool quitstatus = false;
};

}  // namespace love

#endif  // SRC_LOVE_EVENT_H_
