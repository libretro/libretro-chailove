#include "audio.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include <string>

#include "src/SoundData.h"
#include "../Application.h"

namespace chaigame {
	void audio::play(SoundData* soundData) {
		if (Application::getInstance()->sound.hasAudio()) {
			if (soundData->getType() == "music") {
				printf("MUSIC TIME\n");
				Mix_PlayMusic(soundData->music, -1);
				Mix_VolumeMusic(128);
			}
			else if (soundData->getType() == "chunk") {
				printf("CHUNK TIME\n");
				Mix_PlayChannel(-1, soundData->chunk, 0);
			}
		}
	}
}
