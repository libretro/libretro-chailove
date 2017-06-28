#ifndef _SOUND_H_INCLUDED_
#define _SOUND_H_INCLUDED_

#include <SDL.h>

#include <SDL2pp/SDLMixer.hh>

namespace chaigame {
	class sound {
	public:
		bool load();
		bool update();
		bool unload();

		int numtimesopened;
		int frequency;
		int channels;
    	Uint16 format;

    	bool initialized;

    	SDL2pp::SDLMixer* mixer;
	};
}

#endif
