#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "font.h"
#include "src/Font.h"
#include "../Application.h"

namespace chaigame {
	bool font::load() {
		int result = TTF_Init();
		if(result == -1) {
			Application::getInstance()->log->error("TTF_Init failed to initialize font system: {}", TTF_GetError());
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
