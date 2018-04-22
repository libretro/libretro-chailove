#ifndef SRC_LOVE_EVENT_H_
#define SRC_LOVE_EVENT_H_

#include <SDL.h>

namespace love {
/**
 * Manages events, like keypresses.
 */
class event {
	public:
	/**
	 * Exits the ChaiLove application.
	 */
	void quit();
	void update();

	bool m_shouldclose = false;


	private:
	SDL_Event sdlEvent;
};

}  // namespace love

#endif  // SRC_LOVE_EVENT_H_
