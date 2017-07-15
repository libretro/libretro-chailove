#include "window.h"
#include "../Application.h"
#include "SDL.h"
#include <string>
#include "chaigame.h"

#include <iostream>

namespace chaigame {

	bool window::load(Config& config) {
		Application* app = Application::getInstance();

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			printf("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// Build the Screen.
		Uint32 flags = SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
		app->screen = SDL_SetVideoMode(config.window.width, config.window.height, config.window.bbp, flags);
		if (app->screen == NULL) {
			printf("Unable to create screen: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}

		// Enable video buffering.
		app->videoBuffer = (unsigned int *)app->screen->pixels;

		// Set the title.
		setTitle(config.window.title);
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
