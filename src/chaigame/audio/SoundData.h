#ifndef CHAIGAME_UTILITY_SOUNDDATA_H
#define CHAIGAME_UTILITY_SOUNDDATA_H

//#include "SDL.h"
//#include "SDL_mixer.h"
#include <string>
#include "AudioState.h"
#include "physfs.h"

typedef struct
{
   char ChunkID[4];
   uint32_t ChunkSize;
   char Format[4];
   char Subchunk1ID[4];
   uint32_t Subchunk1Size;
   uint16_t AudioFormat;
   uint16_t NumChannels;
   uint32_t SampleRate;
   uint32_t ByteRate;
   uint16_t BlockAlign;
   uint16_t BitsPerSample;
   char Subchunk2ID[4];
   uint32_t Subchunk2Size;
} wavhead_t;

typedef struct
{
   PHYSFS_File* fp = NULL;
   wavhead_t head;
} snd_SoundData;

namespace chaigame {
	class SoundData {
	public:
		SoundData(const std::string& filename);
		bool play();
		bool stop();
		snd_SoundData sndta;
		unsigned bps = 0;
		bool loop = false;
		float volume = 1.0f;
		float pitch = 1.0f;
		AudioState state = Stopped;
		bool isLoaded();
		bool isPlaying();
		int WAV_HEADER_SIZE = 44;
	};
}

#endif
