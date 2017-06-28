#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "src/ImageData.h"
#include "src/Image.h"

namespace chaigame {
	class graphics {
	public:
		bool load();

		void rectangle(Sint16 x, Sint16 y, Sint16 width, Sint16 height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void draw(ImageData* data, int x, int y);
		void draw(Image* data, int x, int y);

		Image* newImage(std::string filename);

		void print(const std::string& text, int x, int y);
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

		Uint8 r, g, b, a;
	};
}

#endif
