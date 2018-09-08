#ifndef SRC_LOVE_AUDIO_H_
#define SRC_LOVE_AUDIO_H_

#include "Types/Audio/SoundData.h"
#include "sound.h"

using love::Types::Audio::SoundData;

namespace love {

/**
 * Provides an interface to output sound to the user's speakers.
 *
 * @see love.sound
 */
class audio {
	public:
	/**
	 * Plays the specified sound.
	 *
	 * @param soundData The sound to play.
	 *
	 * @return True or false, depending on whether or not the sound data successfully played.
	 */
	bool play(SoundData* soundData);

	/**
	 * Creates a new audio source from a file.
	 *
	 * @param filename The .wav file to load.
	 * @param type ("static") The type of audio source to load ("static", "stream"). Optional.
	 *
	 * @return The new SoundData if it loaded correctly, NULL otherwise.
	 *
	 * @see love.sound.newSoundData
	 */
	SoundData* newSource(const std::string& filename, const std::string& type);
	SoundData* newSource(const std::string& filename);

	/**
	 * Returns the master volume.
	 *
	 * @return The current master volume between 0.0f and 1.0f.
	 */
	float getVolume();

	/**
	 * Set the master volume.
	 *
	 * @param volume 1.0f is max and 0.0f is off.
	 *
	 * @return The audio module, to allow method chaining.
	 */
	audio& setVolume(float volume);

	float m_volume = 1.0f;
};

}  // namespace love

#endif  // SRC_LOVE_AUDIO_H_
