#ifndef SRC_MODULES_IMAGE_H_
#define SRC_MODULES_IMAGE_H_

#include "../Types/Graphics/Image.h"
#include <string>

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
	::Types::Graphics::Image* newImageData(const std::string& filename);
};

}  // namespace Modules

#endif  // SRC_MODULES_IMAGE_H_
