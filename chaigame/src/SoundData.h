#ifndef _SOUNDDATA_H_
#define _SOUNDDATA_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

namespace chaigame {
	class SoundData {
	public:
		Mix_Chunk* chunk = NULL;
		Mix_Music* music = NULL;
		SoundData(SDL_RWops* rw, const std::string& type);
		SoundData(const std::string& rw, const std::string& type);
		~SoundData();
		bool loaded();
		bool loadFromRW();
		bool unload();
		void play();
		std::string getType();

		SDL_RWops* loadRWops = NULL;
		std::string loadType;
	};
}

#endif
