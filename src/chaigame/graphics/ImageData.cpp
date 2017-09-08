#include "ImageData.h"
#include "SDL.h"
#include "SDL_gpu.h"

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
		surface = GPU_LoadImage_RW(rw, 1);

		if (!surface) {
			const char* errorChar = SDL_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->error("GPU_LoadImage_RW failed to load data: {}", errString);
			return false;
		}
		return true;
	}

	bool ImageData::destroy() {
		if (!surface) {
			GPU_FreeImage(surface);
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
