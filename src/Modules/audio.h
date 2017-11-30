#ifndef CHAILOVE_AUDIO_H
#define CHAILOVE_AUDIO_H

#include "../Types/Audio/SoundData.h"
#include "sound.h"

using Types::Audio::SoundData;

namespace Modules {
	/**
	 * @brief Provides an interface to output sound to the user's speakers.
	 */
	class audio {
	public:

		/**
		 * @brief Plays the specified sound.
		 */
		void play(SoundData* soundData);

		/**
		 * @brief Creates a new audio source from a file.
		 */
		SoundData* newSource(const std::string& filename);

		void mixer_render(int16_t *buffer);

		int AUDIO_FRAMES = 735; // 44100 / 60
		int WAV_HEADER_SIZE = 44;
		float m_volume = 1.0f;

		/**
		 * @brief Returns the master volume.
		 *
		 * @return The current master volume between 0.0f and 1.0f.
		 */
		float getVolume();

		/**
		 * @brief Set the master volume.
		 *
		 * @param volume 1.0f is max and 0.0f is off.
		 */
		void setVolume(float volume);
	};
}
#endif
