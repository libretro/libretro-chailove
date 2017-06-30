#include "SoundData.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "../../Application.h"

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
			music = Mix_LoadMUS_RW(loadRWops);
			if (!music) {
				printf("Mix_LoadMusic: %s\n", Mix_GetError());
				return false;
			}
			return true;
		}

		if (loadType == "chunk") {
			chunk = Mix_LoadWAV_RW(loadRWops, 1);
			if (!chunk) {
				printf("Mix_LoadWAV_RW: %s\n", Mix_GetError());
				return false;
			}

			return true;
		}
	}

	bool SoundData::unload() {
		// Only call Mixer functions if the audio system is up.
		if (Application::getInstance()->sound.hasAudio()) {
			if (music) {
				Mix_FreeMusic(music);
				music = NULL;
				loadRWops = NULL;
				return true;
			}
			if (chunk) {
				Mix_FreeChunk(chunk);
				chunk = NULL;
				loadRWops = NULL;
				return true;
			}
		}
		if (loadRWops) {
			SDL_RWclose(loadRWops);
			loadRWops = NULL;
		}
		return false;
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

			// If the file has successfully loaded, play the sound.
			if (music) {
				if (Mix_PlayMusic(music, -1) == -1) {
					printf("Failed to play music: %s\n", Mix_GetError());
				};
			}
			else if (chunk) {
				if (Mix_PlayChannel(-1, chunk, 0) == -1) {
					printf("Failed to play chunk: %s\n", Mix_GetError());
				};
			}
		}
	}
}
