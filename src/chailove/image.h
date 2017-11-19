#ifndef CHAILOVE_IMAGE_H
#define CHAILOVE_IMAGE_H

#include "graphics/Image.h"
#include <string>

namespace chailove {
	/**
	 * @brief Provides an interface to decode encoded image data.
	 */
	class image {
	public:
		bool load();
		bool unload();
		/**
		 * @brief Creates a new ImageData object.
		 */
		chailove::Image* newImageData(const std::string& filename);
	};
}

#endif
