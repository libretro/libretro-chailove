#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "font.h"
#include "src/Font.h"

namespace chaigame {
	bool font::load() {
		int result = TTF_Init();
		if(result == -1) {
		    printf("TTF_Init: Failed to init font system:\n");
		    printf("TTF_Init: %s\n", TTF_GetError());
		    return false;
		}
		return true;
	}

	bool font::unload() {
		if (isOpen()) {
			TTF_Quit();
		}
		return true;
	}

	bool font::isOpen() {
		return TTF_WasInit();
	}
}
