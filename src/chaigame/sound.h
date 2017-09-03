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
		bool update();
        SoundData* newSoundData(const std::string& filename);

    	std::vector<SoundData*> sounds;
	};
}
#endif
