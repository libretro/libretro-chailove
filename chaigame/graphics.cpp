#include "graphics.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "../Application.h"
#include "src/ImageData.h"
#include "src/Image.h"

namespace chaigame {

	bool graphics::load(SDL_Surface* renderScreen) {
		// Disable the mouse cursor from showing up.
		screen = renderScreen;
		SDL_ShowCursor(SDL_DISABLE);
		return true;
	}

	void graphics::clear() {
		clear(backR, backG, backB, backA);
	}

	void graphics::clear(int r, int g, int b, int a) {
		Uint32 color = SDL_MapRGBA(screen->format, r, g, b, a);
		SDL_FillRect(screen, NULL, color);
	}

	void graphics::clear(int r, int g, int b) {
		clear(r, g, b, 255);
	}
	void graphics::point(int x, int y) {
		pixelRGBA(screen, x, y, r, g, b, a);
	}

	void graphics::rectangle(const std::string& mode, Sint16 x, Sint16 y, Sint16 width, Sint16 height) {
		if (mode == "line") {
			rectangleRGBA(screen, x, y, x + width, y + height, r, g, b, a);
		}
		else {
			boxRGBA(screen, x, y, x + width, y + height, r, g, b, a);
		}
	}
	void graphics::line(int x1, int y1, int x2, int y2) {
		lineRGBA(screen, x1, y1, x2, y2, r, g, b, a);
	}

	void graphics::draw(ImageData* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_BlitSurface(image->surface, NULL, screen, NULL);
		}
	}

	void graphics::draw(Image* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(image->surface, NULL, screen, dstrect);
		}
	}

	Image* graphics::newImage(const std::string& filename) {
		Image* image = new Image(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	void graphics::print(const std::string& text, int x, int y) {
		stringRGBA(screen, x, y, text.c_str(), r, g, b, a);
	}

	void graphics::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	void graphics::setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue) {
		setBackgroundColor(red, green, blue, 255);
	}
	void graphics::setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
		backR = red;
		backG = green;
		backB = blue;
		backA = alpha;
	}
}
