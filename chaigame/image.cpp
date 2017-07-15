#include "image.h"
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include "src/ImageData.h"
#include "../Application.h"

namespace chaigame {
	chaigame::ImageData* image::newImageData(const std::string& filename) {
		ImageData* image = new chaigame::ImageData(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	bool image::load() {
		int flags = IMG_INIT_PNG | IMG_INIT_JPG;
		int initted = IMG_Init(flags);
		if(flags != (initted & flags)) {
		    Application::getInstance()->log->error("Failed to call IMG_Init with jpg/png: {}", IMG_GetError());
		    return false;
		}
		return true;
	}

	bool image::unload() {
		IMG_Quit();
		return true;
	}
}
