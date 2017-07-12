#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL.h>
#include <libretro.h>
#include "chaigame/chaigame.h"

#ifdef __HAVE_TESTS__
#include "test/Test.h"
#endif

class Application {
public:
    static Application* getInstance();
	static Application* m_instance;
	static void destroy();

	static retro_input_state_t input_state_cb;
	static retro_input_poll_t input_poll_cb;

	chaigame::Config config;
	chaigame::keyboard keyboard;
	chaigame::script* script;
	chaigame::filesystem filesystem;
	chaigame::graphics graphics;
	chaigame::image image;
	chaigame::system system;
	chaigame::sound sound;
	chaigame::timer timer;
	chaigame::audio audio;
	chaigame::joystick joystick;
	chaigame::mouse mouse;
	chaigame::math math;
	chaigame::window window;

	void quit(void);
	bool load(const std::string& file);
	bool update();
	void draw();
	bool running = true;

	uint32_t *videoBuffer;
	SDL_Surface* screen;
	SDL_Event event;

	#ifdef __HAVE_TESTS__
	Test test;
	#endif

	void joystickpressed(int joystick, int button);
};

#endif
