#ifndef _SOUND_H_INCLUDED_
#define _SOUND_H_INCLUDED_

#include <SDL.h>
#include "src/SoundData.h"

namespace chaigame {
	class sound {
	public:
		bool load();
		bool hasAudio();
		void unload();
		SoundData* newSoundData(const std::string& file, const std::string& type);
		bool update();

		int numtimesopened = 0;
		int frequency = 0;
		int channels = 0;
    	Uint16 format;

    	bool initialized = false;
	};
}

#endif
