#include "Font.h"
#include "SDL.h"
#include <string>
#include "SDL_ttf.h"
#include <SDL_gfxPrimitives.h>
#include <SDL_fnt.h>
#include "../../Application.h"
#include "SDL_image.h"

namespace chaigame {
	Font::Font() {}

	Font::Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters) {
		SDL_RWops* rwops = Application::getInstance()->filesystem.openRW(filename);
		if (rwops) {
			SDL_Surface* surface = IMG_Load_RW(rwops, 1);
			if (surface == NULL) {
				printf("Font::Font: %s\n", IMG_GetError());
				return;
			}

			TTY_Font* newFont = FNT_Create(surface, glyphWidth, glyphHeight, letters.c_str());
			if (newFont == NULL) {
				printf("Error creating FNT_Create()\n");
				return;
			}

			ttyFont = newFont;
			ttyFontWidth = glyphWidth;
			ttyFontHeight = glyphHeight;
		}
	}

	Font::Font(const std::string& filename, int ptsize) {
		SDL_RWops* rwops = Application::getInstance()->filesystem.openRW(filename);
		if (rwops) {
			TTF_Font* newFont = TTF_OpenFontRW(rwops, 1, ptsize);
			if (!newFont) {
				printf("TTF_OpenFontRW: %s\n", TTF_GetError());
				return;
			}

			ttfFont = newFont;
		}
	}

	Font::~Font() {
		destroy();
	}

	bool Font::loaded() {
		return ttfFont != NULL || ttyFont != NULL;
	}

	bool Font::destroy() {
		if (ttfFont != NULL) {
			TTF_CloseFont(ttfFont);
			ttfFont = NULL;
		}

		if (ttyFont != NULL) {
			FNT_Free(ttyFont);
			ttyFont = NULL;
		}
	}

	int Font::getHeight() {
		if (ttfFont != NULL) {
			return TTF_FontHeight(ttfFont);
		}
		if (ttyFont != NULL) {
			return ttyFontHeight;
		}

		return 12;
	}

	int Font::getWidth(const std::string& text) {
		if (ttfFont != NULL) {
			int w;
			if (TTF_SizeText(ttfFont, text.c_str(), &w, NULL) == 0) {
				return w;
			}
		}

		if (ttyFont != NULL) {
			return ttyFontWidth * text.length();
		}

		return 0;
	}

	void Font::print(const std::string& text, int x, int y, int r, int g, int b, int a) {
		SDL_Surface* screen = Application::getInstance()->screen;

		// Attempt to render the TTF Font.
		if (ttfFont != NULL) {
			SDL_Color color = {(Uint8)r, (Uint8)g, (Uint8)b};
			SDL_Surface* surface = TTF_RenderText_Blended(ttfFont, text.c_str(), color);
			if (!surface) {
				printf("Font::print - %s\n", TTF_GetError());
				return;
			}

			SDL_Rect* dstrect = new SDL_Rect();
			dstrect->x = x;
			dstrect->y = y;
			SDL_BlitSurface(surface, NULL, screen, dstrect);

			// TODO: Allow re-use of text renderings.
			SDL_FreeSurface(surface);
			return;
		}

		// Use TTY to print the bitmap font?
		if (ttyFont != NULL) {
			FNT_Print(ttyFont, screen, x, y, FNT_ALIGN_LEFT, text.c_str());
			return;
		}

		// Fall back to SDL_gfx primitives.
		stringRGBA(screen, x, y, text.c_str(), r, g, b, a);
	}
}
