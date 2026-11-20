#include "SoundData.h"
#include <string>
#include <stdlib.h>

#include "../../../ChaiLove.h"

namespace love {
namespace Types {
namespace Audio {

SoundData::SoundData(const std::string& filename) {
	// Check the extension.
	m_sound = pntr_load_sound(filename.c_str());

	// Apply the master volume.
	setVolume(m_volume);
}

SoundData::~SoundData() {
	unload();
}

void SoundData::unload() {
	if (m_sound != NULL) {
		pntr_unload_sound(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		// Playing an already playing source does nothing, matching Love2D.
		if (!isPlaying()) {
			pntr_play_sound(m_sound, m_loop);
		}
		return true;
	}
	return false;
}

bool SoundData::stop() {
	pntr_stop_sound(m_sound);
	return true;
}

bool SoundData::isLoaded() {
	return m_sound != NULL;
}

bool SoundData::isLooping() {
	return m_loop;
}

SoundData& SoundData::setLooping(bool looping) {
	m_loop = looping;
	return *this;
}

SoundData& SoundData::setVolume(float volume) {
	if (volume < 0.0f) {
		volume = 0.0f;
	}
	else if (volume >= 1.0f) {
		volume = 1.0f;
	}
	m_volume = volume;
	pntr_set_volume(m_sound, m_volume * ChaiLove::getInstance()->audio.getVolume());
	return *this;
}

float SoundData::getVolume() {
	return m_volume;
}

bool SoundData::isPlaying() {
	return pntr_sound_playing(m_sound);
}

}  // namespace Audio
}  // namespace Types
}  // namespace love
