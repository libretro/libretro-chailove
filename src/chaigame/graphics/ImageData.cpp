#include "ImageData.h"
#include "SDL.h"
#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

#include <iostream>
#include <string>
#include "../../ChaiGame.h"


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
			std::cout << "STBIMG_Load_RW failed to load data: " << errString << std::endl;
			return false;
		}

		// Optimize the image to the display format.
		ChaiGame* game = ChaiGame::getInstance();
		SDL_Surface* optimizedImage = NULL;
		if (game->config.options["alphablending"]) {
			optimizedImage = SDL_DisplayFormatAlpha(surface);
		}
		else {
			Uint32 colorkey = SDL_MapRGBA(surface->format, 0, 0, 0, 0xFF);
			SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
			optimizedImage = SDL_DisplayFormat(surface);
		}
		if (!optimizedImage) {
			std::cout << "SDL_DisplayFormat failed to optimize the image." << std::endl;
		}
		else {
			SDL_FreeSurface(surface);
			surface = optimizedImage;
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
		SDL_RWops* image = ChaiGame::getInstance()->filesystem.openRW(filename);
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
