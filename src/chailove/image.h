#ifndef CHAILOVE_IMAGE_H
#define CHAILOVE_IMAGE_H

#include "graphics/Image.h"
#include <string>

namespace chailove {
	class image {
	public:
		bool load();
		bool unload();
		chailove::Image* newImage(const std::string& filename);
	};
}

#endif
