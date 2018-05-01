#include <vector>
#include <string>
#include <iostream>
#include "sound.h"
#include "SDL.h"
#include "../ChaiLove.h"
#include "Types/Audio/SoundData.h"

using ::ChaiLove;
using love::Types::Audio::SoundData;

namespace love {

bool sound::load() {
	return true;
}

sound::~sound() {
	unload();
}

void sound::unload() {
	// Unload all sounds.
	for (std::vector<SoundData*>::size_type i = 0; i != sounds.size(); i++) {
		if (sounds[i] != NULL) {
			delete sounds[i];
			sounds[i] = NULL;
		}
	}
	sounds.clear();
}

SoundData* sound::newSoundData(const std::string& filename) {
	return ChaiLove::getInstance()->audio.newSource(filename);
}

}  // namespace love
