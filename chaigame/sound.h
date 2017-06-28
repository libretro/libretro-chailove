#ifndef _SOUND_H_INCLUDED_
#define _SOUND_H_INCLUDED_

#include <SDL.h>

namespace chaigame {
	class sound {
	public:
		bool load();
		bool unload();

		int numtimesopened,frequency, channels;
	};
}

#endif
