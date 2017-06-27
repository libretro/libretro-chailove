
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "graphics.h"
#include "../Application.h"
#include "src/ImageData.h"
#include "src/Image.h"

namespace chaigame {
	void graphics::rectangle(Sint16 x, Sint16 y, Sint16 width, Sint16 height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		rectangleRGBA(Application::getInstance()->screen, x, y, x + width, y + height, r, g, b, a);
	}

	void graphics::draw(ImageData* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_BlitSurface(image->surface, NULL, Application::getInstance()->screen, NULL);
		}
	}

	void graphics::draw(Image* image) {
		if (image && image->loaded()) {
			SDL_BlitSurface(image->surface, NULL, Application::getInstance()->screen, NULL);
		}
	}

	Image* graphics::newImage(std::string filename) {
		Image* image = new Image(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

}
