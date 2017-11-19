
#ifdef __HAVE_TESTS__
#ifndef CHAILOVE_TEST_TEST_H
#define CHAILOVE_TEST_TEST_H

#include "../src/Types/Graphics/Image.h"
#include "../src/Types/Graphics/Font.h"
#include "../src/Types/System/Config.h"
#include "../src/Types/Audio/SoundData.h"

using Types::Graphics::Image;
using Types::Graphics::Font;
using Types::System::Config;
using Types::Audio::SoundData;
using ::ChaiLove;

class Test {
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
