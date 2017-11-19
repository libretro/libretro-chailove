#ifndef CHAILOVE_AUDIO_H
#define CHAILOVE_AUDIO_H

#include "../Types/Audio/SoundData.h"
#include "sound.h"

using Types::Audio::SoundData;

namespace Modules {
	class audio {
	public:
		void play(SoundData* soundData);
		SoundData* newSource(const std::string& filename);

		void mixer_render(int16_t *buffer);

		int AUDIO_FRAMES = 735; // 44100 / 60
		int WAV_HEADER_SIZE = 44;
		float m_volume = 1.0f;

		float getVolume();
		void setVolume(float volume);
	};
}
#endif
