#ifndef APPLICATION_H
#define ifndef APPLICATION_H

#include <SDL.h>

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
	Application() {
		x = 100;
		y = 100;
	}

	#ifndef __DISABLE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	std::function<void ()> chaiload;
	std::function<void ()> chaiupdate;
	std::function<void ()> chaidraw;
	#endif

	SDL_Surface* screen;
	SDL_Event event;

	int x, y;
	void quit(void);
	bool load();
	bool update();
	void draw();
	uint32_t *videoBuffer;
};

#endif
