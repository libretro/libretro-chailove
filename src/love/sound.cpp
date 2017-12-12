#include <vector>
#include <string>
#include "sound.h"
#include "SDL.h"
#include "../ChaiLove.h"
#include "../Types/Audio/SoundData.h"

namespace love {

bool sound::load() {
	return true;
}

bool sound::update() {
	// Nothing.
}

void sound::unload() {
	// Unload all sounds.
	for (std::vector<::Types::Audio::SoundData*>::size_type i = 0; i != sounds.size(); i++) {
		sounds[i]->unload();
	}
}

::Types::Audio::SoundData* sound::newSoundData(const std::string& filename) {
	return ::ChaiLove::getInstance()->audio.newSource(filename);
}

}  // namespace love
