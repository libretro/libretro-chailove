#include "SoundData.h"
//#include "SDL.h"
//#include "SDL_mixer.h"
#include <string>
#include "../../Game.h"
#include "../log.h"

namespace chaigame {

	/*SoundData::SoundData(SDL_RWops* rw, const std::string& type) {
		loadRWops = rw;
		loadType = type;
	}*/

	SoundData::SoundData(const std::string& file, const std::string& type) {
 		//loadRWops = Game::getInstance()->filesystem.openRW(file);
 		//loadType = type;
	}

	bool SoundData::loaded() {
		return true;
		//return (music != NULL) || (chunk != NULL);
	}

	std::string SoundData::getType() {
		//if (music) {
			return "stream";
		//}
		//if (chunk) {
			return "static";
		//}
		return "";
	}

	/*bool SoundData::loadFromRW() {
		if (loadType == "stream") {
			music = Mix_LoadMUS_RW(loadRWops);
			if (!music) {
				const char* errChar = Mix_GetError();
				std::string errString("");
				if (errChar != NULL) {
					errString = errChar;
				}
				log()->error("Mix_LoadMusic: {}", errString);
				return false;
			}
			return true;
		}

		if (loadType == "static") {
			chunk = Mix_LoadWAV_RW(loadRWops, 1);
			if (!chunk) {
				const char* errChar = Mix_GetError();
				std::string errString("");
				if (errChar != NULL) {
					errString = errChar;
				}
				log()->error("Mix_LoadWAV_RW: {}", errString);
				return false;
			}

			return true;
		}

		printf("loadType must be either 'stream' or 'static'.");
		return false;
	}*/

	bool SoundData::unload() {
		// Only call Mixer functions if the audio system is up.
		/*Game* app = Game::getInstance();
		if (app != NULL && app->sound.hasAudio()) {
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
		}*/
		return false;
	}

	void SoundData::play() {
		/*Game* app = Game::getInstance();
		// Make sure we have an audio system.
		if (app && app->sound.hasAudio()) {
			// See if we are to load the file.
			if (!loaded() && loadRWops) {
				loadFromRW();
			}

			// If the file has successfully loaded, play the sound.
			if (music) {
				if (Mix_PlayMusic(music, -1) == -1) {
					const char* errChar = Mix_GetError();
					std::string errString("");
					if (errChar != NULL) {
						errString = errChar;
					}
					log()->error("Failed to play music: {}", errString);
				};
			}
			else if (chunk) {
				if (Mix_PlayChannel(-1, chunk, 0) == -1) {
					const char* errChar = Mix_GetError();
					std::string errString("");
					if (errChar != NULL) {
						errString = errChar;
					}
					log()->error("Failed to play chunk: {}", errString);
				};
			}
		}*/
	}
}
