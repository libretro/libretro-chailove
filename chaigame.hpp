#include <SDL.h>
#include <chaiscript/chaiscript.hpp>

// TODO: Fix Chai loading with the Standard Library.
//#include <chaiscript/chaiscript_stdlib.hpp>

class ChaiGame {
public:
    static ChaiGame* getInstance();
	static ChaiGame* m_instance;

	//ChaiGame() : chai(chaiscript::Std_Lib::library()) {
	ChaiGame() {
		x = 100;
		y = 100;
	}

	//chaiscript::ChaiScript chai;
	chaiscript::ChaiScript chai;
	SDL_Surface* screen;
	SDL_Event event;
	int x, y;
	void quit_app(void);
	bool init_app();
	void checkInput();
	void exec_app();
};
