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
};

}  // namespace love

#endif  // SRC_LOVE_IMAGE_H_
