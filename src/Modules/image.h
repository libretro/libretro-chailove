#ifndef CHAILOVE_IMAGE_H
#define CHAILOVE_IMAGE_H

#include "../Types/Graphics/Image.h"
#include <string>

using Types::Graphics::Image;

namespace Modules {

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
		Image* newImageData(const std::string& filename);
	};
}

#endif
