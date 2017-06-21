#include <stdint.h>
#include <string>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "chaigame.h"

ChaiGame* ChaiGame::m_instance = NULL;


bool ChaiGame::isRunning() {
	return m_instance != NULL;
}
void ChaiGame::destroy() {
	m_instance = NULL;
}

ChaiGame* ChaiGame::getInstance() {
	if (!m_instance) {
		m_instance = new ChaiGame;
	}
	return m_instance;
}

void ChaiGame::quit_app(void) {
	SDL_Quit();
}

bool ChaiGame::init_app() {
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

	// ChaiScript.
	#ifndef __DISABLE_CHAISCRIPT__
	chai.eval_file("main.chai");
	#endif

	return true;
}

bool ChaiGame::checkInput() {
	bool quit = false;

	/* Check for events */
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
				y+=1;
			default:
				break;
		}
	}

	return quit;
}

void ChaiGame::exec_app(){

	// Clear the screen
	Uint32 color = SDL_MapRGBA(screen->format, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, color);

	// Draw Background.
	rectangleRGBA(screen,
		x, y,
		x + 100, y + 100,
		0, 0, 255, 255);

	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);
}
