
#ifdef __HAVE_TESTS__
#ifndef CHAILOVE_TEST_NATIVE_MAIN_H
#define CHAILOVE_TEST_NATIVE_MAIN_H

#include "../../src/ChaiLove.h"

using love::Types::Graphics::Image;
using love::Types::Graphics::Font;
using love::Types::System::Config;
using love::Types::Audio::SoundData;
using ::ChaiLove;

class Main {
public:
	void conf(Config& t);
	bool load();
	void update(float delta);
	void draw();
	int tester = 0;
	Font* thefont;
	Font* secondfont;
	SoundData* jump;
	Image* img;
	ChaiLove* app;
};

#endif
#endif
