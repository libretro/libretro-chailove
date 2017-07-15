#ifdef __HAVE_TESTS__

#include "Test.h"
#include "../Game.h"

void Test::conf(chaigame::Config& t) {
	t.window.width = 1080;
	t.window.height = 768;
}

bool Test::load() {
	Game* app = Game::getInstance();
	app->filesystem.mount("test", "/");
	secondfont = app->graphics.newFont("examples/assets/Raleway-Regular.ttf", 60);
	thefont = app->graphics.newFont("examples/assets/c64_16x16.png", 16, 16, "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
}

void Test::update(float delta) {}

void Test::draw() {
	Game* app = Game::getInstance();

	app->graphics.setColor(77, 182, 172);
	app->graphics.ellipse("fill", 0, 768, 200, 180);

	int width = thefont->getWidth("Bitmap Commodore Font!");
	int height = app->graphics.getHeight() / 2.0f - thefont->getHeight() / 2.0f;

	app->graphics.setColor(100, 181, 246);
	app->graphics.setFont(thefont);
	app->graphics.print("Bitmap Commodore Font!", app->graphics.getWidth() / 2.0f - width / 2.0f, 200);

	app->graphics.setColor(255, 181, 0);
	app->graphics.setFont(secondfont);

	width = secondfont->getWidth("TTF Font here!");
	height = app->graphics.getHeight() / 2.0f - secondfont->getHeight() / 2.0f;
	app->graphics.print("TTF Font here!", app->graphics.getWidth() / 2.0f - width / 2.0f, height);
}

#endif
