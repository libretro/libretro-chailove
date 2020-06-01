#ifndef LIBRETROSSDL_BRIDGE_H__
#define LIBRETROSSDL_BRIDGE_H__

#include "libretro.h"

void libretro_audio_cb(int16_t left, int16_t right);

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id);

#endif
