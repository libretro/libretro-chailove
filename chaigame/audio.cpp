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
}
