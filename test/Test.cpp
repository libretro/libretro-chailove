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
	app->graphics.setColor(0, 255, 100);
	app->graphics.print("Hello World! Press UP", 100, app->graphics.getHeight() - 100);

	if (app->joystick[0].isDown("up")) {
		app->graphics.setColor(100, 0, 255);
		app->graphics.ellipse("fill", 200, 200, 75, 20);
	}
}

#endif
