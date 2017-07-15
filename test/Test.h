#ifndef CHAIGAME_TEST_TEST_H
#define CHAIGAME_TEST_TEST_H

#include "../chaigame/src/Font.h"
#include "../chaigame/src/Config.h"

class Test {
public:
	void conf(chaigame::Config& t);
	bool load();
	void update(float delta);
	void draw();
	int tester = 0;
	chaigame::Font* thefont;
	chaigame::Font* secondfont;
};

#endif
