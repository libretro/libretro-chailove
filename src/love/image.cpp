#include "image.h"
#include <string>
#include <map>
#include "Types/Graphics/Image.h"

using love::Types::Graphics::Image;

namespace love {

Image* image::newImageData(const std::string& filename) {
	std::map<std::string, Image*>::iterator it = m_images.find(filename);
	if (it != m_images.end()) {
		return it->second;
	}

	Image* image = new Image(filename);
	if (image->loaded()) {
		m_images[filename] = image;
		return image;
	}
	delete image;
	return NULL;
}

bool image::load() {
	return true;
}

bool image::unload() {
	for (std::map<std::string, Image*>::iterator it = m_images.begin(); it != m_images.end(); ++it) {
		delete it->second;
	}
	m_images.clear();
	return true;
}

}  // namespace love
