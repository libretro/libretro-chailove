#include "SoundData.h"
#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include "../../../ChaiLove.h"
#include "AudioState.h"
#include "physfs.h"

namespace love {
namespace Types {
namespace Audio {

SoundData::SoundData(const std::string& filename) {
	// Load the file.
	ChaiLove* app = ChaiLove::getInstance();
	PHYSFS_file* file = app->filesystem.openFile(filename);
	if (file == NULL) {
		std::cout << "[ChaiLove] [SoundData] Couldn't open up file." << filename << app->filesystem.getLastError() << std::endl;
		return;
	}

	// Find the file size.
	int size = app->filesystem.getSize(file);
	if (size <= 0) {
		std::cout << "[ChaiLove] [SoundData] Couldn't determine file size." << filename << app->filesystem.getLastError() << std::endl;
		PHYSFS_close(file);
		return;
	}

	// Read the full buffer.
	void* buffer = (void*)malloc(size);
	int result = PHYSFS_readBytes(file, buffer, size);
	if (result < 0) {
		std::cout << "[ChaiLove] [SoundData] Failed to load SoundData " << filename << app->filesystem.getLastError() << std::endl;
		free(buffer);
		PHYSFS_close(file);
		return;
	}

	// Load the file into the buffer.
	m_sound = audio_mixer_load_wav(buffer, size);
	free(buffer);
	PHYSFS_close(file);
	if (!isLoaded()) {
		std::cout << "[ChaiLove] audio: Failed to load wav from buffer " << filename << std::endl;
	}
}

SoundData::~SoundData() {
	unload();
}

float SoundData::getVolume() {
	return m_volume;
}

SoundData& SoundData::setVolume(float volume) {
	if (volume > 1.0f) {
		volume = 1.0f;
	} else if (volume < 0.0f) {
		volume = 0.0f;
	}
	m_volume = volume;
	return *this;
}

void SoundData::unload() {
	if (isLoaded()) {
		audio_mixer_destroy(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		state = Playing;
		return true;
	}
	return false;
}

bool SoundData::resume() {
	if (isLoaded()) {
		state = Playing;
		return true;
	}
	return false;
}

bool SoundData::pause() {
	if (isLoaded()) {
		state = Paused;
		return true;
	}
	return false;
}

bool SoundData::stop() {
	state = Stopped;
	if (isLoaded()) {
		// PHYSFS_seek(sndta.fp, WAV_HEADER_SIZE);
	}
	return true;
}

bool SoundData::isLoaded() {
	return m_sound != NULL;
}

bool SoundData::isPlaying() {
	return state == Playing;
}

bool SoundData::isLooping() {
	return loop;
}

SoundData& SoundData::setLooping(bool looping) {
	loop = looping;
	return *this;
}

}  // namespace Audio
}  // namespace Types
}  // namespace love
