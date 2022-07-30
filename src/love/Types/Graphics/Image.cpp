#include "Image.h"
#include "SDL.h"
#define SDL_STBIMAGE_IMPLEMENTATION
#include <SDL_stbimage.h>

#include <string>
#include "../../../ChaiLove.h"
#include "../../../LibretroLog.h"


namespace love {
namespace Types {
namespace Graphics {

Image::Image(SDL_RWops* rw) {
	loadFromRW(rw);
}

bool Image::loaded() {
	return surface != NULL;
}

bool Image::loadFromRW(SDL_RWops* rw) {
	surface = STBIMG_Load_RW(rw, 1);

	if (!loaded()) {
		const char* errorChar = SDL_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		LibretroLog::log(RETRO_LOG_ERROR) << "STBIMG_Load_RW failed to load data: " << errString << std::endl;
		return false;
	}

	// Optimize the image to the display format.
	ChaiLove* game = ChaiLove::getInstance();
	SDL_Surface* optimizedImage = NULL;
	if (game->config.options["alphablending"]) {
		optimizedImage = SDL_DisplayFormatAlpha(surface);
	} else {
		Uint32 colorkey = SDL_MapRGBA(surface->format, 0, 0, 0, 0xFF);
		SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
		optimizedImage = SDL_DisplayFormat(surface);
	}

	if (optimizedImage == NULL) {
		LibretroLog::log(RETRO_LOG_INFO) << "[ChaiLove] [graphics] Warning: SDL_DisplayFormat failed to optimize the image." << std::endl;
	} else {
		SDL_FreeSurface(surface);
		surface = optimizedImage;
	}
	return true;
}

bool Image::destroy() {
	if (loaded()) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	return true;
}

Image::~Image() {
	destroy();
}

Image::Image(const std::string& filename) {
	SDL_RWops* image = ChaiLove::getInstance()->filesystem.openRW(filename);
	loadFromRW(image);
}

int Image::getWidth() {
	if (loaded()) {
		return surface->w;
	}
	return 0;
}

int Image::getHeight() {
	if (loaded()) {
		return surface->h;
	}
	return 0;
}

}  // namespace Graphics
}  // namespace Types
}  // namespace love
