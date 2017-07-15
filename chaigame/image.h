#ifndef _IMAGE_H_INCLUDED_
#define _IMAGE_H_INCLUDED_

#include "src/ImageData.h"
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
