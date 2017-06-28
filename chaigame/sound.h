#ifndef _SOUND_H_INCLUDED_
#define _SOUND_H_INCLUDED_

#include <SDL.h>
#include <SDL_mixer.h>

namespace chaigame {
	class sound {
	public:
		bool load();
		bool unload();
	};
}

#endif
