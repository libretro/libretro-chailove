#ifndef _SRCFONT_H_INCLUDED_
#define _SRCFONT_H_INCLUDED_

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace chaigame {
	class Font {
	public:
		Font();
		Font(const std::string& filename, int ptsize);
		~Font();
		bool loaded();
		bool destroy();
		void print(const std::string& text, int x, int y, int r, int g, int b, int a);
		TTF_Font *font = NULL;
		int getHeight();
	};
}

#endif
