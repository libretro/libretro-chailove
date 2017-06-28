#include "graphics.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Application.h"
#include "src/ImageData.h"
#include "src/Image.h"

namespace chaigame {

	bool graphics::load() {
		r = 255;
		g = 0;
		b = 0;
		a = 255;
		return true;
	}

	void graphics::rectangle(Sint16 x, Sint16 y, Sint16 width, Sint16 height, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		rectangleRGBA(Application::getInstance()->screen, x, y, x + width, y + height, r, g, b, a);
	}

	void graphics::draw(ImageData* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_BlitSurface(image->surface, NULL, Application::getInstance()->screen, NULL);
		}
	}

	void graphics::draw(Image* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(image->surface, NULL, Application::getInstance()->screen, dstrect);
		}
	}

	Image* graphics::newImage(std::string filename) {
		Image* image = new Image(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	void graphics::print(const std::string& text, int x, int y) {
		stringRGBA(Application::getInstance()->screen, x, y, text.c_str(), r, g, b, a);
	}

	void graphics::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
}
