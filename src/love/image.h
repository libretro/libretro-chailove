#ifndef SRC_LOVE_IMAGE_H_
#define SRC_LOVE_IMAGE_H_

#include "Types/Graphics/Image.h"
#include <string>
#include <map>

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
	 * ## Example
	 *
	 * @code
	 * var bear = love.image.newImageData("bear.png")
	 * @endcode
	 *
	 * @param filename The filename of the image file.
	 *
	 * Images can't be changed, so loading the same file again returns the same ImageData.
	 *
	 * @return The new ImageData object.
	 */
	Image* newImageData(const std::string& filename);

	private:
	std::map<std::string, Image*> m_images;
};

}  // namespace love

#endif  // SRC_LOVE_IMAGE_H_
