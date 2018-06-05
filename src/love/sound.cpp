#include <vector>
#include <string>
#include <iostream>
#include "sound.h"
#include "SDL.h"
#include "../ChaiLove.h"
#include "Types/Audio/SoundData.h"
#include "audio/audio_mixer.h"

using ::ChaiLove;
using love::Types::Audio::SoundData;

namespace love {

void sound::convert_float_to_s16(int16_t *out, const float *in, size_t samples) {
	size_t i = 0;
	for (; i < samples; i++)
	{
		int32_t val = (int32_t)(in[i] * 0x8000);
		out[i] = (val > 0x7FFF) ? 0x7FFF : (val < -0x8000 ? -0x8000 : (int16_t)val);
	}
}

bool sound::load() {
/*
	float samples[BUFSIZE * 2] = {0};
	int16_t samples2[2 * BUFSIZE] = {0};
	audio_mixer_mix(samples, BUFSIZE, 1.0, false);
	convert_float_to_s16(samples2, samples, 2 * BUFSIZE);
*/

	audio_mixer_init(44100);
	m_loaded = true;
	return true;
}

sound::~sound() {
	unload();
}

bool sound::isLoaded() {
	return m_loaded;
}

void sound::unload() {
	// Unload all sounds.
	for (std::vector<SoundData*>::size_type i = 0; i != sounds.size(); i++) {
		if (sounds[i] != NULL) {
			delete sounds[i];
		}
	}
	sounds.clear();

	audio_mixer_done();
	m_loaded = false;
}

SoundData* sound::newSoundData(const std::string& filename) {
	return ChaiLove::getInstance()->audio.newSource(filename);
}

}  // namespace love
