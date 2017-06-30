#ifndef _AUDIO_H_INCLUDED_
#define _AUDIO_H_INCLUDED_

#include "src/SoundData.h"

namespace chaigame {
	class audio {
	public:
		void play(SoundData* soundData);
	};
}

#endif
