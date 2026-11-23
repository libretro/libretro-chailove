#include "graphics.h"

#include "../ChaiLove.h"
#include "Types/Graphics/Image.h"
#include "Types/Graphics/Font.h"
#include "Types/Graphics/Color.h"

#include <limits>
#include <vector>

using love::Types::Graphics::Image;
using love::Types::Graphics::Quad;
using love::Types::Graphics::Font;
using love::Types::Graphics::Point;
using love::Types::Graphics::Color;

namespace love {

graphics::graphics() {
	setFont();
}

pntr_image* graphics::getScreen() {
	if (m_app != NULL) {
		return m_app->screen;
	}
	return NULL;
}

bool graphics::load(pntr_app* app) {
	// Set the default font.
	graphics::setFont();

	// Match the default colors of Love2D
	color_back = pntr_new_color(0, 0, 0, 255); // Black
	color_front = pntr_new_color(255, 255, 255, 255); // White

	m_app = app;

	return true;
}

graphics& graphics::clear() {
	pntr_clear_background(getScreen(), color_back);
	return *this;
}

graphics& graphics::clear(int r, int g, int b, int a) {
	pntr_clear_background(getScreen(), pntr_new_color(r, g, b, a));
	return *this;
}

graphics& graphics::clear(int r, int g, int b) {
	return clear(r, g, b, 255);
}

graphics& graphics::point(int x, int y) {
	pntr_draw_point(getScreen(), x, y, color_front);
	return *this;
}

graphics& graphics::point(Point* p) {
	return point(p->x, p->y);
}

namespace {

/**
 * Converts a script coordinate to a pixel, keeping out-of-range values within an int.
 */
int toPixel(double value) {
	if (!(value > -2147483648.0)) {
		// Negative overflow, or NaN.
		return std::numeric_limits<int>::min();
	}
	if (value > 2147483647.0) {
		return std::numeric_limits<int>::max();
	}
	return static_cast<int>(value);
}

/**
 * Reads a number from a script value, returning false when it is not a number.
 */
bool toNumber(const chaiscript::Boxed_Value& value, double* output) {
	if (!value.get_type_info().is_arithmetic()) {
		return false;
	}
	*output = chaiscript::Boxed_Number(value).get_as<double>();
	return true;
}

}  // namespace

graphics& graphics::points(const std::vector<chaiscript::Boxed_Value>& points) {
	std::vector<pntr_vector> vectors;
	vectors.reserve(points.size());

	// Numbers are read in x and y pairs.
	bool hasX = false;
	double x = 0;
	double number;

	for (const chaiscript::Boxed_Value& value : points) {
		if (toNumber(value, &number)) {
			if (hasX) {
				vectors.push_back(pntr_vector{toPixel(x), toPixel(number)});
			} else {
				x = number;
			}
			hasX = !hasX;
			continue;
		}

		// A Point.
		try {
			const Point& p = chaiscript::boxed_cast<const Point&>(value);
			vectors.push_back(pntr_vector{toPixel(p.x), toPixel(p.y)});
			continue;
		} catch (const chaiscript::exception::bad_boxed_cast&) {
			// Not a Point.
		}

		// A nested [x, y] vector.
		try {
			const std::vector<chaiscript::Boxed_Value>& pair = chaiscript::boxed_cast<const std::vector<chaiscript::Boxed_Value>&>(value);
			double pairX, pairY;
			if (pair.size() >= 2 && toNumber(pair[0], &pairX) && toNumber(pair[1], &pairY)) {
				vectors.push_back(pntr_vector{toPixel(pairX), toPixel(pairY)});
			}
		} catch (const chaiscript::exception::bad_boxed_cast&) {
			// Unsupported values are skipped.
		}
	}

	if (!vectors.empty()) {
		pntr_draw_points(getScreen(), vectors.data(), static_cast<int>(vectors.size()), color_front);
	}

	return *this;
}

graphics& graphics::rectangle(const std::string& drawmode, int x, int y, int width, int height) {
	if (drawmode == "line") {
		pntr_draw_rectangle(getScreen(), x, y, width, height, color_front);
	} else {
		pntr_draw_rectangle_fill(getScreen(), x, y, width, height, color_front);
	}

	return *this;
}

graphics& graphics::line(int x1, int y1, int x2, int y2) {
	pntr_draw_line(getScreen(), x1, y1, x2, y2, color_front);
	return *this;
}

graphics& graphics::draw(Image* image) {
	return draw(image, 0, 0);
}

graphics& graphics::draw(Image* image, int x, int y) {
	if (image && image->loaded()) {
		pntr_draw_image(getScreen(), image->surface, x, y);
	}

	return *this;
}

graphics& graphics::draw(Image* image, Quad quad) {
	return draw(image, quad, 0, 0);
}

graphics& graphics::draw(Image* image, Quad quad, int x, int y) {
	if (image && image->loaded()) {
		pntr_rectangle srcRect;
		srcRect.x = quad.x;
		srcRect.y = quad.x;
		srcRect.width = quad.sw;
		srcRect.height = quad.sh;
		pntr_draw_image_rec(getScreen(), image->surface, quad.toRect(), x, y);
	}

	return *this;
}

graphics& graphics::draw(Image* image, int x, int y, float r, float sx, float sy, float ox, float oy) {
	if (image == NULL || !image->loaded()) {
		return *this;
	}

	// Scaled.
	if (r == 0.0f) {
		pntr_draw_image_scaled(getScreen(), image->surface, x, y, sx, sy, ox, oy, m_smooth, PNTR_WHITE);
		return *this;
	}

	// Just rotated
	ChaiLove* chailove = ChaiLove::getInstance();
	float degrees = chailove->math.degrees(r);
	if (sx == 1.0f && sy == 1.0f) {
		pntr_draw_image_rotated(getScreen(), image->surface, x, y, degrees, ox, oy, m_smooth);
		return *this;
	}

	// Rotated and scaled, with the origin given in unscaled image pixels.
	pntr_rectangle srcRect = {0, 0, 0, 0};
	pntr_draw_image_rotozoom(getScreen(), image->surface, srcRect, x, y, degrees, sx, sy, ox, oy, m_smooth, PNTR_WHITE);

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
	}

