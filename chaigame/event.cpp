#include "event.h"
#include <SDL.h>

namespace chaigame {
	void event::quit() {
		quitstatus = true;
	}
}
