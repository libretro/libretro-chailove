#include "SoundData.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "../../../ChaiLove.h"

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

	// Get the extension of the file.
	std::string extension = app->filesystem.newFileData(filename).getExtension();
	if (extension == "wav") {
		m_sound = audio_mixer_load_wav(buffer, size);
	} else if (extension == "ogg") {
		m_sound = audio_mixer_load_ogg(buffer, size);
	} else {
		std::cout << "[ChaiLove] [SoundData] File " << filename << " extension of " << extension << " is currently not supported." << std::endl;
		return;
	}
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
		m_volume = audio_mixer_voice_get_volume(m_voice);
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
		m_voice = audio_mixer_play(m_sound, m_loop, m_volume, audioCallback);
		if (m_voice != NULL) {
			m_playing = true;
		}
		return true;
	}
	return false;
}

bool SoundData::stop() {
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
	return m_playing;
}

bool SoundData::isLooping() {
	return m_loop;
}

SoundData& SoundData::setLooping(bool looping) {
	m_loop = looping;
	return *this;
}

void SoundData::audioCallback(audio_mixer_sound_t* sound, unsigned reason) {
	// This is called when an audio finishes.
	ChaiLove* app = ChaiLove::getInstance();

	// Loop through all sounds, and find the given one.
	std::vector<Types::Audio::SoundData*> v = app->sound.sounds;
	for(std::vector<SoundData*>::iterator it = v.begin(); it != v.end(); ++it) {
		SoundData* currentsound = *it;
		if (currentsound == NULL) {
			continue;
		}
		// We found the active sound.
		if (currentsound->m_sound == sound) {
			switch (reason) {
				case AUDIO_MIXER_SOUND_FINISHED:
				case AUDIO_MIXER_SOUND_STOPPED:
					currentsound->m_playing = false;
					break;
				case AUDIO_MIXER_SOUND_REPEATED:
					currentsound->m_playing = true;
					break;
			}
			break;
		}
	}
}


}  // namespace Audio
}  // namespace Types
}  // namespace love
