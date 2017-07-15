#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "font.h"
#include "src/Font.h"
#include "log.h"

namespace chaigame {
	bool font::load() {
		int result = TTF_Init();
		if(result == -1) {
			const char* errorChar = TTF_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->error("TTF_Init failed to initialize font system: {}", errString());
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
