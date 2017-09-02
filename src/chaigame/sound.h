#ifndef CHAIGAME_SOUND_H
#define CHAIGAME_SOUND_H

#include "audio/SoundData.h"
#include <vector>



#define WAV_HEADER_SIZE 44

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
   void* fp;
   wavhead_t head;
} snd_SoundData;



namespace chaigame {
	class sound {
	public:
		bool load();
		bool hasAudio();
		void unload();
		SoundData* newSoundData(const std::string& file, const std::string& type);
		SoundData* newSoundData(const std::string& file);
		bool update();

		int numtimesopened = 0;
		int frequency = 0;
		int channels = 0;
    	int format;

    	bool initialized = false;
    	bool firstRun = true;
    	bool loaded = false;
    	bool toInit = false;

    	std::vector<SoundData*> sounds;
	};
}
#endif
