#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "src/ImageData.h"
#include "src/Image.h"
#include "src/Quad.h"

namespace chaigame {
	class graphics {
	public:
		bool load(SDL_Surface* screen);

		void rectangle(const std::string& mode, Sint16 x, Sint16 y, Sint16 width, Sint16 height);
		void clear();
		void clear(int r, int g, int b, int a);
		void clear(int r, int g, int b);
		void point(int x, int y);
		void line(int x1, int y1, int x2, int y2);

		void draw(ImageData* data, int x, int y);
		void draw(Image* data, int x, int y);
		void draw(Image* image, Quad quad, int x, int y);

		Quad newQuad(int x, int y, int width, int height, int sw, int sh);

		Image* newImage(const std::string& filename);

		void print(const std::string& text, int x, int y);
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
		void setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
		void setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue);

		Uint8 r = 255, g = 0, b = 0, a = 255;
		Uint8 backR = 0, backG = 0, backB = 0, backA = 255;
		SDL_Surface* screen;
	};
}

#endif
