#ifndef _SCRIPT_H_INCLUDED_
#define _SCRIPT_H_INCLUDED_

#include <SDL.h>
#include <string>

#ifdef __HAVE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>

// TODO: Fix Chai loading with the Standard Library.
//#include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace chaigame {
	class script {
	public:
		script();

		void load();
		void update(float delta);
		void draw();
		bool loadModule(const std::string& moduleName);

		#ifdef __HAVE_CHAISCRIPT__
		chaiscript::ChaiScript chai;
		std::function<void ()> chaiload;
		std::function<void (float)> chaiupdate;
		std::function<void ()> chaidraw;
		#endif
	};
}

#endif
