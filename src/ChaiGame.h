#ifndef CHAIGAME_GAME_H
#define CHAIGAME_GAME_H

#define CHAIGAME_VERSION_MAJOR 0
#define CHAIGAME_VERSION_MINOR 4
#define CHAIGAME_VERSION_PATCH 0
#define CHAIGAME_VERSION_STRING "0.4.0"

#include "SDL.h"
#include "libretro.h"
#include "chaigame/keyboard.h"
#include "chaigame/system/Config.h"
#include "chaigame/script.h"
#include "chaigame/filesystem.h"
#include "chaigame/graphics.h"
#include "chaigame/image.h"
#include "chaigame/system.h"
#include "chaigame/sound.h"
#include "chaigame/font.h"
#include "chaigame/timer.h"
#include "chaigame/audio.h"
#include "chaigame/joystick.h"
#include "chaigame/mouse.h"
#include "chaigame/window.h"
#include "chaigame/math.h"
#include "chaigame/event.h"

#ifdef __HAVE_TESTS__
#include "test/Test.h"
#endif

class ChaiGame {
public:
    static ChaiGame* getInstance();
	static ChaiGame* m_instance;
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
	chaigame::font font;
	chaigame::timer timer;
	chaigame::audio audio;
	chaigame::joystick joystick;
	chaigame::mouse mouse;
	chaigame::math math;
	chaigame::window window;
	chaigame::event event;

	void quit(void);
	bool load(const std::string& file);
	bool update();
	void draw();
	void reset();
	std::string savestate();
	bool loadstate(std::string data);

	uint32_t *videoBuffer;
	SDL_Surface* screen;
	SDL_Event sdlEvent;

	#ifdef __HAVE_TESTS__
	Test test;
	#endif
};

#endif
