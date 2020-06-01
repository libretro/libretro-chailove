#include "ChaiLove.h"
#include "libretro.h"
#include "libretro-sdl-bridge-cpp.h"

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb_cpp(unsigned port, unsigned device, unsigned index, unsigned id) {
	return ChaiLove::input_state_cb(port, device, index, id);
}
