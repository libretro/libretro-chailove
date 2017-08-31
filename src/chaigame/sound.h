#ifndef CHAIGAME_SOUND_H
#define CHAIGAME_SOUND_H

#include "audio/SoundData.h"
#include <vector>

namespace chaigame {
	class sound {
	public:
		bool load();
		bool hasAudio();
		void unload();
		SoundData* newSoundData(const std::string& file, const std::string& type);
		SoundData* newSoundData(const std::string& file);
		bool update();

		int numtimesopened = 0;
		int frequency = 0;
		int channels = 0;
    	int format;

    	bool initialized = false;
    	bool firstRun = true;
    	bool loaded = false;
    	bool toInit = false;

    	std::vector<SoundData*> sounds;
	};
}

#endif
