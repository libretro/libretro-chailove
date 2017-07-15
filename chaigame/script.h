#ifndef CHAIGAME_SCRIPT_H
#define CHAIGAME_SCRIPT_H

#include <string>
#include "src/Config.h"

#ifdef __HAVE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>

// TODO: Fix Chai loading with the Standard Library.
//#include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace chaigame {
	class script {
	public:
		script();

		void conf(Config& t);
		void load();
		void update(float delta);
		void draw();
		bool loadModule(const std::string& moduleName);
		void joystickpressed(int joystick, int button);
		void joystickreleased(int joystick, int button);

		#ifdef __HAVE_CHAISCRIPT__
		chaiscript::ChaiScript chai;
		std::function<void ()> chaiload;
		std::function<void (Config&)> chaiconf;
		std::function<void (float)> chaiupdate;
		std::function<void ()> chaidraw;
		std::function<void (int, int)> chaijoystickpressed;
		std::function<void (int, int)> chaijoystickreleased;
		bool hasUpdate = true;
		bool hasDraw = true;
		bool hasjoystickpressed = true;
		bool hasjoystickreleased = true;
		#endif

		std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
	};
}

#endif
