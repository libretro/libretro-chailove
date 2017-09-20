#ifndef CHAIGAME_UTILITY_IMAGEDATA_H
#define CHAIGAME_UTILITY_IMAGEDATA_H

#include <SDL.h>
#include "SDL_gpu.h"
#include <string>

namespace chaigame {
	class ImageData {
	public:
		GPU_Image* surface;
		ImageData(SDL_RWops* rw);
		ImageData(const std::string& filename);
		~ImageData();
		bool loaded();
		bool loadFromRW(SDL_RWops* rw);
		bool destroy();

		int getWidth();
		int getHeight();
	};
}

#endif
