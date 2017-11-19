#ifndef CHAILOVE_GRAPHICS_H
#define CHAILOVE_GRAPHICS_H

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "graphics/Image.h"
#include "graphics/Quad.h"
#include "graphics/Font.h"

namespace chailove {

	/**
	 * \brief The primary purpose of the graphics module is to draw to the screen.
	 */
	class graphics {
	public:

		graphics();
		bool load();

		/**
		 * Draws a rectangle.
		 *
		 * @param drawmode How to draw the rectangle. Can be "fill" or "line".
		 * @param x The position of top-left corner along the x-axis.
		 * @param y The position of top-left corner along the y-axis.
		 * @param width Width of the rectangle.
		 * @param height Height of the rectangle.
		 *
		 * @code
		 * graphics.rectangle("fill", 100, 100, 50, 50)
		 * @endcode
		 */
		void rectangle(const std::string& drawmode, int x, int y, int width, int height);
		void clear();
		void clear(int r, int g, int b, int a);
		void clear(int r, int g, int b);
		void point(int x, int y);
		void line(int x1, int y1, int x2, int y2);

		void draw(Image* image, int x, int y);
		void draw(Image* image, Quad quad, int x, int y);

		Quad newQuad(int x, int y, int width, int height, int sw, int sh);

		Image* newImage(const std::string& filename);
		Font* newFont();
		Font* newFont(const std::string& filename);
		Font* newFont(const std::string& filename, int size);
		Font* newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
		void setFont(Font* font);
		void setFont();
		Font* getFont();

		/**
		 * Prints the given text to the screen.
		 */
		void print(const std::string& text, int x, int y);

		/**
		 * Sets the active drawing color to the given color.
		 */
		void setColor(int red, int green, int blue, int alpha);
		/**
		 * Sets the active drawing color to the given color.
		 */
		void setColor(int red, int green, int blue);
		/**
		 * Sets the background color to the given color.
		 */
		void setBackgroundColor(int red, int green, int blue, int alpha);
		/**
		 * Sets the background color to the given color.
		 */
		void setBackgroundColor(int red, int green, int blue);

		Uint8 r = 255, g = 255, b = 255, a = 255;
		Uint8 backR = 0, backG = 0, backB = 0, backA = 255;
		SDL_Surface* getScreen();

		/**
		 * Retrieve the width of the screen.
		 */
		int getWidth();
		/**
		 * Retrieve the height of the screen.
		 */
		int getHeight();

		void circle(const std::string& drawmode, int x, int y, int radius);
		void ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy);
		void arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2);

		Font* activeFont;
		Font defaultFont;
	};
}

#endif
