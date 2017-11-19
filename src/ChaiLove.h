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
 * - \link Modules::audio audio \endlink
 * - \link Modules::event event \endlink
 * - \link Modules::filesystem filesystem \endlink
 * - \link Modules::font font \endlink
 * - \link Modules::graphics graphics \endlink
 * - \link Modules::image image \endlink
 * - \link Modules::joystick joystick \endlink
 * - \link Modules::keyboard keyboard \endlink
 * - \link Modules::script script \endlink
 * - \link Modules::math math \endlink
 * - \link Modules::mouse mouse \endlink
 * - \link Modules::timer timer \endlink
 * - \link Modules::window window \endlink
 *
 * ## Example
 *
 * The below `main.chai` is a simple hello world example:
 *
 * @code
 * global logo
 * global x
 * global y
 *
 * def load() {
 * 	graphics.setBackgroundColor(54, 172, 248)
 * 	logo = graphics.newImage("logo.png")
 * 	x = 10.0f
 * 	y = 10.0f
 * }
 *
 * def draw() {
 *     graphics.print("Hello World!", 100, 100)
 *     graphics.draw(logo, x, y)
 * }
 *
 * def update(delta) {
 * 	x += delta * 60.0f
 * 	y += delta * 30.0f
 * }
 * @endcode
 */

 #ifndef CHAILOVE_GAME_H
#define CHAILOVE_GAME_H

#define CHAILOVE_VERSION_MAJOR 0
#define CHAILOVE_VERSION_MINOR 8
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "0.8.0"

#include "SDL.h"
#include "libretro.h"
#include "Modules/keyboard.h"
#include "Types/System/Config.h"
#include "Modules/script.h"
#include "Modules/filesystem.h"
#include "Modules/graphics.h"
#include "Modules/image.h"
#include "Modules/system.h"
#include "Modules/sound.h"
#include "Modules/font.h"
#include "Modules/timer.h"
#include "Modules/audio.h"
#include "Modules/joystick.h"
#include "Modules/mouse.h"
#include "Modules/window.h"
#include "Modules/math.h"
#include "Modules/event.h"

#ifdef __HAVE_TESTS__
#include "test/Test.h"
#endif

using Types::System::Config;

class ChaiLove {
public:
    static ChaiLove* getInstance();
	static ChaiLove* m_instance;
	static void destroy();

	static retro_input_state_t input_state_cb;
	static retro_input_poll_t input_poll_cb;

	Config config;
	Modules::keyboard keyboard;
	Modules::script* script;
	Modules::filesystem filesystem;
	Modules::graphics graphics;
	Modules::image image;
	Modules::system system;
	Modules::sound sound;
	Modules::font font;
	Modules::timer timer;
	Modules::audio audio;
	Modules::joystick joystick;
	Modules::mouse mouse;
	Modules::math math;
	Modules::window window;
	Modules::event event;

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
