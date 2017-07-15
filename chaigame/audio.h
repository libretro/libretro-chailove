#ifndef CHAIGAME_AUDIO_H
#define CHAIGAME_AUDIO_H

#include "src/SoundData.h"

namespace chaigame {
	class audio {
	public:
		void play(SoundData* soundData);
		SoundData* newSource(const std::string& filename, const std::string& type);
		SoundData* newSource(const std::string& filename);
	};
}

#endif
