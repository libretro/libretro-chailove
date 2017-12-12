#include "graphics.h"

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_gfxBlitFunc.h>
#include <SDL_rotozoom.h>

#include "../ChaiLove.h"
#include "../Types/Graphics/Image.h"
#include "../Types/Graphics/Font.h"
#include "../Types/Graphics/Color.h"

using Types::Graphics::Image;
using Types::Graphics::Quad;
using Types::Graphics::Font;
using Types::Graphics::Point;
using Types::Graphics::Color;

namespace love {

graphics::graphics() {
	setFont();
}

SDL_Surface* graphics::getScreen() {
	return ChaiLove::getInstance()->screen;
}

bool graphics::load() {
	// Enable alpha blending.
	if (SDL_SetAlpha(getScreen(), SDL_SRCALPHA, 0) == -1) {
		std::cout << "[ChaiLove] Enabling alpha blending failed" << std::endl;
	}

	// Set the default font.
	graphics::setFont();
	return true;
}

graphics& graphics::clear() {
	return clear(backR, backG, backB, backA);
}

graphics& graphics::clear(int r, int g, int b, int a) {
	SDL_Surface* screen = getScreen();
	Uint32 color = SDL_MapRGBA(screen->format, r, g, b, a);
	SDL_FillRect(screen, NULL, color);

	return *this;
}

graphics& graphics::clear(int r, int g, int b) {
	return clear(r, g, b, 255);
}
graphics& graphics::point(int x, int y) {
	pixelRGBA(getScreen(), x, y, r, g, b, a);

	return *this;
}
graphics& graphics::point(Point* p) {
	return point(p->x, p->y);
}
/*
TODO: Fix graphics.points(Vector<Points>)
void graphics::points(std::vector<Point*> points) {
	for (std::vector<Point*>::iterator it = points.begin() ; it != points.end(); ++it) {
		point(*it);
	}
}
void graphics::points(std::vector<Point> points) {
	for (std::vector<Point>::iterator it = points.begin() ; it != points.end(); ++it) {
		Point a = *it;
		point(a.x, a.y);
	}
}
*/

graphics& graphics::rectangle(const std::string& drawmode, int x, int y, int width, int height) {
	if (drawmode == "line") {
		rectangleRGBA(getScreen(), x, y, x + width, y + height, r, g, b, a);
	} else {
		boxRGBA(getScreen(), x, y, x + width, y + height, r, g, b, a);
	}

	return *this;
}
graphics& graphics::line(int x1, int y1, int x2, int y2) {
	lineRGBA(getScreen(), x1, y1, x2, y2, r, g, b, a);

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y) {
	if (image && image->loaded()) {
		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		SDL_BlitSurface(image->surface, NULL, getScreen(), &dstrect);
	}

	return *this;
}

graphics& graphics::draw(Image* image, Quad quad, int x, int y) {
	if (image && image->loaded()) {
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = x + quad.width;
		dest.h = y + quad.height;
		SDL_Rect src = quad.toRect();
		SDL_BlitSurface(image->surface, &src, getScreen(), &dest);
	}

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy, float ox, float oy) {
	if (image && image->loaded()) {
		ChaiLove* app = ChaiLove::getInstance();
		float angle = app->math.degrees(r);
		SDL_Surface* tempSurface = rotozoomSurfaceXY(image->surface, angle, sx, sy, m_smooth);
		if (tempSurface) {
			float aspectX = ox / image->getWidth();
			float aspectY = oy / image->getHeight();
			SDL_Rect dstrect;
			dstrect.x = x - aspectX * tempSurface->w;
			dstrect.y = y - aspectY * tempSurface->h;
			SDL_BlitSurface(tempSurface, NULL, getScreen(), &dstrect);
			SDL_FreeSurface(tempSurface);
		}
	}

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy, float ox) {
	return draw(image, x, y, r, sx, sy, ox, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy) {
	return draw(image, x, y, r, sx, sy, 0.0f, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx) {
	return draw(image, x, y, r, sx, sx, 0.0f, 0.0f);
}

graphics& graphics::draw(Image* image, int x, int y, float r) {
	if (r == 0.0f) {
		return draw(image, x, y);
	} else {
		return draw(image, x, y, r, 1.0f, 1.0f, 0.0f, 0.0f);
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

graphics& graphics::print(const std::string& text, int x, int y) {
	activeFont->print(text, x, y, r, g, b, a);

	return *this;
}

graphics& graphics::setColor(int red, int green, int blue, int alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;

	return *this;
}
graphics& graphics::setColor(int red, int green, int blue) {
	return setColor(red, green, blue, 255);
}

Color graphics::getBackgroundColor() {
	Color c;
	c.r = backR;
	c.g = backG;
	c.b = backB;
	c.a = backA;
	return c;
}
graphics& graphics::setBackgroundColor(int red, int green, int blue) {
	return setBackgroundColor(red, green, blue, 255);
}
graphics& graphics::setBackgroundColor(int red, int green, int blue, int alpha) {
	backR = red;
	backG = green;
	backB = blue;
	backA = alpha;

	return *this;
}

/**
 * @brief Sets the default scaling filters used with images, and fonts.
 */
graphics& graphics::setDefaultFilter(const std::string& filter) {
	if (filter == "linear") {
		m_smooth = 1;
	} else if (filter == "nearest") {
		m_smooth = 0;
	}

	return *this;
}

/**
 * @brief Returns the default scaling filters used with images and fonts.
 */
std::string graphics::getDefaultFilter() {
	switch (m_smooth) {
		case 0:
			return "linear";
		case 1:
			return "nearest";
	}
}


int graphics::getWidth() {
	return getScreen()->w;
}
int graphics::getHeight() {
	return getScreen()->h;
}

graphics& graphics::circle(const std::string& drawmode, int x, int y, int radius) {
	if (drawmode == "line") {
		circleRGBA(getScreen(), x, y, radius, r, g, b, a);
	} else {
		filledCircleRGBA(getScreen(), x, y, radius, r, g, b, a);
	}

	return *this;
}

graphics& graphics::arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2) {
	if (drawmode == "line") {
		arcRGBA(getScreen(), x, y, radius, angle1, angle2, r, g, b, a);
	} else {
		filledPieRGBA(getScreen(), x, y, radius, angle1, angle2, r, g, b, a);
	}

	return *this;
}

graphics& graphics::ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy) {
	if (drawmode == "line") {
		ellipseRGBA(getScreen(), x, y, radiusx, radiusy, r, g, b, a);
	} else {
		filledEllipseRGBA(getScreen(), x, y, radiusx, radiusy, r, g, b, a);
	}

	return *this;
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

graphics& graphics::setFont(Font* font) {
	activeFont = font;

	return *this;
}

graphics& graphics::setFont() {
	activeFont = &defaultFont;

	return *this;
}

Font* graphics::getFont() {
	return activeFont;
}

}  // namespace love
