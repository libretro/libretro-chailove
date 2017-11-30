#ifndef SRC_MODULES_EVENT_H_
#define SRC_MODULES_EVENT_H_

namespace Modules {
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

}  // namespace Modules

#endif  // SRC_MODULES_EVENT_H_
