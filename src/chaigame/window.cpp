#include "window.h"
#include <string>
#include "../ChaiGame.h"
#include "SDL.h"
#include "log.h"
#include "system/Config.h"

namespace chaigame {

	bool window::load(Config& config) {
		ChaiGame* app = ChaiGame::getInstance();

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			const char* errorChar = SDL_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->critical("Unable to initialize SDL: {}", errString);
			return false;
		}

		// Build the Screen.
		Uint32 flags;
		if (config.window.hwsurface) {
			flags = SDL_HWSURFACE;
		}
		else {
			flags = SDL_SWSURFACE;
		}
		if (config.window.asyncblit) {
			flags |= SDL_ASYNCBLIT;
		}
		if (config.window.doublebuffering) {
			flags |= SDL_DOUBLEBUF;
		}
		app->screen = SDL_SetVideoMode(config.window.width, config.window.height, config.window.bbp, flags);
		if (app->screen == NULL) {
			const char* errorChar = SDL_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->critical("Unable to create screen: {}", errString);
			SDL_Quit();
			return false;
		}

		// Enable video buffering.
		app->videoBuffer = (unsigned int *)app->screen->pixels;

		// Set the title.
		setTitle(config.window.title);

		return true;
	}

	bool window::unload() {
		SDL_Quit();
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
