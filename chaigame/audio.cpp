#include "audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

#include "src/SoundData.h"
#include "../Application.h"

namespace chaigame {
	void audio::play(SoundData* soundData) {
		if (soundData) {
			soundData->play();
		}
	}

	SoundData* audio::newSource(const std::string& filename, const std::string& type) {
		return Application::getInstance()->sound.newSoundData(filename, type);
	}

	SoundData* audio::newSource(const std::string& filename) {
		return Application::getInstance()->sound.newSoundData(filename);
	}
}
