#ifndef CHAILOVE_IMAGE_H
#define CHAILOVE_IMAGE_H

#include "graphics/ImageData.h"
#include <string>

namespace chailove {
	class image {
	public:
		bool load();
		bool unload();
		chailove::ImageData* newImageData(const std::string& filename);
	};
}

#endif
