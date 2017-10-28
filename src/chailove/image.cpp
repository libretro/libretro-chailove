#include "image.h"
#include <string>
#include "graphics/ImageData.h"

namespace chailove {
	chailove::ImageData* image::newImageData(const std::string& filename) {
		ImageData* image = new chailove::ImageData(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	bool image::load() {
		return true;
		/*int flags = IMG_INIT_PNG | IMG_INIT_JPG;
		int initted = IMG_Init(flags);
		if(flags != (initted & flags)) {

			const char* errorChar = IMG_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			std::cout << "Failed to call IMG_Init with jpg/png: {}", errString);
			return false;
		}
		return true;*/
	}

	bool image::unload() {
		//IMG_Quit();
		return true;
	}
}
