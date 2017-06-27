#include "script.h"
#include "chaigame.h"
#include <string>
#include "../Application.h"
using namespace chaiscript;

namespace chaigame {
	script::script() {
		#ifndef __DISABLE_CHAISCRIPT__
		Application* app = Application::getInstance();

		// Register the Graphics module.
		chai.add(fun(&graphics::rectangle), "rectangle");
		chai.add(fun(&graphics::newImage), "newImage");
		chai.add(fun<void, graphics, Image*>(&graphics::draw), "draw");
		chai.add_global(var(std::ref(app->graphics)), "graphics");

		// Register the Keyboard module.
		chai.add(fun(&keyboard::update), "update");
		chai.add(fun(&keyboard::isDown), "isDown");
		chai.add_global(var(std::ref(app->keyboard)), "keyboard");

		// Register the Image module.
		chai.add(fun(&image::newImageData), "newImageData");
		chai.add_global(var(std::ref(app->image)), "image");

		// Load main.chai.
		chai.eval_file("main.chai");

		// Find the game functions.
		chaiload = chai.eval<std::function<void ()> >("load");
		chaiupdate = chai.eval<std::function<void (Uint32)> >("update");
		chaidraw = chai.eval<std::function<void ()> >("draw");
		#endif
	}

	void script::load() {
		#ifndef __DISABLE_CHAISCRIPT__
		chaiload();
		#endif
	}

	void script::update(Uint32 delta) {
		#ifndef __DISABLE_CHAISCRIPT__
		chaiupdate(delta);
		#endif
	}

	void script::draw() {
		#ifndef __DISABLE_CHAISCRIPT__
		chaidraw();
		#endif
	}
}
