#include "libretro-sdl-bridge.h"
#include "libretro-sdl-bridge-cpp.h"

void libretro_audio_cb(int16_t left, int16_t right) {
	// Nothing, since we're using libretro-common.
	// audio_cb(left, right);
}

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	libretro_input_state_cb_cpp(port,device,index,id);
}
