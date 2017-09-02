#include "audio.h"
//#include "SDL.h"
//#include "SDL_mixer.h"
#include <string>

#include "audio/SoundData.h"
#include "../Game.h"

namespace chaigame {
	void audio::play(SoundData* soundData) {
		if (soundData) {
			soundData->play();
		}
	}

	SoundData* audio::newSource(const std::string& filename, const std::string& type) {
		return Game::getInstance()->sound.newSoundData(filename, type);
	}

	SoundData* audio::newSource(const std::string& filename) {
		return Game::getInstance()->sound.newSoundData(filename);
	}


void audio::mixer_render(int16_t *buffer)
{
   // Clear buffer
   memset(buffer, 0, AUDIO_FRAMES * 2 * sizeof(int16_t));

   // Loop over audio sources
   for (unsigned i = 0; i < num_sources; i++)
   {
      if (sources[i]->state == AUDIO_STOPPED)
         continue;

      uint8_t* rawsamples8 = calloc(
         AUDIO_FRAMES * sources[i]->bps, sizeof(uint8_t));

      bool end = ! fread(rawsamples8,
            sizeof(uint8_t),
            AUDIO_FRAMES * sources[i]->bps,
            sources[i]->sndta.fp);

      int16_t* rawsamples16 = (int16_t*)rawsamples8;

      for (unsigned j = 0; j < AUDIO_FRAMES; j++)
      {
         int16_t left = 0;
         int16_t right = 0;
         if (sources[i]->sndta.head.NumChannels == 1 && sources[i]->sndta.head.BitsPerSample ==  8) { left = right = rawsamples8[j]*64; }
         if (sources[i]->sndta.head.NumChannels == 2 && sources[i]->sndta.head.BitsPerSample ==  8) { left = rawsamples8[j*2+0]*64; right=rawsamples8[j*2+1]*64; }
         if (sources[i]->sndta.head.NumChannels == 1 && sources[i]->sndta.head.BitsPerSample == 16) { left = right = rawsamples16[j]; }
         if (sources[i]->sndta.head.NumChannels == 2 && sources[i]->sndta.head.BitsPerSample == 16) { left = rawsamples16[j*2+0]; right=rawsamples16[j*2+1]; }
         buffer[j*2+0] += left  * sources[i]->volume * volume;
         buffer[j*2+1] += right * sources[i]->volume * volume;
      }

      if (end)
      {
         if (!sources[i]->loop)
            sources[i]->state = AUDIO_STOPPED;
         fseek(sources[i]->sndta.fp, WAV_HEADER_SIZE, SEEK_SET);
      }

      free(rawsamples8);
   }
}
}
