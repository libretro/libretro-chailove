#include "system.h"

#include <string>

#include "../Application.h"

namespace chaigame {
	std::string system::getOS() {
		return "libretro";
	}

	void system::loadModule(const std::string& moduleName) {
		Application* app = Application::getInstance();
		app->script->loadModule(moduleName);
	}
}
