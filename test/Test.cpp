#ifdef __HAVE_TESTS__

#include "Test.h"
#include "../chaigame/chaigame.h"
#include "../Application.h"

void Test::conf(chaigame::Config& t) {
	t.window.width = 1080;
	t.window.height = 768;
}

bool Test::load() {
	Application* app = Application::getInstance();
	thefont = app->graphics.newFont("test/examples/assets/Raleway-Regular.ttf", 60);
}

void Test::update(float delta) {}

void Test::draw() {
	Application* app = Application::getInstance();

	app->graphics.setColor(77, 182, 172);
	app->graphics.ellipse("fill", 300, 400, 200, 180);

	app->graphics.setColor(100, 181, 246);
	app->graphics.setFont(thefont);
	app->graphics.print("Hello World!", 300, 100);
}

#endif
