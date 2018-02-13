
#ifdef __HAVE_TESTS__
#ifndef CHAILOVE_TEST_NATIVE_MAIN_H
#define CHAILOVE_TEST_NATIVE_MAIN_H

#include "../../src/love/Types/Graphics/Image.h"
#include "../../src/love/Types/Graphics/Font.h"
#include "../../src/love/config.h"
#include "../../src/love/Types/Audio/SoundData.h"

#include "../../src/ChaiLove.h"

using love::Types::Graphics::Image;
using love::Types::Graphics::Font;
using love::config;
using love::Types::Audio::SoundData;
using ::ChaiLove;

class Main {
public:
	void conf(config& t);
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
