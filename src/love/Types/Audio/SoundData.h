#ifndef SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
#define SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_

#include <string>
#include "physfs.h"
#include "audio/audio_mixer.h"

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
	 * Gets the current volume of the Source.
	 *
	 * @return The volume of the source, from 0.0f to 1.0f.
	 */
	float getVolume();

	/**
	 * Sets the current volume of the Source.
	 *
	 * @param volume The volume to set the source at, from 0.0f to 1.0f.
	 *
	 * @return The SoundData object iself, to allow for method chaining.
	 */
	SoundData& setVolume(float volume);

	/**
	 * Returns whether the Source is playing.
	 *
	 * @return True if the sound is playing.
	 */
	bool isPlaying();

	/**
	 * Returns whether the Source will loop.
	 */
	bool isLooping();

	/**
	 * Set whether the Source should loop.
	 */
	SoundData& setLooping(bool loop);

	// The audio callback for when a sound finishes.
	static void audioCallback(audio_mixer_sound_t* sound, unsigned reason);

	// Properties
	bool m_playing = false;
	bool m_loop = false;
	float m_volume = 1.0f;
	void* buffer = NULL;
	audio_mixer_sound* m_sound = NULL;
	// TODO(RobLoach): Make voice a vector?
	audio_mixer_voice_t* m_voice = NULL;
};

}  // namespace Audio
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
