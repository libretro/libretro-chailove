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
 * @brief Contains audio samples that you can playback.
 */
class SoundData {
	public:
	SoundData(const std::string& filename);
	~SoundData();

	/**
	 * @brief Plays a source.
	 */
	bool play();

	/**
	 * @brief Stops an audio source.
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
	 * @brief Gets the current volume of the Source.
	 */
	float getVolume();

	/**
	 * @brief Sets the current volume of the Source.
	 *
	 * @return The SoundData object iself, to allow for method chaining.
	 */
	SoundData& setVolume(float volume);

	/**
	 * @brief Returns whether the Source is playing.
	 *
	 * @return True if the sound is playing.
	 */
	bool isPlaying();

	/**
	 * @brief Resumes playing the given Source.
	 */
	bool resume();

	/**
	 * @brief Pauses the given Source.
	 */
	bool pause();

	int WAV_HEADER_SIZE = 44;

	/**
	 * @brief Returns whether the Source will loop.
	 */
	bool isLooping();

	/**
	 * @brief Set whether the Source should loop.
	 */
	SoundData& setLooping(bool loop);
};

}  // namespace Audio
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_AUDIO_SOUNDDATA_H_
