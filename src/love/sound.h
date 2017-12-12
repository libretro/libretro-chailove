#ifndef SRC_LOVE_SOUND_H_
#define SRC_LOVE_SOUND_H_

#include "Types/Audio/SoundData.h"
#include <vector>

namespace love {

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
    Types::Audio::SoundData* newSoundData(const std::string& filename);

	std::vector<Types::Audio::SoundData*> sounds;
};

}  // namespace love

#endif  // SRC_LOVE_SOUND_H_
