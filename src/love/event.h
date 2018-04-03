#ifndef SRC_LOVE_EVENT_H_
#define SRC_LOVE_EVENT_H_

namespace love {
/**
 * Manages events, like keypresses.
 */
class event {
	public:
	/**
	 * Exits ChaiLove.
	 */
	void quit();
	bool m_quitstatus = false;
};

}  // namespace love

#endif  // SRC_LOVE_EVENT_H_
