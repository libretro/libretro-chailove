#include <vector>
#include <string>
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

void sound::unload() {
	// Unload all sounds.
	for (std::vector<SoundData*>::size_type i = 0; i != sounds.size(); i++) {
		sounds[i]->unload();
	}
}

SoundData* sound::newSoundData(const std::string& filename) {
	return ChaiLove::getInstance()->audio.newSource(filename);
}

}  // namespace love
