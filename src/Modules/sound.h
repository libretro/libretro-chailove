#ifndef CHAILOVE_SOUND_H
#define CHAILOVE_SOUND_H

#include "../Types/Audio/SoundData.h"
#include <vector>

using Types::Audio::SoundData;

namespace Modules {
	/**
	 * @brief This module is responsible for decoding sound files. It can't play the sounds, see love.audio for that.
	 */
	class sound {
	public:
		bool load();
		bool hasAudio();
		void unload();
		bool update();
		/**
		 * @brief Creates a new SoundData.
		 */
        SoundData* newSoundData(const std::string& filename);

    	std::vector<SoundData*> sounds;
	};
}
#endif
