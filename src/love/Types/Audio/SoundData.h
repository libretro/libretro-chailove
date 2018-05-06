#ifndef SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
#define SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_

#include <string>
#include "AudioState.h"
#include "physfs.h"

namespace love {
namespace Types {
namespace Audio {

typedef struct {
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

typedef struct {
	PHYSFS_File* fp = NULL;
	wavhead_t head;
} snd_SoundData;

/**
 * Contains audio samples that you can playback.
 */
class SoundData {
	public:
	SoundData(const std::string& filename);
	~SoundData();

	/**
	 * Plays the source.
	 */
	bool play();

	/**
	 * Stops the audio source.
	 */
	bool stop();

	void unload();
	snd_SoundData sndta;
	unsigned bps = 0;
	bool loop = false;
	float m_volume = 1.0f;
	float pitch = 1.0f;
	AudioState state = Stopped;
	bool isLoaded();

	/**
	 * Gets the current volume of the Source.
	 *
	 * @return The volume of the source, from 0.0f to 1.0f.
	 */
	float getVolume();

	/**
	 * Sets the current volume of the Source.
	 *
	 * @param volume The volume to set the source at, from 0.0f to 1.0f.
	 *
	 * @return The SoundData object iself, to allow for method chaining.
	 */
	SoundData& setVolume(float volume);

	/**
	 * Returns whether the Source is playing.
	 *
	 * @return True if the sound is playing.
	 */
	bool isPlaying();

	/**
	 * Resumes playing the given Source.
	 */
	bool resume();

	/**
	 * Pauses the given Source.
	 */
	bool pause();

	/**
	 * Returns whether the Source will loop.
	 */
	bool isLooping();

	/**
	 * Set whether the Source should loop.
	 */
	SoundData& setLooping(bool loop);

	int WAV_HEADER_SIZE = 44;
};

}  // namespace Audio
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
