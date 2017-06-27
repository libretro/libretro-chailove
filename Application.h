#ifndef APPLICATION_H
#define ifndef APPLICATION_H

#include <SDL.h>
#include "chaigame/chaigame.h"

#ifndef __DISABLE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>
#endif

// TODO: Fix Chai loading with the Standard Library.
//#include <chaiscript/chaiscript_stdlib.hpp>

class Application {
public:
    static Application* getInstance();
    static bool isRunning();
	static Application* m_instance;
	static void destroy();

	//Application() : chai(chaiscript::Std_Lib::library()) {
	//Application() {
	//}

	#ifndef __DISABLE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	std::function<void ()> chaiload;
	std::function<void (Uint32)> chaiupdate;
	std::function<void ()> chaidraw;
	#endif

	SDL_Surface* screen;
	SDL_Event event;

	chaigame::keyboard keyboard;

	void quit(void);
	bool load();
	bool update();
	void draw();
	uint32_t *videoBuffer;
	Uint32 tick;
};

#endif
