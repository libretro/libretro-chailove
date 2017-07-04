#include "window.h"
#include "../Application.h"
#include <SDL.h>
#include <string>

namespace chaigame {

	bool window::load() {
		Application* app = Application::getInstance();

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			printf("Unable to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// Build the Screen.
		app->screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);
		if (app->screen == NULL) {
			printf("Unable to create screen: %s", SDL_GetError());
			SDL_Quit();
			return false;
		}

		// Enable video buffering.
		app->videoBuffer = (unsigned int *)app->screen->pixels;

		// Set the title.
		setTitle("ChaiGame");
	}

	bool window::unload() {
		SDL_Quit();
		return true;
	}

	std::string window::getTitle() {
		// TODO: Implement SDL_WM_GetCaption().
		return "ChaiGame";
	}

	void window::setTitle(std::string title) {
		SDL_WM_SetCaption(title.c_str(), 0);
	}
}
