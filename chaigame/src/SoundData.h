#ifndef _SOUNDDATA_H_
#define _SOUNDDATA_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

namespace chaigame {
	class SoundData {
	public:
		Mix_Chunk* chunk;
		Mix_Music* music;
		SoundData(SDL_RWops* rw, const std::string& type);
		SoundData(const std::string& filename, const std::string& type);
		~SoundData();
		bool loaded();
		bool loadFromRW(SDL_RWops* rw, const std::string& type);
		bool destroy();
		std::string getType();

		std::string type;
	};
}

#endif
