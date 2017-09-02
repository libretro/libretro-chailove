#ifndef CHAIGAME_AUDIO_H
#define CHAIGAME_AUDIO_H

#include "audio/SoundData.h"
#include "sound.h"



#define AUDIO_FRAMES (44100 / 60)

typedef enum
{
   AUDIO_STOPPED = 0,
   AUDIO_PAUSED,
   AUDIO_PLAYING
} audio_source_state;

typedef struct
{
   snd_SoundData sndta;
   unsigned bps; // bytes per sample
   bool loop;
   float volume;
   float pitch;
   audio_source_state state;
} audio_Source;




namespace chaigame {
	class audio {
	public:
		void play(SoundData* soundData);
		SoundData* newSource(const std::string& filename, const std::string& type);
		SoundData* newSource(const std::string& filename);

		unsigned num_sources = 0;
		audio_Source** sources = NULL;
		float volume = 1.0;

		void mixer_render(int16_t *buffer);
	};
}
#endif
