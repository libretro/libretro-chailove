/**
 * \file ChaiLove.h
 *
 * Main header file for ChaiLove.
 */

/**
 * \mainpage ChaiLove API
 *
 * This is the API documentation for [ChaiLove](https://github.com/RobLoach/ChaiLove). For more information about ChaiLove itself, see the [ChaiLove homepage](https://github.com/RobLoach/ChaiLove).
 *
 * ## Modules
 *
 * - \link chailove::audio audio \endlink
 * - \link chailove::event event \endlink
 * - \link chailove::filesystem filesystem \endlink
 * - \link chailove::font font \endlink
 * - \link chailove::graphics graphics \endlink
 * - \link chailove::image image \endlink
 * - \link chailove::joystick joystick \endlink
 * - \link chailove::keyboard keyboard \endlink
 * - \link chailove::math math \endlink
 * - \link chailove::mouse mouse \endlink
 * - \link chailove::timer timer \endlink
 * - \link chailove::window window \endlink
 *
 * ## Example
 *
 * The below is a simple hello world example.
 *
 * \snippet simple/main.chai
 */

 #ifndef CHAILOVE_GAME_H
#define CHAILOVE_GAME_H

#define CHAILOVE_VERSION_MAJOR 0
#define CHAILOVE_VERSION_MINOR 7
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "0.7.0"

#include "SDL.h"
#include "libretro.h"
#include "chailove/keyboard.h"
#include "chailove/system/Config.h"
#include "chailove/script.h"
#include "chailove/filesystem.h"
#include "chailove/graphics.h"
#include "chailove/image.h"
#include "chailove/system.h"
#include "chailove/sound.h"
#include "chailove/font.h"
#include "chailove/timer.h"
#include "chailove/audio.h"
#include "chailove/joystick.h"
#include "chailove/mouse.h"
#include "chailove/window.h"
#include "chailove/math.h"
#include "chailove/event.h"

#ifdef __HAVE_TESTS__
#include "test/Test.h"
#endif

class ChaiLove {
public:
    static ChaiLove* getInstance();
	static ChaiLove* m_instance;
	static void destroy();

	static retro_input_state_t input_state_cb;
	static retro_input_poll_t input_poll_cb;

	chailove::Config config;
	chailove::keyboard keyboard;
	chailove::script* script;
	chailove::filesystem filesystem;
	chailove::graphics graphics;
	chailove::image image;
	chailove::system system;
	chailove::sound sound;
	chailove::font font;
	chailove::timer timer;
	chailove::audio audio;
	chailove::joystick joystick;
	chailove::mouse mouse;
	chailove::math math;
	chailove::window window;
	chailove::event event;

	void quit(void);
	bool load(const std::string& file);
	bool update();
	void draw();
	void reset();
	std::string savestate();
	bool loadstate(const std::string& data);

	uint32_t *videoBuffer;
	SDL_Surface* screen;
	SDL_Event sdlEvent;

	#ifdef __HAVE_TESTS__
	Test test;
	#endif
};

#endif
