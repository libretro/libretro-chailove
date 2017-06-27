#ifndef _IMAGEDATA_H_INCLUDED_
#define _IMAGEDATA_H_INCLUDED_

#include <SDL.h>
#include <string>

namespace chaigame {
	class ImageData {
	public:
		SDL_Surface* surface;
		ImageData(SDL_RWops* rw);
		ImageData(std::string filename);
		~ImageData();
		bool loaded();
		bool loadFromRW(SDL_RWops* rw);
		bool destroy();
	};
}

#endif
