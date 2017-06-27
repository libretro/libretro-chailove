#ifndef _IMAGEDATA_H_INCLUDED_
#define _IMAGEDATA_H_INCLUDED_

#include <SDL.h>
#include <string>

namespace chaigame {
	class ImageData {
	public:
		SDL_Surface* surface;
		ImageData(SDL_RWops* rw);
		ImageData(std::string filename);
		~ImageData();
		bool loaded();
		bool loadFromRW(SDL_RWops* rw);
		bool destroy();

	 /* TODO: Add rwops API
		SDL_RWops* rw;
		if ((rw=PHYSFSRWOPS_openRead(filepath.c_str()) == NULL)
		{
		    return false; //file doesn't exist
		}

		SDL_Surface* surface = IMG_Load_RW(rw, 0);

		SDL_FreeRW(rw);
		*/
		//void newImageData(std::string filename);
	};
}

#endif
