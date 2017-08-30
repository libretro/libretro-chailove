#include "ImageData.h"
#include "SDL.h"
#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

#include <string>
#include "../../Game.h"
#include "../log.h"

namespace chaigame {

	ImageData::ImageData(SDL_RWops* rw) {
		loadFromRW(rw);
	}

	bool ImageData::loaded() {
		return surface != NULL;
	}

	bool ImageData::loadFromRW(SDL_RWops* rw) {
		surface = STBIMG_Load_RW(rw, 1);

		if (!surface) {
			const char* errorChar = SDL_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->error("STBIMG_Load_RW failed to load data: {}", errString);
			return false;
		}
		return true;
	}

	bool ImageData::destroy() {
		if (!surface) {
			SDL_FreeSurface(surface);
			surface = NULL;
		}
		return true;
	}

	ImageData::~ImageData() {
		destroy();
	}

	ImageData::ImageData(const std::string& filename) {
		SDL_RWops* image = Game::getInstance()->filesystem.openRW(filename);
		loadFromRW(image);
	}

	int ImageData::getWidth() {
		if (surface != NULL) {
			return surface->w;
		}
		return 0;
	}

	int ImageData::getHeight() {
		if (surface != NULL) {
			return surface->h;
		}
		return 0;
	}
}
