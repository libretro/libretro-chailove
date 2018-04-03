/**
 * \mainpage ChaiLove API
 *
 * [ChaiLove](https://github.com/libretro/libretro-chailove) is a framework for making 2D games in the [ChaiScript scripting language](http://chaiscript.com/). ChaiLove is totally free, and can be used in anything from friendly open-source hobby projects, to evil, closed-source commercial ones.
 *
 * Some interesting places to go from here:
 * - \link ::love love \endlink (the module)
 * - \link love::audio love.audio \endlink Provides an interface to output sound to the user's speakers.
 * - \link love::config love.config \endlink Global ChaiLove configuration.
 * - \link love::console love.console \endlink The in-game debugging console.
 * - \link love::event love.event \endlink Manages events, like keypresses.
 * - \link love::filesystem love.filesystem \endlink Provides an interface to the user's filesystem.
 * - \link love::font love.font \endlink Allows you to work with fonts.
 * - \link love::graphics love.graphics \endlink Drawing of shapes and images, management of screen geometry.
 * - \link love::image love.image \endlink Provides an interface to decode encoded image data.
 * - \link love::joystick love.joystick \endlink Provides an interface to connected joysticks.
 * - \link love::keyboard love.keyboard \endlink Provides an interface to the user's keyboard.
 * - \link love::math love.math \endlink Provides system-independent mathematical functions.
 * - \link love::mouse love.mouse \endlink Provides an interface to the user's mouse.
 * - \link love::script love.script \endlink This module is responsible for callback events.
 * - \link love::sound love.sound \endlink This module is responsible for decoding sound files.
 * - \link love::system love.system \endlink Provides access to information about the user's system.
 * - \link love::timer love.timer \endlink Provides high-resolution timing functionality.
 * - \link love::window love.window \endlink Provides an interface for the program's window.
 *
 * ## ChaiScript
 *
 * Never used ChaiScript before? It's a really cool language! This manual won't teach you ChaiScript, but fortunately there are other good resources for that.
 *
 * - [ChaiScript Cheatsheet](https://git.io/vxPqI)
 * - [ChaiScript Documentation](http://chaiscript.com/docs.html)
 *
 * ## Hello World
 *
 * This is the full source for 'hello world' in ChaiLove, using a `main.chai` file. Running this code will cause an 640 by 480 window to appear, and display white text on a black background.
 *
 * @code
 * def draw() {
 *     love.graphics.print("Hello World!", 200, 250)
 * }
 * @endcode
 */

#ifndef SRC_CHAILOVE_H_
#define SRC_CHAILOVE_H_

#define CHAILOVE_VERSION_MAJOR 0
#define CHAILOVE_VERSION_MINOR 18
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "0.18.0"

#include "SDL.h"
#include "libretro.h"
#include "love/keyboard.h"
#include "love/config.h"
#include "love/data.h"
#include "love/script.h"
#include "love/filesystem.h"
#include "love/graphics.h"
#include "love/image.h"
#include "love/system.h"
#include "love/sound.h"
#include "love/font.h"
#include "love/timer.h"
#include "love/audio.h"
#include "love/joystick.h"
#include "love/mouse.h"
#include "love/window.h"
#include "love/math.h"
#include "love/event.h"
#include "love/console.h"

#ifdef __HAVE_TESTS__
#include "../test/native/NativeTest.h"
#endif

class ChaiLove {
	public:
	static ChaiLove* getInstance();
	static ChaiLove* m_instance;
	static void destroy();

	static retro_input_state_t input_state_cb;
	static retro_input_poll_t input_poll_cb;
	static retro_environment_t environ_cb;

	love::config config;
	love::console console;
	love::keyboard keyboard;
	love::script* script;
	love::data data;
	love::filesystem filesystem;
	love::graphics graphics;
	love::image image;
	love::system system;
	love::sound sound;
	love::font font;
	love::timer timer;
	love::audio audio;
	love::joystick joystick;
	love::mouse mouse;
	love::math math;
	love::window window;
	love::event event;

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
	NativeTest test;
	#endif
};

#endif  // SRC_CHAILOVE_H_
