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

	std::cout << "Sound: Loading " << filename << std::endl;
	ChaiLove* app = ChaiLove::getInstance();
	PHYSFS_file* file = app->filesystem.openFile(filename);
	std::cout << "SOUND Loading File" << std::endl;
	if (file == NULL) {
		std::cout << "[ChaiLove] [SoundData] Couldn't open up file." << filename << app->filesystem.getLastError() << std::endl;
		return;
	}

	std::cout << "SOUND Getting length" << std::endl;
	// Find the file size.
	int size = PHYSFS_fileLength(file);
	if (size <= 0) {
		std::cout << "[ChaiLove] [SoundData] Couldn't determine file size." << filename << app->filesystem.getLastError() << std::endl;
		PHYSFS_close(file);
		return;
	}

	std::cout << "SOUND size " << size << std::endl;
	//PHYSFS_seek(file, 0);
	// Read in the full buffer.
	/*
	std::cout << "SOUND reading buffer" << std::endl;
	void* buffer;
	int result = PHYSFS_readBytes(file, &buffer, size);
	if (result < 0) {
		std::cout << "[ChaiLove] Failed to load SoundData " << filename << app->filesystem.getLastError() << std::endl;
		PHYSFS_close(file);
		return;
	}
	std::cout << buffer;


	m_sound = audio_mixer_load_wav(buffer, size);

	std::cout << "SOUND phys close" << std::endl;
	PHYSFS_close(file);
	*/
	std::cout << "SOUND audio_mixer_oad" << std::endl;



	/**
	 * Load manually
	 */

	void* buffer2;
	FILE *pFile = fopen( "test/assets/startup.wav", "rb") ;
	if (pFile==NULL) {
		fputs("File error", stderr);
		exit (1);
	}
	buffer2 = (void*)malloc (size);
	if (buffer2 == NULL) {
		fputs ("Memory error", stderr);
		exit (2);
	}
	fread(buffer2, 1, size, pFile);
	m_sound = audio_mixer_load_wav(buffer2, size);
	fclose (pFile);
	free (buffer2);



	std::cout << "SOUND done" << std::endl;

	if (!isLoaded()) {
		std::cout << "[ChaiLove] Failed to load SoundData from a wav" << std::endl;
		return;
	}
	std::cout << "SOUND done2" << std::endl;
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
		// PHYSFS_close(sndta.fp);

		std::cout << "SOUND audio_mixer_destroy" << std::endl;
		audio_mixer_destroy(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		// PHYSFS_seek(sndta.fp, WAV_HEADER_SIZE);
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
