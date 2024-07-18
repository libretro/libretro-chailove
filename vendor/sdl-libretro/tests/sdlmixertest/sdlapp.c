#include <stdint.h>

/********************************************************************************/
/*                   SDL PART	:BEGIN						*/
/********************************************************************************/
#include "SDL.h"
#include "SDL_mixer.h"

SDL_Surface* screen;
SDL_Event event;

Mix_Chunk *med = NULL;
Mix_Music *music = NULL;

extern uint32_t *videoBuffer;

#include "TestGfxPrimitives.c"


void quit_app(void)
{
    Mix_FreeChunk( med );
    Mix_FreeMusic( music );
    //Quit SDL_mixer
    Mix_CloseAudio();
	SDL_Quit();
}

void init_sdlmixer(){

    int numtimesopened, frequency, channels;
    Uint16 format;

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
    {
        return ;
    }

    numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
    if(!numtimesopened) {
    	printf("Mix_QuerySpec: %s\n",Mix_GetError());
    }
    else {
    	char *format_str="Unknown";
    	switch(format) {
    	    case AUDIO_U8: format_str="U8"; break;
    	    case AUDIO_S8: format_str="S8"; break;
    	    case AUDIO_U16LSB: format_str="U16LSB"; break;
    	    case AUDIO_S16LSB: format_str="S16LSB"; break;
    	    case AUDIO_U16MSB: format_str="U16MSB"; break;
    	    case AUDIO_S16MSB: format_str="S16MSB"; break;
    	}
    	printf("opened=%d times  frequency=%dHz  format=%s  channels=%d\n",
            numtimesopened, frequency, format_str, channels);
    }

    music = Mix_LoadMUS( "beat.wav" );
    med = Mix_LoadWAV( "medium.wav" );

    printf("load medium.wav\n");
}

int init_app(){

	/* Generate title string */
	sprintf (title,"TestGfxPrimitives - v%i.%i.%i",SDL_GFXPRIMITIVES_MAJOR, SDL_GFXPRIMITIVES_MINOR, SDL_GFXPRIMITIVES_MICRO);

	 //Initialize all SDL subsystems 
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { return 1; }
	//SDL_Init(SDL_INIT_VIDEO);
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

					//Play the medium hit effect
                    			if( Mix_PlayChannel( -1, med, 0 ) == -1 )
                    			{
                        			return 1;
                    			}

					if ( event.button.button == SDL_BUTTON_LEFT ) {
						/* Switch to next graphics */
						curprim++;
					} else if ( event.button.button == SDL_BUTTON_RIGHT ) {
						/* Switch to prev graphics */
						curprim--;
					}
					break;
				case SDL_KEYDOWN:
	
					//If SPACE was pressed
					if( event.key.keysym.sym == SDLK_SPACE )
			                {
			                    //If there is no music playing
			                    if( Mix_PlayingMusic() == 0 )
			                    {
			                        //Play the music
			                        if( Mix_PlayMusic( music, -1 ) == -1 )
			                        {
			                            return 1;
			                        }
			                    }
			                    //If music is being played
			                    else
			                    {
			                        //If the music is paused
			                        if( Mix_PausedMusic() == 1 )
			                        {
			                            //Resume the music
			                            Mix_ResumeMusic();
			                        }
			                        //If the music is playing
			                        else
			                        {
			                            //Pause the music
			                            Mix_PauseMusic();
			                        }
			                    }
			                }
			                //If m was pressed
                			else if( event.key.keysym.sym == SDLK_m )
                			{
                			    //Stop the music
                			    Mix_HaltMusic();
                			}

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


