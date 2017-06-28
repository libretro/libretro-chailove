#include "ImageData.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "../../Application.h"

namespace chaigame {

	ImageData::ImageData(SDL_RWops* rw) {
		loadFromRW(rw);
	}

	bool ImageData::loaded() {
		return surface != NULL;
	}

	bool ImageData::loadFromRW(SDL_RWops* rw) {
		surface = IMG_Load_RW(rw, 1);

		if (!surface) {
			printf("IMG_Load_RW: %s\n", IMG_GetError());
			return false;
		}
		return true;
	}

	bool ImageData::destroy() {
		printf("DESTROY IMAGE");
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
		SDL_RWops* image = Application::getInstance()->filesystem.openRW(filename);
		loadFromRW(image);
	}
}
