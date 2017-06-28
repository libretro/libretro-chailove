#include <SDL.h>
//#include <SDL_mixer.h>

#include "sound.h"

namespace chaigame {
	bool sound::load() {
		/*int flags = MIX_INIT_OGG;// | MIX_INIT_MOD;
		int initted = Mix_Init(flags);
		if (initted&flags != flags) {
		    printf("Mix_Init: Failed to init required ogg and mod support!\n");
		    printf("Mix_Init: %s\n", Mix_GetError());
		    return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			printf("Mix_OpenAudio: %s\n", Mix_GetError());
			return false;
		}*/

		return true;
	}
	bool sound::unload() {
		//Mix_Quit();
	}
}
