#ifdef __HAVE_TESTS__

#ifndef _TEST_H_INCLUDED_
#define _TEST_H_INCLUDED_

#include "../chaigame/chaigame.h"

class Test {
public:
	void conf(chaigame::Config& t);
	bool load();
	void update(float delta);
	void draw();
	int tester = 0;
};

#endif
#endif
