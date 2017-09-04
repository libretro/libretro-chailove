#ifdef __HAVE_TESTS__
#ifndef CHAIGAME_TEST_TEST_H
#define CHAIGAME_TEST_TEST_H

#include "../src/chaigame/graphics/Font.h"
#include "../src/chaigame/system/Config.h"
#include "../src/chaigame/audio/SoundData.h"

class Test {
public:
	void conf(chaigame::Config& t);
	bool load();
	void update(float delta);
	void draw();
	int tester = 0;
	chaigame::Font* thefont;
	chaigame::Font* secondfont;
	chaigame::SoundData* jump;
};

#endif
#endif
