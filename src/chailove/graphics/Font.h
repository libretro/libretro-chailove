#ifndef CHAILOVE_UTILITY_FONT_H
#define CHAILOVE_UTILITY_FONT_H

#include "SDL.h"
//#include "SDL_ttf.h"
#include <string>
#include <SDL_fnt.h>
#include "Image.h"

namespace chailove {
	class Font {
	public:
		Font();
		Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
		Font(const std::string& filename, int ptsize);
		~Font();
		bool loaded();
		bool destroy();
		void print(const std::string& text, int x, int y, int r, int g, int b, int a);
		//TTF_Font* ttfFont = NULL;
		TTY_Font* ttyFont = NULL;
		int ttyFontWidth, ttyFontHeight;
		int getHeight(const std::string& text);
		int getHeight();
		int getWidth(const std::string& text);

		Image* m_image;
	};
}

#endif
