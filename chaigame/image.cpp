#include "image.h"
#include "../Application.h"
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include "src/ImageData.h"

namespace chaigame {
	chaigame::ImageData* image::newImageData(std::string filename) {
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
		    printf("IMG_Init: Failed to init required jpg and png support!\n");
		    printf("IMG_Init: %s\n", IMG_GetError());
		    return false;
		}
		return true;
	}

	bool image::unload() {
		IMG_Quit();
		return true;
	}
}
