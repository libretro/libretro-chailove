#include "SoundData.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "../../Application.h"

#include <iostream>

namespace chaigame {

	SoundData::SoundData(SDL_RWops* rw, const std::string& type) {
		loadFromRW(rw, type);
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

	bool SoundData::loadFromRW(SDL_RWops* rw, const std::string& type) {
		if (type == "music") {
			music = Mix_LoadMUS_RW(rw);
			if (!music) {
				printf("Mix_LoadMusic: %s\n", Mix_GetError());
				return false;
			}
			return true;
		}

		chunk = Mix_LoadWAV_RW(rw, 1);
		if (!chunk) {
			printf("Mix_LoadMusic: %s\n", Mix_GetError());
			return false;
		}

		return true;
	}

	bool SoundData::destroy() {
		if (music) {
			Mix_HaltMusic();
			Mix_FreeMusic(music);
			music = NULL;
		}
		if (chunk) {
			Mix_FreeChunk(chunk);
			chunk = NULL;
		}
		return true;
	}

	SoundData::~SoundData() {
		destroy();
	}

	SoundData::SoundData(const std::string& filename, const std::string& type) {
		SDL_RWops* file = Application::getInstance()->filesystem.openRW(filename);
		if (file) {
			loadFromRW(file, type);
		}
	}
}
