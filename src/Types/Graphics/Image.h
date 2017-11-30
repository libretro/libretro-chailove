#ifndef SRC_TYPES_GRAPHICS_IMAGE_H_
#define SRC_TYPES_GRAPHICS_IMAGE_H_

#include <SDL.h>
#include <string>

namespace Types {
namespace Graphics {

/**
 * @brief Drawable image type.
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
	 * @brief Gets the width of the Texture.
	 */
	int getWidth();
	/**
	 * @brief Gets the height of the Texture.
	 */
	int getHeight();
};

}  // namespace Graphics
}  // namespace Types

#endif  // SRC_TYPES_GRAPHICS_IMAGE_H_
