#ifndef SRC_LOVE_IMAGE_H_
#define SRC_LOVE_IMAGE_H_

#include "Types/Graphics/Image.h"
#include <string>

using love::Types::Graphics::Image;

namespace love {

/**
 * Provides an interface to decode encoded image data.
 */
class image {
	public:
	bool load();
	bool unload();

	/**
	 * Creates a new ImageData object.
	 *
	 * @param filename The filename of the image file.
	 *
	 * @return The new ImageData object.
	 */
	Image* newImageData(const std::string& filename);
};

}  // namespace love

#endif  // SRC_LOVE_IMAGE_H_
