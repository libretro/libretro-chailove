#include <stdint.h>

/********************************************************************************/
/*                   SDL PART	:BEGIN						*/
/********************************************************************************/
#include "SDL.h"

SDL_Surface* screen;
SDL_Event event;

extern uint32_t *videoBuffer;

#include "TestGfxPrimitives.c"


void quit_app(void)
{

	SDL_Quit();
}

void init_app(){

	/* Generate title string */
	sprintf (title,"TestGfxPrimitives - v%i.%i.%i",SDL_GFXPRIMITIVES_MAJOR, SDL_GFXPRIMITIVES_MINOR, SDL_GFXPRIMITIVES_MICRO);

	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE);

        videoBuffer=(unsigned int *)screen->pixels;

	/* Use alpha blending */
	SDL_SetAlpha(screen, SDL_SRCALPHA, 0);

	done = 0;
	oldprim = 0;
	curprim = 1;

}

void checkInput()
{
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_MOUSEBUTTONDOWN:
					if ( event.button.button == SDL_BUTTON_LEFT ) {
						/* Switch to next graphics */
						curprim++;
					} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
						/* Switch to prev graphics */
						curprim--;
					}
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}

}


void exec_app(){

	tmain();
	checkInput();
}

/********************************************************************************/
/*                   SDL PART	:END						*/
/********************************************************************************/


