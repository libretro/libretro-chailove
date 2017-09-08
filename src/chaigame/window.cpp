#include "window.h"
#include <string>
#include "../Game.h"
#include "SDL.h"
#include "SDL_gpu.h"
#include "log.h"
#include "system/Config.h"

namespace chaigame {
/*
	int GPU_LogCallback(GPU_LogLevelEnum log_level, const char* format, va_list args) {
		printf("Custom GPU Log callback\n");
		printf(format, args);
		switch (log_level) {
			case GPU_LOG_INFO:
				log()->info(format, args);
				break;
    		case GPU_LOG_WARNING:
				log()->warn(format, args);
				break;
    		case GPU_LOG_ERROR:
				log()->error(format, args);
    			break;
    	}
	}*/

	bool window::load(Config& config) {
		Game* app = Game::getInstance();

    	GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

		// Initialize SDL_gpu.
		GPU_WindowFlagEnum initFlags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
    	app->screen = GPU_Init(config.window.height, config.window.bbp, initFlags);
    	if (app->screen == NULL) {
    		GPU_ErrorObject err = GPU_PopErrorCode();
    		log()->critical("Unable to initialize SDL_gpu: {}", GPU_GetErrorString(err.error));
    		return false;
    	}

		// Set the title.
		setTitle(config.window.title);

		return true;
	}

	bool window::unload() {
		GPU_Quit();
		return true;
	}

	std::string window::getTitle() {
		char* titleChar;
		SDL_WM_GetCaption(&titleChar, NULL);
		return std::string(titleChar);
	}

	void window::setTitle(std::string title) {
		SDL_WM_SetCaption(title.c_str(), 0);
	}
}
