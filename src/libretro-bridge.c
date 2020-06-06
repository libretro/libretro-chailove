#include <libretro.h>

static retro_input_state_t input_state_cb = NULL;

static retro_video_refresh_t video_cb = NULL;
// This is needed to allow SDL-libretro to compile.
// @see SDL_LIBRETROaudio.c:37
retro_audio_sample_t audio_cb;

void libretro_audio_cb(int16_t left, int16_t right) {
	// Nothing, since we're using libretro-common.
	// audio_cb(left, right);
}

/**
 * libretro-sdl callback; Send through the input state.
 */
short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id) {
	return input_state_cb(port, device, index, id);
}
