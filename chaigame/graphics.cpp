#include "graphics.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxBlitFunc.h>

#include "../Application.h"
#include "src/ImageData.h"
#include "src/Image.h"

namespace chaigame {


	SDL_Surface* graphics::getScreen() {
		return Application::getInstance()->screen;
	}

	bool graphics::load() {
		// Enable alpha blending.
		if (SDL_SetAlpha(getScreen(), SDL_SRCALPHA, 0) == -1) {
			printf("Warning: Enabling alpha blending failed.");
		}
		return true;
	}

	void graphics::clear() {
		clear(backR, backG, backB, backA);
	}

	void graphics::clear(int r, int g, int b, int a) {
		SDL_Surface* screen = getScreen();
		Uint32 color = SDL_MapRGBA(screen->format, r, g, b, a);
		SDL_FillRect(screen, NULL, color);
	}

	void graphics::clear(int r, int g, int b) {
		clear(r, g, b, 255);
	}
	void graphics::point(int x, int y) {
		pixelRGBA(getScreen(), x, y, r, g, b, a);
	}

	void graphics::rectangle(const std::string& mode, int x, int y, int width, int height) {
		if (mode == "line") {
			rectangleRGBA(getScreen(), x, y, x + width, y + height, r, g, b, a);
		}
		else {
			boxRGBA(getScreen(), x, y, x + width, y + height, r, g, b, a);
		}
	}
	void graphics::line(int x1, int y1, int x2, int y2) {
		lineRGBA(getScreen(), x1, y1, x2, y2, r, g, b, a);
	}

	void graphics::draw(ImageData* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_BlitSurface(image->surface, NULL, getScreen(), NULL);
		}
	}

	void graphics::draw(Image* image, int x, int y) {
		if (image && image->loaded()) {
			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(image->surface, NULL, getScreen(), dstrect);
		}
	}

	void graphics::draw(Image* image, Quad quad, int x, int y) {
		if (image && image->loaded()) {
			SDL_Rect* dest = new SDL_Rect();
			dest->x = x;
			dest->y = y;
			dest->w = x + quad.width;
			dest->h = y + quad.height;
			if (SDL_gfxBlitRGBA(image->surface, quad.toRect(), getScreen(), dest) == -1) {
				printf("Error on blitting");
			}
		}
	}

	Image* graphics::newImage(const std::string& filename) {
		Image* image = new Image(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	Quad graphics::newQuad(int x, int y, int width, int height, int sw, int sh) {
		return Quad(x, y, width, height, sw, sh);
	}

	void graphics::print(const std::string& text, int x, int y) {
		stringRGBA(getScreen(), x, y, text.c_str(), r, g, b, a);
	}

	void graphics::setColor(int red, int green, int blue, int alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	void graphics::setColor(int red, int green, int blue) {
		setColor(red, green, blue, 255);
	}
	void graphics::setBackgroundColor(int red, int green, int blue) {
		setBackgroundColor(red, green, blue, 255);
	}
	void graphics::setBackgroundColor(int red, int green, int blue, int alpha) {
		backR = red;
		backG = green;
		backB = blue;
		backA = alpha;
	}
	int graphics::getWidth() {
		return getScreen()->w;
	}
	int graphics::getHeight() {
		return getScreen()->h;
	}

	void graphics::circle(const std::string& mode, int x, int y, int radius) {
		if (mode == "line") {
			circleRGBA(getScreen(), x, y, radius, r, g, b, a);
		}
		else {
			filledCircleRGBA(getScreen(), x, y, radius, r, g, b, a);
		}
	}
}
