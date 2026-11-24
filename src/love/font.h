#ifndef SRC_LOVE_FONT_H_
#define SRC_LOVE_FONT_H_

#include "Types/Graphics/Font.h"
#include <functional>
#include <map>
#include <string>

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
	 * Retrieves the Font loaded with the given key, or creates it, freeing it on unload.
	 *
	 * Fonts can't be changed, so the same one is shared rather than loaded again.
	 *
	 * @return The Font, or NULL if it failed to load.
	 */
	Font* get(const std::string& key, const std::function<Font*()>& create);

	private:
	std::map<std::string, Font*> m_fonts;
};

}  // namespace love

#endif  // SRC_LOVE_FONT_H_
