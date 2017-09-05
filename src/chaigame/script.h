#ifndef CHAIGAME_SCRIPT_H
#define CHAIGAME_SCRIPT_H

#include <string>
#include "system/Config.h"

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
		void mousepressed(int x, int y, int button);
		void mousereleased(int x, int y, int button);

		#ifdef __HAVE_CHAISCRIPT__
		chaiscript::ChaiScript chai;
		std::function<void ()> chaiload;
		std::function<void (Config&)> chaiconf;
		std::function<void (float)> chaiupdate;
		std::function<void ()> chaidraw;
		std::function<void (int, int)> chaijoystickpressed;
		std::function<void (int, int)> chaijoystickreleased;
		std::function<void (int, int, int)> chaimousepressed;
		std::function<void (int, int, int)> chaimousereleased;
		bool hasUpdate = true;
		bool hasDraw = true;
		bool hasjoystickpressed = true;
		bool hasjoystickreleased = true;
		bool hasmousepressed = true;
		bool hasmousereleased = true;
		bool hasload = true;
		bool hasconf = true;
		#endif

		std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
	};
}

#endif
