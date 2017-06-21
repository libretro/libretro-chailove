#include <stdint.h>
#include <string>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "chaigame.hpp"

extern uint32_t *videoBuffer;

ChaiGame* ChaiGame::m_instance = NULL;

int multiply(int i, int j)
{
	return i * j;
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

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);

	if (screen == NULL) {
		return false;
	}

	SDL_WM_SetCaption("Hello!", NULL);

	videoBuffer = (unsigned int *)screen->pixels;
	SDL_SetAlpha(screen, SDL_SRCALPHA, 0);

	SDL_ShowCursor(SDL_DISABLE);


	#ifndef __DISABLE_CHAISCRIPT__
	chai.add(chaiscript::fun(&multiply), "multiply");
	chai.eval_file("main.chai");
	#endif

	return true;
}

void ChaiGame::checkInput() {
	/* Check for events */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_LEFT ) {
				} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
					/* Switch to prev graphics */
					//curprim--;
				}
				break;
			case SDL_KEYDOWN:

				#ifndef __DISABLE_CHAISCRIPT__
				x += chai.eval<int>("multiply(5, 20);");
				//x += 100;
				#endif
				y+=1;
			default:
				break;
		}
	}

}


void ChaiGame::exec_app(){

	// Clear the screen
	Uint32 color = SDL_MapRGBA(screen->format, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, color);

	// Draw Background.
	rectangleRGBA(screen,
		x, y,
		x+100, y+100,
		0, 0, 255, 255);

	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);

	checkInput();
}
