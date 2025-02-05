#ifndef SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
#define SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_

#include <string>
#include "audio/audio_mixer.h"

#include "pntr_app.h"

namespace love {
namespace Types {
namespace Audio {

/**
 * Contains audio samples that you can playback.
 */
class SoundData {
	public:
	SoundData(const std::string& filename);
	~SoundData();

	/**
	 * Plays the source.
	 */
	bool play();

	/**
	 * Stops the audio source.
	 */
	bool stop();

	void unload();
	bool isLoaded();

	/**
	 * Returns whether the Source will loop.
	 *
	 * @see setLooping
	 */
	bool isLooping();

	/**
	 * Set whether the Source should loop.
	 *
	 * @see isLooping
	 */
	SoundData& setLooping(bool loop);

	/**
	 * Set the volume for the sound.
	 *
	 * @param volume A float from 0.0f to 1.0f.
	 */
	SoundData& setVolume(float volume);

	/**
	 * Retrieve the volume for the sound.
	 */
	float getVolume();

	/**
	 * Returns true or false depending on if the sound is actively playing.
	 */
	bool isPlaying();

	pntr_sound* m_sound = NULL;
	bool m_loop = false;
	float m_volume = 1.0f;
};

}  // namespace Audio
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
