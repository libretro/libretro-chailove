#include "window.h"
#include "../Game.h"
#include "SDL.h"
#include <string>
#include "log.h"
#include "src/Config.h"

namespace chaigame {

	bool window::load(Config& config) {
		Game* app = Game::getInstance();

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			const char* errorChar = SDL_GetError();
			std::string errString("");
			if (errorChar != NULL) {
				errString = errorChar;
			}
			log()->critical("Unable to initialize SDL: {}", errString);
			return false;
		}

		// Build the Screen.
		Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
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
