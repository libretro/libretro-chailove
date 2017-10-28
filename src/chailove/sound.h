#ifndef CHAILOVE_SOUND_H
#define CHAILOVE_SOUND_H

#include "audio/SoundData.h"
#include <vector>

namespace chailove {
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
