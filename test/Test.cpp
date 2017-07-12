#ifdef __HAVE_TESTS__

#include "Test.h"
#include "../chaigame/chaigame.h"
#include "../Application.h"

void Test::conf(chaigame::Config& t) {
	t.window.width = 400;
	t.window.height = 400;
}

bool Test::load() {

}

void Test::update(float delta) {
}

void Test::draw() {
	Application* app = Application::getInstance();
	app->graphics.setColor(200, 100, 100);
	app->graphics.print("Test.cpp: Hello World!", 100, app->graphics.getHeight() - 100);

	app->graphics.setColor(200, 200, 200);
	app->graphics.ellipse("fill", 200, 200, 75, 20);
}

#endif
