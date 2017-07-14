#include "Font.h"
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_gfxPrimitives.h>
#include "../../Application.h"

namespace chaigame {
	Font::Font() {
	}

	Font::Font(const std::string& filename, int ptsize) {
		SDL_RWops* rwops = Application::getInstance()->filesystem.openRW(filename);
		if (rwops) {
			font = TTF_OpenFontRW(rwops, 1, ptsize);
			if(!font) {
				printf("TTF_OpenFontRW: %s\n", TTF_GetError());
			}
		}
	}

	Font::~Font() {
		destroy();
	}

	bool Font::loaded() {
		return font != NULL;
	}

	bool Font::destroy() {
		if (loaded()) {
			TTF_CloseFont(font);
			font = NULL;
		}
	}

	int Font::getHeight() {
		if (loaded()) {
			return TTF_FontHeight(font);
		}
		return 12;
	}

	void Font::print(const std::string& text, int x, int y, int r, int g, int b, int a) {
		if (loaded()) {
			SDL_Color color = {(Uint8)r, (Uint8)g, (Uint8)b};
			SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
			if (!surface) {
				printf("Font::print - %s\n", TTF_GetError());
				return;
			}

			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(surface, NULL, Application::getInstance()->screen, dstrect);

		    // TODO: Allow re-use of text renderings.
		    SDL_FreeSurface(surface);
		}
		else {
			stringRGBA(Application::getInstance()->screen, x, y, text.c_str(), r, g, b, a);
		}
	}
}
