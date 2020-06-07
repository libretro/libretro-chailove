#ifndef LIBRETRO_BRIDGE_H__
#define LIBRETRO_BRIDGE_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "libretro.h"

static retro_input_state_t input_state_cb;
static retro_video_refresh_t video_cb;
//retro_audio_sample_t audio_cb;

// This is needed to allow SDL-libretro to compile.
// @see SDL_LIBRETROaudio.c:37
// retro_audio_sample_t audio_cb;

void libretro_audio_cb(int16_t left, int16_t right);

short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id);


void libretro_set_input(retro_input_state_t cb);


#ifdef __cplusplus
}
#endif

#endif
