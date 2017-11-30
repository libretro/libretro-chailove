#ifndef SRC_TYPES_GRAPHICS_FONT_H_
#define SRC_TYPES_GRAPHICS_FONT_H_

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <SDL_fnt.h>
#include "Image.h"

namespace Types {
namespace Graphics {

/**
 * @brief Defines the shape of characters that can be drawn onto the screen.
 */
class Font {
	public:
	Font();
	Font(const std::string& filename, int glyphWidth, int glyphHeight, const std::string& letters);
	Font(const std::string& filename, int ptsize);
	~Font();

	/**
	 * @brief Retrieves whether or not the font is loaded.
	 */
	bool loaded();
	bool destroy();
	void print(const std::string& text, int x, int y, int r, int g, int b, int a);
	TTF_Font* ttfFont = NULL;
	TTY_Font* ttyFont = NULL;
	int ttyFontWidth, ttyFontHeight;
	/**
	 * @brief Determines the vertical size the given text needs.
	 */
	int getHeight(const std::string& text);
	/**
	 * @brief Determines the vertical size a line of text needs.
	 */
	int getHeight();
	/**
	 * @brief Determines the horizontal size a line of text needs.
	 */
	int getWidth(const std::string& text);

	Image* m_image;
};

}  // namespace Graphics
}  // namespace Types

#endif  // SRC_TYPES_GRAPHICS_FONT_H_
