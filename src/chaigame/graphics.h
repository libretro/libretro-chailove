#ifndef CHAIGAME_GRAPHICS_H
#define CHAIGAME_GRAPHICS_H

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "graphics/ImageData.h"
#include "graphics/Image.h"
#include "graphics/Quad.h"
#include "graphics/Font.h"
#include "graphics/Color.h"

namespace chaigame {
	class graphics {
	public:

		graphics();
		bool load();

		void rectangle(const std::string& drawmode, float x, float y, float width, float height);
		void clear();
		void clear(int r, int g, int b, int a);
		void clear(int r, int g, int b);
		void point(float x, float y);
		void line(float x1, float y1, float x2, float y2);

		void draw(ImageData* image, float x, float y);
		void draw(ImageData* image, Quad quad, float x, float y);

		Quad newQuad(int x, int y, int width, int height, int sw, int sh);

		ImageData* newImage(const std::string& filename);
		Font* newFont();
		Font* newFont(const std::string& filename);
		Font* newFont(const std::string& filename, int size);
		Font* newFont(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
		void setFont(Font* font);
		void setFont();
		Font* getFont();

		void print(const std::string& text, float x, float y);
		void setColor(int red, int green, int blue, int alpha);
		void setColor(int red, int green, int blue);
		void setBackgroundColor(int red, int green, int blue, int alpha);
		void setBackgroundColor(int red, int green, int blue);

		Color color;
		Color backColor;
		GPU_Target* getScreen();

		int getWidth();
		int getHeight();

		void circle(const std::string& drawmode, float x, float y, float radius);
		void ellipse(const std::string& drawmode, float x, float y, float radiusx, float radiusy, float degrees);
		void arc(const std::string& drawmode, float x, float y, float radius, float angle1, float angle2);

		Font* activeFont;
	};
}

#endif
