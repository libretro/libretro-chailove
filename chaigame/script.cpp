#include "script.h"
#include "chaigame.h"
#include "../Application.h"

#ifndef __DISABLE_CHAISCRIPT__
using namespace chaiscript;
#endif

namespace chaigame {
	script::script() {
		#ifndef __DISABLE_CHAISCRIPT__
		Application* app = Application::getInstance();

		// Register the Graphics module.
		chai.add(fun(&graphics::rectangle), "rectangle");
		chai.add(fun(&graphics::newImage), "newImage");
		chai.add(fun(&graphics::print), "print");
		chai.add(fun(&graphics::setColor), "setColor");
		chai.add(fun<void, graphics, Image*, int, int>(&graphics::draw), "draw");
		chai.add_global(var(std::ref(app->graphics)), "graphics");

		// Register the Keyboard module.
		chai.add(fun(&keyboard::update), "update");
		chai.add(fun(&keyboard::isDown), "isDown");
		chai.add_global(var(std::ref(app->keyboard)), "keyboard");

		// Register the Image module.
		chai.add(fun(&image::newImageData), "newImageData");
		chai.add_global(var(std::ref(app->image)), "image");

		// Register the Filesystem module.
		chai.add(fun(&filesystem::read), "read");
		chai.add_global(var(std::ref(app->filesystem)), "filesystem");

		// Register the System module.
		chai.add(fun(&system::getOS), "getOS");
		chai.add_global(var(std::ref(app->system)), "system");

		// Register the Sound module.
		chai.add(fun(&sound::newSoundData), "newSoundData");
		chai.add_global(var(std::ref(app->sound)), "sound");

		// Register the Audio module.
		chai.add(fun(&audio::play), "play");
		chai.add_global(var(std::ref(app->audio)), "audio");

		// Load main.chai.
		std::string file("main.chai");
		std::string contents = app->filesystem.read(file);
		chai.eval(contents);

		// Find the game functions.
		chaiload = chai.eval<std::function<void ()> >("load");
		chaiupdate = chai.eval<std::function<void (double)> >("update");
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
