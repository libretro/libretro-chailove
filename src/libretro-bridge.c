#include <libretro.h>
#define LIBRETRO_BRIDGE_IMPLEMENTATION
#include "libretro-bridge.h"
#include "stdio.h"


void libretro_audio_cb(int16_t left, int16_t right) {
	// Nothing, since we're using libretro-common.
	// audio_cb(left, right);
}

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	printf("WTF???\n");
	if (input_state_cb == NULL) {
		printf("WTF\n");
		return 0;
	}
	else {
		return input_state_cb(port, device, index, id);
	}
}
