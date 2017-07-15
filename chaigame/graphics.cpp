#include "graphics.h"

#include "SDL.h"
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxBlitFunc.h>

#include "../Application.h"
#include "src/ImageData.h"
#include "src/Image.h"
#include "src/Font.h"

namespace chaigame {

	graphics::graphics() {
		activeFont = new Font();
	}

	SDL_Surface* graphics::getScreen() {
		return Application::getInstance()->screen;
	}

	bool graphics::load() {
		// Enable alpha blending.
		if (SDL_SetAlpha(getScreen(), SDL_SRCALPHA, 0) == -1) {
			Application::getInstance()->log->warn("Enabling alpha blending failed");
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

	void graphics::rectangle(const std::string& drawmode, int x, int y, int width, int height) {
		if (drawmode == "line") {
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
			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(image->surface, NULL, getScreen(), dstrect);
		}
	}

	void graphics::draw(ImageData* image, Quad quad, int x, int y) {
		if (image && image->loaded()) {
			SDL_Rect* dest = new SDL_Rect();
			dest->x = x;
			dest->y = y;
			dest->w = x + quad.width;
			dest->h = y + quad.height;
			if (SDL_gfxBlitRGBA(image->surface, quad.toRect(), getScreen(), dest) == -1) {
				Application::getInstance()->log->error("Error calling SDL_gfxBlitRGBA");
			}
		}
	}

	ImageData* graphics::newImage(const std::string& filename) {
		ImageData* image = new ImageData(filename);
		if (image->loaded()) {
			return image;
		}
		return NULL;
	}

	Quad graphics::newQuad(int x, int y, int width, int height, int sw, int sh) {
		return Quad(x, y, width, height, sw, sh);
	}

	void graphics::print(const std::string& text, int x, int y) {
		activeFont->print(text, x, y, r, g, b, a);
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

	void graphics::circle(const std::string& drawmode, int x, int y, int radius) {
		if (drawmode == "line") {
			circleRGBA(getScreen(), x, y, radius, r, g, b, a);
		}
		else {
			filledCircleRGBA(getScreen(), x, y, radius, r, g, b, a);
		}
	}

	void graphics::arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2) {
		if (drawmode == "line") {
			arcRGBA(getScreen(), x, y, radius, angle1, angle2, r, g, b, a);
		}
		else {
			filledPieRGBA(getScreen(), x, y, radius, angle1, angle2, r, g, b, a);
		}
	}

	void graphics::ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy) {
		if (drawmode == "line") {
			ellipseRGBA(getScreen(), x, y, radiusx, radiusy, r, g, b, a);
		}
		else {
			filledEllipseRGBA(getScreen(), x, y, radiusx, radiusy, r, g, b, a);
		}
	}

	Font* graphics::newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
		return new Font(filename, glyphWidth, glyphHeight, letters);
	}

	Font* graphics::newFont(const std::string& filename, int size) {
		return new Font(filename, size);
	}

	Font* graphics::newFont() {
		return new Font();
	}

	Font* graphics::newFont(const std::string& filename) {
		return newFont(filename, 12);
	}

	void graphics::setFont(Font* font) {
		activeFont = font;
	}

	void graphics::setFont() {
		activeFont = new Font();
	}

	Font* graphics::getFont() {
		return activeFont;
	}
}
