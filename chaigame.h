#include <SDL.h>

#ifndef __DISABLE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>
#endif

// TODO: Fix Chai loading with the Standard Library.
//#include <chaiscript/chaiscript_stdlib.hpp>

class ChaiGame {
public:
    static ChaiGame* getInstance();
    static bool isRunning();
	static ChaiGame* m_instance;
	static void destroy();

	//ChaiGame() : chai(chaiscript::Std_Lib::library()) {
	ChaiGame() {
		x = 100;
		y = 100;
	}

	#ifndef __DISABLE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	#endif

	SDL_Surface* screen;
	SDL_Event event;

	int x, y;
	void quit_app(void);
	bool init_app();
	bool checkInput();
	void exec_app();
	uint32_t *videoBuffer;
};
