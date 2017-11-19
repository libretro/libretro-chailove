
#ifdef __HAVE_TESTS__
#ifndef CHAILOVE_TEST_TEST_H
#define CHAILOVE_TEST_TEST_H

#include "../src/chailove/graphics/Image.h"
#include "../src/chailove/graphics/Font.h"
#include "../src/chailove/system/Config.h"
#include "../src/chailove/audio/SoundData.h"

class Test {
public:
	void conf(chailove::Config& t);
	bool load();
	void update(float delta);
	void draw();
	int tester = 0;
	chailove::Font* thefont;
	chailove::Font* secondfont;
	chailove::SoundData* jump;
	chailove::Image* img;
};

#endif
#endif
