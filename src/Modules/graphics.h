#ifndef SRC_MODULES_GRAPHICS_H_
#define SRC_MODULES_GRAPHICS_H_

#include <vector>

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "../Types/Graphics/Image.h"
#include "../Types/Graphics/Quad.h"
#include "../Types/Graphics/Font.h"
#include "../Types/Graphics/Point.h"
#include "../Types/Graphics/Color.h"

using Types::Graphics::Image;
using Types::Graphics::Quad;
using Types::Graphics::Font;
using Types::Graphics::Point;
using Types::Graphics::Color;

namespace Modules {

/**
 * @brief The primary purpose of the graphics module is to draw to the screen.
 */
class graphics {
	public:
	graphics();
	bool load();

	/**
	 * @brief Draws a rectangle.
	 *
	 * @param drawmode How to draw the rectangle. Can be "fill" or "line".
	 * @param x The position of top-left corner along the x-axis.
	 * @param y The position of top-left corner along the y-axis.
	 * @param width Width of the rectangle.
	 * @param height Height of the rectangle.
	 *
	 * @code
	 * love.graphics.rectangle("fill", 100, 100, 50, 50)
	 * @endcode
	 */
	void rectangle(const std::string& drawmode, int x, int y, int width, int height);

	/**
	 * @brief Clears the screen to the set background color.
	 */
	void clear();

	/**
	 * @brief Clears the screen to the given background color.
	 */
	void clear(int r, int g, int b, int a);

	/**
	 * @brief Clears the screen to the given background color.
	 */
	void clear(int r, int g, int b);

	/**
	 * @brief Draws a point.
	 */
	void point(int x, int y);

	/**
	 * @brief Draws a point.
	 */
	void point(Point* p);

	// void points(std::vector<Point*>);
	// void points(std::vector<Point>);

	/**
	 * @brief Draws a line.
	 */
	void line(int x1, int y1, int x2, int y2);


	/**
	 * @brief Draws an image on screen.
	 *
	 * @param image The image to draw on the screen.
	 * @param x The position to draw the object (x-axis).
	 * @param y The position to draw the object (y-axis).
	 */
	void draw(Image* image, int x, int y);

	/**
	 * @brief Draws an image on screen, using the given Quad as a source.
	 */
	void draw(Image* image, Quad quad, int x, int y);

	/**
	 * @brief Creates a new Quad.
	 */
	Quad newQuad(int x, int y, int width, int height, int sw, int sh);

	/**
	 * @brief Creates a new Image from a given filepath.
	 *
	 * @param filename The filepath to the image file.
	 *
	 * @return An image object which can be drawn to the screen.
	 */
	Image* newImage(const std::string& filename);

	Font* newFont();

	/**
	 * @brief Creates a new TrueType font, with a default size of 12.
	 *
	 * @param filename The path to the TrueType font.
	 *
	 * @return The created TrueType font.
	 */
	Font* newFont(const std::string& filename);

	/**
	 * @brief Creates a new TrueType font, with the given font size.
	 *
	 * @param filename The path to the TrueType font.
	 * @param size The size of the font to create.
	 *
	 * @return The created TrueType font.
	 */
	Font* newFont(const std::string& filename, int size);

	/**
	 * @brief Creates a new BMFont with the given spec.
	 *
	 * @param filename The path to the font image.
	 * @param glyphWidth The width of each character.
	 * @param glyphHeight The height of each character.
	 * @param letters The letters presented in the font image.
	 *
	 * @return The created BMFont.
	 */
	Font* newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);

	/**
	 * @brief Set an already-loaded Font as the current font.
	 *
	 * @param The font to set as the active font.
	 */
	void setFont(Font* font);

	void setFont();

	/**
	 * @brief Retrieve th currently active font.
	 */
	Font* getFont();

	/**
	 * @brief Prints the given text to the screen.
	 *
	 * @param text The text to draw.
	 * @param x The position to draw the object (x-axis).
	 * @param y The position to draw the object (y-axis).
	 */
	void print(const std::string& text, int x, int y);

	/**
	 * @brief Sets the active drawing color to the given color.
	 */
	void setColor(int red, int green, int blue, int alpha);

	/**
	 * @brief Sets the active drawing color to the given color.
	 */
	void setColor(int red, int green, int blue);

	/**
	 * @brief Retrieves the active background color.
	 */
	Color getBackgroundColor();

	/**
	 * @brief Sets the background color to the given color.
	 */
	void setBackgroundColor(int red, int green, int blue, int alpha);

	/**
	 * @brief Sets the background color to the given color.
	 */
	void setBackgroundColor(int red, int green, int blue);

	/**
	 * @brief Retrieve the width of the screen.
	 */
	int getWidth();

	/**
	 * @brief Retrieve the height of the screen.
	 */
	int getHeight();

	/**
	 * @brief Draws a circle.
	 */
	void circle(const std::string& drawmode, int x, int y, int radius);

	/**
	 * @brief Draws an ellipse.
	 */
	void ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy);

	/**
	 * @brief Draws an image with the given angle, zoom, and origin.
	 *
	 * @param image The image to draw on the screen.
	 * @param x (0) The position to draw the object (x-axis).
	 * @param y (0) The position to draw the object (y-axis).
	 * @param r (0) Orientation (radians).
	 * @param sx (1) Scale factor (x-axis).
	 * @param sy (sx) Scale factor (y-axis).
	 * @param ox (0) Origin offset (x-axis).
	 * @param oy (0) Origin offset (y-axis).
	 */
	void draw(Image* image, int x, int y, float r, float sx, float sy, float ox, float oy);
	void draw(Image* image, int x, int y, float r, float sx, float sy, float ox);
	void draw(Image* image, int x, int y, float r, float sx, float sy);
	void draw(Image* image, int x, int y, float r, float sx);
	void draw(Image* image, int x, int y, float r);

	/**
	 * @brief Draws an arc.
	 */
	void arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2);

	Uint8 r = 255, g = 255, b = 255, a = 255;
	Uint8 backR = 0, backG = 0, backB = 0, backA = 255;
	SDL_Surface* getScreen();
	Font* activeFont;
	Font defaultFont;
};

}  // namespace Modules

#endif  // SRC_MODULES_GRAPHICS_H_
