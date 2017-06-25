#include <stdint.h>
#include <string>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "Application.h"

#include "chaigame/chaigame.h"


Application* Application::m_instance = NULL;


bool Application::isRunning() {
	return m_instance != NULL;
}
void Application::destroy() {
	m_instance = NULL;
}

Application* Application::getInstance() {
	if (!m_instance) {
		m_instance = new Application;
	}
	return m_instance;
}

void Application::quit(void) {
	// Tell SDL to quit.
	SDL_Quit();
}

bool Application::load() {
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	// Build the Screen.
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);
	if (screen == NULL) {
		SDL_Quit();
		return false;
	}

	// Enable video buffering.
	videoBuffer = (unsigned int *)screen->pixels;

	// Fix alpha blending.
	if (SDL_SetAlpha(screen, SDL_SRCALPHA, 0) == -1) {
		// Error: Do nothing.
	}

	// Disable the mouse cursor from showing up.
	SDL_ShowCursor(SDL_DISABLE);

	// Set up the game timer.
	tick = SDL_GetTicks();

	// ChaiScript.
	#ifndef __DISABLE_CHAISCRIPT__
	// Load main.chai.
	chai.eval_file("main.chai");

	// Find the game functions.
	chaiload = chai.eval<std::function<void ()> >("load");
	chaiupdate = chai.eval<std::function<void (Uint32)> >("update");
	chaidraw = chai.eval<std::function<void ()> >("draw");

	// Add all the modules.
	chai.add(chaiscript::fun(chaigame::graphics::rectangle), "rectangle");

	// Initialize the game.
	chaiload();
	#endif

	return true;
}

bool Application::update() {
	bool quit = false;

	// Update all the input.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				quit = true;
				if ( event.button.button == SDL_BUTTON_LEFT ) {
				} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
					/* Switch to prev graphics */
					//curprim--;
				}
				break;
			case SDL_KEYDOWN:

				#ifndef __DISABLE_CHAISCRIPT__
				//x += chai.eval<int>("multiply(5, 20);");
				//x += 100;
				#endif
			default:
				break;
		}
	}

	// Retrieve the new game time.
	Uint32 current = SDL_GetTicks();

	// Update the game.
	#ifndef __DISABLE_CHAISCRIPT__
	chaiupdate(current - tick);
	#endif

	// Update the timer.
	tick = current;

	return quit;
}

/**
 * Render the application.
 */
void Application::draw(){
	// Clear the screen
	Uint32 color = SDL_MapRGBA(screen->format, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, color);

	// Test drawing a rectangle.
	chaigame::graphics::rectangle(10, 10, 100, 100, 0, 255, 255, 255);

	#ifndef __DISABLE_CHAISCRIPT__
	chaidraw();
	#endif

	SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);
}
