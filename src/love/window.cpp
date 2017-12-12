#include "window.h"
#include <string>
#include "../ChaiLove.h"
#include "SDL.h"
#include "../Types/System/Config.h"

using ::ChaiLove;
using Types::System::Config;
using std::string;

namespace love {

bool window::load(const Config& config) {
	ChaiLove* app = ChaiLove::getInstance();

	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		const char* errorChar = SDL_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		std::cout << "[game] Unable to initialize SDL " << errString << std::endl;
		return false;
	}

	// Build the Screen.
	Uint32 flags;
	if (config.window.hwsurface) {
		flags = SDL_HWSURFACE;
	} else {
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
		std::cout << "[game] Unable to initialize SDL" << errString << std::endl;
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

string window::getTitle() {
	char* titleChar;
	SDL_WM_GetCaption(&titleChar, NULL);
	return std::string(titleChar);
}

void window::setTitle(string title) {
	SDL_WM_SetCaption(title.c_str(), 0);
}

}  // namespace love
