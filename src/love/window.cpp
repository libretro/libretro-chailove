#include "window.h"
#include <string>
#include <iostream>
#include "../ChaiLove.h"
#include "SDL.h"
#include "config.h"

using ::ChaiLove;
using std::string;

namespace love {

bool window::load(const config& conf) {
	ChaiLove* app = ChaiLove::getInstance();

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		const char* errorChar = SDL_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		std::cout << "[game] Unable to initialize SDL " << errString << std::endl;
		return false;
	}

	// Create the Window.
	window = SDL_CreateWindow(conf.window.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, conf.window.width, conf.window.height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		const char* errorChar = SDL_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		std::cout << "[game] Unable to initialize window. " << errString << std::endl;
		return false;
	}

	// Build the Screen.
	/*Uint32 flags;
	if (conf.window.hwsurface) {
		flags = SDL_HWSURFACE;
	} else {
		flags = SDL_SWSURFACE;
	}
	if (conf.window.asyncblit) {
		flags |= SDL_ASYNCBLIT;
	}
	if (conf.window.doublebuffering) {
		flags |= SDL_DOUBLEBUF;
	}*/
	app->screen = SDL_GetWindowSurface(window);

	// Enable video buffering.
	app->videoBuffer = (unsigned int *)app->screen->pixels;

    app->renderer = SDL_CreateSoftwareRenderer(app->screen);
    if (app->renderer == NULL) {
		const char* errorChar = SDL_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		std::cout << "[game] Unable to initialize renderer. " << errString << std::endl;
		return false;
	}

	return true;
}

bool window::unload() {
	SDL_DestroyRenderer(ChaiLove::getInstance()->renderer);
	ChaiLove::getInstance()->renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return true;
}

string window::getTitle() {
	const char* titleChar = SDL_GetWindowTitle(window);
	return std::string(titleChar);
}

window& window::setTitle(string title) {
	SDL_SetWindowTitle(window, title.c_str());
	return *this;
}

}  // namespace love
