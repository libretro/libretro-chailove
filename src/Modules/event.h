#ifndef CHAILOVE_EVENT_H
#define CHAILOVE_EVENT_H

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
}

#endif
