#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "src/ImageData.h"
#include "src/Image.h"
#include "src/Quad.h"
#include "src/Font.h"

namespace chaigame {
	class graphics {
	public:

		graphics();
		bool load();

		void rectangle(const std::string& drawmode, int x, int y, int width, int height);
		void clear();
		void clear(int r, int g, int b, int a);
		void clear(int r, int g, int b);
		void point(int x, int y);
		void line(int x1, int y1, int x2, int y2);

		void draw(ImageData* image, int x, int y);
		void draw(ImageData* image, Quad quad, int x, int y);

		Quad newQuad(int x, int y, int width, int height, int sw, int sh);

		ImageData* newImage(const std::string& filename);
		Font* newFont();
		Font* newFont(const std::string& filename);
		Font* newFont(const std::string& filename, int size);
		Font* newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
		void setFont(Font* font);
		void setFont();
		Font* getFont();

		void print(const std::string& text, int x, int y);
		void setColor(int red, int green, int blue, int alpha);
		void setColor(int red, int green, int blue);
		void setBackgroundColor(int red, int green, int blue, int alpha);
		void setBackgroundColor(int red, int green, int blue);

		Uint8 r = 255, g = 0, b = 0, a = 255;
		Uint8 backR = 0, backG = 0, backB = 0, backA = 255;
		SDL_Surface* getScreen();

		int getWidth();
		int getHeight();

		void circle(const std::string& drawmode, int x, int y, int radius);
		void ellipse(const std::string& drawmode, int x, int y, int radiusx, int radiusy);
		void arc(const std::string& drawmode, int x, int y, int radius, int angle1, int angle2);

		Font* activeFont;
	};
}

#endif
