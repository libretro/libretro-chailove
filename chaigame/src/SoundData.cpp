#include "SoundData.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "../../Application.h"

#include <iostream>

namespace chaigame {

	SoundData::SoundData(SDL_RWops* rw, const std::string& type) {
		loadRWops = rw;
		loadType = type;
	}

	SoundData::SoundData(const std::string& file, const std::string& type) {
 		loadRWops = Application::getInstance()->filesystem.openRW(file);
 		loadType = type;
	}

	bool SoundData::loaded() {
		return (music != NULL) || (chunk != NULL);
	}

	std::string SoundData::getType() {
		if (music) {
			return "music";
		}
		if (chunk) {
			return "chunk";
		}
		return "";
	}

	bool SoundData::loadFromRW() {
		if (loadType == "music") {
			printf("Mix_LoadMUS_RW\n");
			music = Mix_LoadMUS_RW(loadRWops);
			if (!music) {
				printf("Mix_LoadMusic: %s\n", Mix_GetError());
				return false;
			}
			return true;
		}

		if (loadType == "chunk") {
			printf("Mix_LoadWAV_RW\n");
			chunk = Mix_LoadWAV_RW(loadRWops, 1);
			if (!chunk) {
				printf("Mix_LoadWAV_RW: %s\n", Mix_GetError());
				return false;
			}

			return true;
		}
	}

	bool SoundData::unload() {
		if (music) {
			printf("\nFreeMusic");
			Mix_FreeMusic(music);
			music = NULL;
			loadRWops = NULL;
		}
		if (chunk) {
			printf("\nMix_FreeChunk");
			Mix_FreeChunk(chunk);
			chunk = NULL;
			loadRWops = NULL;
		}
		if (loadRWops) {
			printf("\nSDL_RWclose");
			SDL_RWclose(loadRWops);
			loadRWops = NULL;
		}
		return true;
	}

	SoundData::~SoundData() {
		unload();
	}

	void SoundData::play() {
		// Make sure we have an audio system.
		if (Application::getInstance()->sound.hasAudio()) {
			// See if we are to load the file.
			if (!loaded() && loadRWops) {
				loadFromRW();
			}
			else {
				if (music) {
					printf("MUSIC TIME\n");
					Mix_PlayMusic(music, -1);
					//Mix_VolumeMusic(128);
				}
				else if (chunk) {
					printf("CHUNK TIME\n");
					Mix_PlayChannel(-1, chunk, 0);
				}
			}
		}
	}
}
