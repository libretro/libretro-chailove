#include "graphics.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxBlitFunc.h>

#include "../Game.h"
#include "graphics/ImageData.h"
#include "graphics/Image.h"
#include "graphics/Font.h"
#include "graphics/Color.h"
#include "log.h"

namespace chaigame {

	graphics::graphics() {
		activeFont = new Font();
	}

	GPU_Target* graphics::getScreen() {
		return Game::getInstance()->screen;
	}

	bool graphics::load() {
		// Enable alpha blending.
		//if (SDL_SetAlpha(getScreen(), SDL_SRCALPHA, 0) == -1) {
		//	log()->warn("Enabling alpha blending failed");
		//}

		return true;
	}

	void graphics::clear() {
		clear(backColor.r, backColor.g, backColor.b, backColor.a);
	}

	void graphics::clear(int r, int g, int b, int a) {
		GPU_Target* screen = getScreen();
		GPU_ClearRGBA(screen, r, g, b, a);
	}

	void graphics::clear(int r, int g, int b) {
		GPU_Target* screen = getScreen();
		GPU_ClearRGB(screen, r, g, b);
	}
	void graphics::point(float x, float y) {
		GPU_Pixel(getScreen(), x, y, color.toSDLColor());
	}

	void graphics::rectangle(const std::string& drawmode, float x, float y, float width, float height) {
		if (drawmode == "line") {
			GPU_Rectangle(getScreen(), x, y, x + width, y + height, color.toSDLColor());
		}
		else {
			GPU_RectangleFilled(getScreen(), x, y, x + width, y + height, color.toSDLColor());
		}
	}
	void graphics::line(float x1, float y1, float x2, float y2) {
		GPU_Line(getScreen(), x1, y1, x2, y2, color.toSDLColor());
	}

	void graphics::draw(ImageData* image, float x, float y) {
		if (image && image->loaded()) {
			GPU_Blit(image->surface, NULL, getScreen(), x, y);
		}
	}

	void graphics::draw(ImageData* image, Quad quad, float x, float y) {
		if (image && image->loaded()) {
			GPU_Rect* src = new GPU_Rect();
			src->x = x;
			src->y = y;
			src->w = x + quad.width;
			src->h = y + quad.height;
			GPU_Blit(image->surface, quad.toRect(), getScreen(), x, y);
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

	void graphics::print(const std::string& text, float x, float y) {
		activeFont->print(text, x, y, color.r, color.g, color.b, color.a);
	}

	void graphics::setColor(int red, int green, int blue, int alpha) {
		color.r = red;
		color.g = green;
		color.b = blue;
		color.a = alpha;
	}
	void graphics::setColor(int red, int green, int blue) {
		setColor(red, green, blue, 255);
	}
	void graphics::setBackgroundColor(int red, int green, int blue) {
		setBackgroundColor(red, green, blue, 255);
	}
	void graphics::setBackgroundColor(int red, int green, int blue, int alpha) {
		backColor.r = red;
		backColor.g = green;
		backColor.b = blue;
		backColor.a = alpha;
	}
	int graphics::getWidth() {
		return getScreen()->w;
	}
	int graphics::getHeight() {
		return getScreen()->h;
	}

	void graphics::circle(const std::string& drawmode, float x, float y, float radius) {
		if (drawmode == "line") {
			GPU_Circle(getScreen(), x, y, radius, color.toSDLColor());
		}
		else {
			GPU_CircleFilled(getScreen(), x, y, radius, color.toSDLColor());
		}
	}

	void graphics::arc(const std::string& drawmode, float x, float y, float radius, float start_angle, float end_angle) {
		if (drawmode == "line") {
			GPU_Arc(getScreen(), x, y, radius, start_angle, end_angle, color.toSDLColor());
		}
		else {
			GPU_ArcFilled(getScreen(), x, y, radius, start_angle, end_angle, color.toSDLColor());
		}
	}

	void graphics::ellipse(const std::string& drawmode, float x, float y, float radiusx, float radiusy, float degrees) {
		if (drawmode == "line") {
			GPU_Ellipse(getScreen(), x, y, radiusx, radiusy, degrees, color.toSDLColor());
		}
		else {
			GPU_EllipseFilled(getScreen(), x, y, radiusx, radiusy, degrees, color.toSDLColor());
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