	return draw(image, x, y, r, 1.0f, 1.0f, 0.0f, 0.0f);
}

Image* graphics::newImage(const std::string& filename) {
	return ChaiLove::getInstance()->image.newImageData(filename);
}

Quad graphics::newQuad(int x, int y, int width, int height, int sw, int sh) {
	return Quad(x, y, width, height, sw, sh);
}

graphics& graphics::print(const std::string& text) {
	activeFont->print(text, 0, 0, color_front);
	return *this;
}

graphics& graphics::print(const std::string& text, int x, int y) {
	activeFont->print(text, x, y, color_front);
	return *this;
}

graphics& graphics::setColor(int red, int green, int blue, int alpha) {
	color_front = pntr_new_color(red, green, blue, alpha);
	return *this;
}

graphics& graphics::setColor(int red, int green, int blue) {
	return setColor(red, green, blue, 255);
}

Color graphics::getColor() {
	return color_front;
}

Color graphics::getBackgroundColor() {
	return color_back;
}
graphics& graphics::setBackgroundColor(int red, int green, int blue) {
	return setBackgroundColor(red, green, blue, 255);
}
graphics& graphics::setBackgroundColor(int red, int green, int blue, int alpha) {
	color_back = pntr_new_color(red, green, blue, alpha);
	return *this;
}

/**
 * Sets the default scaling filters used with images, and fonts.
 */
graphics& graphics::setDefaultFilter(const std::string& filter) {
	if (filter == "linear") {
		m_smooth = PNTR_FILTER_BILINEAR;
	} else if (filter == "nearest") {
		m_smooth = PNTR_FILTER_NEARESTNEIGHBOR;
	}

	return *this;
}

/**
 * Returns the default scaling filters used with images and fonts.
 */
std::string graphics::getDefaultFilter() {
	switch (m_smooth) {
		case PNTR_FILTER_NEARESTNEIGHBOR:
			return "nearest";
		case PNTR_FILTER_BILINEAR:
			return "linear";
	}

	return "nearest";
}

int graphics::getWidth() {
	return pntr_app_width(m_app);
}
int graphics::getHeight() {
	return pntr_app_height(m_app);
}

Point graphics::getDimensions() {
	return Point(getWidth(), getHeight());
}

graphics& graphics::circle(const std::string& drawmode, int x, int y, int radius) {
	if (drawmode == "line") {
		pntr_draw_circle(getScreen(), x, y, radius, color_front);
	} else {
		pntr_draw_circle_fill(getScreen(), x, y, radius, color_front);
	}

	return *this;
}

graphics& graphics::arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2) {
	if (drawmode == "line") {
		pntr_draw_arc(getScreen(), x, y, radius, angle1, angle2, radius * 2, color_front);
	} else {
		pntr_draw_arc_fill(getScreen(), x, y, radius, angle1, angle2, radius * 2, color_front);
	}

	return *this;
}

graphics& graphics::ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy) {
	if (drawmode == "line") {
		pntr_draw_ellipse(getScreen(), x, y, radiusx, radiusy, color_front);
	} else {
		pntr_draw_ellipse_fill(getScreen(), x, y, radiusx, radiusy, color_front);
	}

	return *this;
}

Font* graphics::newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
	std::string key = filename + ":" + std::to_string(glyphWidth) + "x" + std::to_string(glyphHeight) + ":" + letters;
	return ChaiLove::getInstance()->font.get(key, [&] { return new Font(filename, glyphWidth, glyphHeight, letters); });
}

Font* graphics::newFont(const std::string& filename, int size) {
	std::string key = filename + ":" + std::to_string(size);
	return ChaiLove::getInstance()->font.get(key, [&] { return new Font(filename, size); });
}

Font* graphics::newFont(const std::string& filename) {
	return newFont(filename, 16);
}

Font* graphics::newFont() {
	return newFont(13);
}

Font* graphics::newFont(int size) {
	// Not a valid file name, so it can't clash with the TrueType font keys.
	std::string key = ":default:" + std::to_string(size);
	return ChaiLove::getInstance()->font.get(key, [&] { return new Font(size); });
}

graphics& graphics::setFont(Font* font) {
	if (font != NULL) {
		activeFont = font;
	}
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
