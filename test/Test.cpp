#ifdef __HAVE_TESTS__

#include "Test.h"
#include "../chaigame/chaigame.h"
#include "../Application.h"

void Test::conf(chaigame::Config& t) {
	t.window.width = 1024;
	t.window.height = 768;
}

bool Test::load() {

}

void Test::update(float delta) {
}

void Test::draw() {
	Application* app = Application::getInstance();
	app->graphics.print("Hello World!", 100, 100);
}

#endif
