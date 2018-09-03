#include "SoundData.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "../../../ChaiLove.h"
#include "physfs.h"

namespace love {
namespace Types {
namespace Audio {

SoundData::SoundData(const std::string& filename) {
	// Load the file.
	ChaiLove* app = ChaiLove::getInstance();

	// Load the file.
	int size = 0;
	void* buffer = app->filesystem.readBuffer(filename, size);
	if (buffer == NULL) {
		std::cout << "[ChaiLove] [SoundData] Failed to load file buffer " << filename << std::endl;
		return;
	}

	// Load the file into the buffer.
	// TODO(RobLoach): Check the audio file extensions of ".wav".
	m_sound = audio_mixer_load_wav(buffer, size);
	free(buffer);
	if (m_sound == NULL) {
		std::cout << "[ChaiLove] [SoundData] Failed to load wav from buffer " << filename << std::endl;
	}
}

SoundData::~SoundData() {
	unload();
}

float SoundData::getVolume() {
	if (m_voice != NULL) {
		return audio_mixer_voice_get_volume(m_voice);
	}
	return m_volume;
}

SoundData& SoundData::setVolume(float volume) {
	if (volume > 1.0f) {
		volume = 1.0f;
	} else if (volume < 0.0f) {
		volume = 0.0f;
	}
	m_volume = volume;
	if (m_voice != NULL) {
		audio_mixer_voice_set_volume(m_voice, m_volume);
	}
	return *this;
}

void SoundData::unload() {
	if (m_voice != NULL) {
		audio_mixer_stop(m_voice);
	}
	if (isLoaded()) {
		audio_mixer_destroy(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		m_voice = audio_mixer_play(m_sound, m_loop, m_volume, NULL);
		return true;
	}
	return false;
}

bool SoundData::stop() {
	// state = Stopped;
	if (isLoaded()) {
		if (m_voice != NULL) {
			audio_mixer_stop(m_voice);
		}
	}
	return true;
}

bool SoundData::isLoaded() {
	return m_sound != NULL;
}

bool SoundData::isPlaying() {
	if (m_voice != NULL) {
		return true;
	}
	return false;
}

bool SoundData::isLooping() {
	return m_loop;
}

SoundData& SoundData::setLooping(bool looping) {
	m_loop = looping;
	return *this;
}

}  // namespace Audio
}  // namespace Types
}  // namespace love
