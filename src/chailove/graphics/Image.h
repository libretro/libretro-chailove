#ifndef CHAILOVE_UTILITY_IMAGE_H
#define CHAILOVE_UTILITY_IMAGE_H

#include <SDL.h>
#include <string>

namespace chailove {
	class Image {
	public:
		SDL_Surface* surface;
		Image(SDL_RWops* rw);
		Image(const std::string& filename);
		~Image();
		bool loaded();
		bool loadFromRW(SDL_RWops* rw);
		bool destroy();

		int getWidth();
		int getHeight();
	};
}

#endif
