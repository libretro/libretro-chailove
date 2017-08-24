#include "sound.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "../Game.h"
#include <vector>
#include <string>
#include "src/SoundData.h"
#include "log.h"

namespace chaigame {
	bool sound::load() {
		/*toInit = true;
		int flags = MIX_INIT_OGG | MIX_INIT_MOD;
		int initted = Mix_Init(flags);
		if ((initted & flags) != flags) {
			const char* errorChar = Mix_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->error("[sound] Mix_Init() failed requiring ogg and mod support: {}", errString);
			return false;
		}*/
		return loaded = true;
	}

	bool sound::hasAudio() {
		return initialized;
	}

	bool sound::update() {
		/*if (firstRun && toInit) {
			firstRun = false;
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
				const char* errorChar = Mix_GetError();
				std::string errString("");
				if (errorChar != NULL) {
					errString = errorChar;
				}
				log()->error("Mix_OpenAudio: {}", errString);
				return false;
			}

			numtimesopened = Mix_QuerySpec(&frequency, &format, &channels);
			if (!numtimesopened) {
				const char* errorChar = Mix_GetError();
				std::string errString("");
				if (errorChar != NULL) {
					errString = errorChar;
				}
				log()->error("Mix_QuerySpec: {}", errString);
				return false;
			}
			initialized = true;
			std::string format_str="Unknown";
			switch(format) {
				case AUDIO_U8: format_str="U8"; break;
				case AUDIO_S8: format_str="S8"; break;
				case AUDIO_U16LSB: format_str="U16LSB"; break;
				case AUDIO_S16LSB: format_str="S16LSB"; break;
				case AUDIO_U16MSB: format_str="U16MSB"; break;
				case AUDIO_S16MSB: format_str="S16MSB"; break;
			}
			// printf("\n  opened=%d times\n  frequency=%dHz\n  format=%s\n  channels=%d\n", numtimesopened, frequency, format_str.c_str(), channels);

		}
		*/
		return initialized;
	}

	void sound::unload() {
		// Unload all sounds.
		for (std::vector<SoundData*>::size_type i = 0; i != sounds.size(); i++) {
			sounds[i]->unload();
		}
/*
		// Unload SDL_Mixer.
		if (loaded) {
			log()->info("Mix_Quit(): Starting");
			Mix_Quit();
			log()->info("Mix_Quit(): Finished");
			loaded = false;
		}

		// Unload the audio system.
		if (initialized) {
			log()->info("Mix_CloseAudio: Starting");
			Mix_CloseAudio();
			log()->info("Mix_CloseAudio: Finished");
			initialized = false;
		}*/
	}

	SoundData* sound::newSoundData(const std::string& file, const std::string& type) {
		/*SDL_RWops* rw = Game::getInstance()->filesystem.openRW(file);
		if (rw) {
			SoundData* newSound = new SoundData(rw, type);
			sounds.push_back(newSound);
			return newSound;
		}*/
		log()->error("Error loading newSoundData('{}', '{}')", file, type);
		return NULL;
	}

	SoundData* sound::newSoundData(const std::string& file) {
		return newSoundData(file, "static");
	}
}
