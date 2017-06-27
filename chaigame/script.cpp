#include "script.h"
#include "chaigame.h"
#include <string>
#include "../Application.h"

namespace chaigame {
	script::script() {
		#ifndef __DISABLE_CHAISCRIPT__
		// Register the Graphics module.
		chai.add(chaiscript::fun(&chaigame::graphics::rectangle), "rectangle");
		chai.add_global(chaiscript::var(std::ref(Application::getInstance()->graphics)), "graphics");

		// Register the Keyboard module.
		chai.add(chaiscript::fun(&chaigame::keyboard::update), "update");
		chai.add(chaiscript::fun(&chaigame::keyboard::isDown), "isDown");
		chai.add_global(chaiscript::var(std::ref(Application::getInstance()->keyboard)), "keyboard");

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
