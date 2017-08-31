#ifndef CHAIGAME_IMAGE_H
#define CHAIGAME_IMAGE_H

#include "graphics/ImageData.h"
#include <string>

namespace chaigame {
	class image {
	public:
		bool load();
		bool unload();
		chaigame::ImageData* newImageData(const std::string& filename);
	};
}

#endif
