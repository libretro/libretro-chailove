
#ifdef __HAVE_TESTS__
#ifndef CHAILOVE_TEST_TEST_H
#define CHAILOVE_TEST_TEST_H

#include "../src/love/Types/Graphics/Image.h"
#include "../src/love/Types/Graphics/Font.h"
#include "../src/love/Types/System/Config.h"
#include "../src/love/Types/Audio/SoundData.h"

using love::Types::Graphics::Image;
using love::Types::Graphics::Font;
using love::Types::System::Config;
using love::Types::Audio::SoundData;
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
