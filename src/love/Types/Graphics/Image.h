#ifndef SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_
#define SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_

#include <SDL.h>
#include <string>

namespace love {
namespace Types {
namespace Graphics {

/**
 * Drawable image type.
 */
class Image {
	public:
	SDL_Surface* surface;
	Image(SDL_RWops* rw);
	Image(const std::string& filename);
	~Image();
	bool loaded();
	bool loadFromRW(SDL_RWops* rw);
	bool destroy();

	/**
	 * Gets the width of the Texture.
	 */
	int getWidth();

	/**
	 * Gets the height of the Texture.
	 */
	int getHeight();

	std::string getSource();

	std::string source;
};

}  // namespace Graphics
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_GRAPHICS_IMAGE_H_
