#ifndef LIBRETRO_SDL_BRIDGE_CPP_H__
#define LIBRETRO_SDL_BRIDGE_CPP_H__

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb_cpp(unsigned port, unsigned device, unsigned index, unsigned id);

#endif
