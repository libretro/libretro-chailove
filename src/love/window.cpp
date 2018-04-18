#include "window.h"
#include <string>
#include <iostream>
#include "../ChaiLove.h"
#include "SDL.h"
#include "config.h"
#include "libretro.h"
#include "Types/Graphics/Point.h"

using ::ChaiLove;
using love::Types::Graphics::Point;
using std::string;

namespace love {

bool window::load(const config& conf) {
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
	}
	app->screen = SDL_SetVideoMode(conf.window.width, conf.window.height, conf.window.bbp, flags);
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
	setTitle(conf.window.title);
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

window& window::setTitle(string title) {
	SDL_WM_SetCaption(title.c_str(), 0);
	return *this;
}

void window::showMessageBox(const std::string& msg, int frames) {
	retro_message retroMessage;
	retroMessage.msg = msg.c_str();
	retroMessage.frames = frames;
	ChaiLove::environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &retroMessage);
}

void window::showMessageBox(const std::string& msg) {
	showMessageBox(msg, 2800);
}

}  // namespace love
