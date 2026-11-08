#ifndef SRC_LOVE_FONT_H_
#define SRC_LOVE_FONT_H_

#include "Types/Graphics/Font.h"
#include <list>

using love::Types::Graphics::Font;

namespace love {
/**
 * Allows you to work with fonts.
 *
 * @see love.graphics.newFont
 */
class font {
	public:
	~font();
	bool load();

	/**
	 * Retrieves whether or not all sub-systems have been loaded.
	 *
	 * @return True if the Font sub-system has been loaded.
	 *
	 * @see love.graphics.newFont
	 */
	bool isOpen();

	bool unload();

	/**
	 * Takes ownership of the given Font, freeing it on unload.
	 *
	 * @return The Font, or NULL if it failed to load.
	 */
	Font* add(Font* newFont);

	private:
	std::list<Font*> m_fonts;
};

}  // namespace love

#endif  // SRC_LOVE_FONT_H_
