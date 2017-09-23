#include <vector>
#include <string>
#include "sound.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "../ChaiGame.h"
#include "audio/SoundData.h"
#include "log.h"

namespace chaigame {

	bool sound::load() {
		return true;
	}

	bool sound::update() {
		// Nothing.
	}

	void sound::unload() {
		// Unload all sounds.
		for (std::vector<SoundData*>::size_type i = 0; i != sounds.size(); i++) {
			sounds[i]->unload();
		}
	}

    SoundData* sound::newSoundData(const std::string& filename) {
    	return ChaiGame::getInstance()->audio.newSource(filename);
    }
}
