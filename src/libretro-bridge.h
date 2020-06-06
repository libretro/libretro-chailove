#ifndef LIBRETRO_BRIDGE_H__
#define LIBRETRO_BRIDGE_H__

#include "libretro.h"

static retro_input_state_t input_state_cb;



static retro_video_refresh_t video_cb;
// This is needed to allow SDL-libretro to compile.
// @see SDL_LIBRETROaudio.c:37
// retro_audio_sample_t audio_cb;

void libretro_audio_cb(int16_t left, int16_t right);

short int libretro_input_state_cb(unsigned port, unsigned device, unsigned index, unsigned id);

#endif
