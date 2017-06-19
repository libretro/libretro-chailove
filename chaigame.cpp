#include <stdint.h>

/********************************************************************************/
/*                   SDL PART	:BEGIN						*/
/********************************************************************************/
#include "SDL.h"

SDL_Surface* screen;
SDL_Event event;

extern uint32_t *videoBuffer;
#include "SDL_gfxPrimitives.h"
//#include "TestGfxPrimitives.c"

int done = 0;
int x = 0;


void quit_app(void)
{

	SDL_Quit();
}

bool init_app(){

	/* Generate title string */
	//sprintf (title,"TestGfxPrimitives - v%i.%i.%i",SDL_GFXPRIMITIVES_MAJOR, SDL_GFXPRIMITIVES_MINOR, SDL_GFXPRIMITIVES_MICRO);

	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);

	videoBuffer=(unsigned int *)screen->pixels;

	/* Use alpha blending */
	SDL_SetAlpha(screen, SDL_SRCALPHA, 0);

	done = 0;
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

void checkInput()
{
	/* Check for events */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_LEFT ) {
					/* Switch to next graphics */
					//curprim++;
					x+=1;
				} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
					/* Switch to prev graphics */
					//curprim--;
				}
				break;
			case SDL_KEYDOWN:
				/* Any keypress quits the app... */
			x+=1;
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
		}
	}

}


void exec_app(){

	// Clear the screen
	Uint32 color = SDL_MapRGBA(screen->format, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, color);

	// Draw Background.
	rectangleRGBA(screen,
		x, 100,
		200, 200,
		0, 0, 255, 255);

	//SDL_UpdateRect(screen, 0, 0, 0, 0);
	SDL_Flip(screen);

	checkInput();
}

/********************************************************************************/
/*                   SDL PART	:END						*/
/********************************************************************************/

