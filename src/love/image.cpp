#include "image.h"
#include <string>
#include <list>
#include "Types/Graphics/Image.h"

using love::Types::Graphics::Image;

namespace love {

Image* image::newImageData(const std::string& filename) {
	Image* image = new Image(filename);
	if (image->loaded()) {
		m_images.push_back(image);
		return image;
	}
	delete image;
	return NULL;
}

bool image::load() {
	return true;
}

bool image::unload() {
	for (std::list<Image*>::iterator it = m_images.begin(); it != m_images.end(); ++it) {
		if (*it != NULL) {
	    	delete *it;
	    }
	}
	m_images.clear();
	return true;
}

}  // namespace love
