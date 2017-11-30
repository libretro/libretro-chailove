/**
 * \mainpage ChaiLove API
 *
 * This is the API documentation for [ChaiLove](https://github.com/RobLoach/ChaiLove). For more information about ChaiLove itself, see the [ChaiLove homepage](https://github.com/RobLoach/ChaiLove).
 *
 * When beginning to write games using ChaiLove, the most important parts of the API are the callbacks: `load` to do one-time setup of your game, `update` which is used to manage your game's state frame-to-frame, and `draw` which is used to render the game state onto the screen.
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
 * def update(dt) {
 * 	x += dt * 60.0f
 * 	y += dt * 30.0f
 * }
 *
 * def draw() {
 *     graphics.print("Hello World!", 100, 100)
 *     graphics.draw(logo, x, y)
 * }
 * @endcode
 *
 * ## Modules
 *
 * - \link Modules::audio audio \endlink Provides an interface to output sound to the user's speakers.
 * - \link Modules::event event \endlink Manages events, like keypresses.
 * - \link Modules::filesystem filesystem \endlink Provides an interface to the user's filesystem.
 * - \link Modules::font font \endlink Allows you to work with fonts.
 * - \link Modules::graphics graphics \endlink Drawing of shapes and images, management of screen geometry.
 * - \link Modules::image image \endlink Provides an interface to decode encoded image data.
 * - \link Modules::joystick joystick \endlink Provides an interface to connected joysticks.
 * - \link Modules::keyboard keyboard \endlink Provides an interface to the user's keyboard.
 * - \link Modules::math math \endlink Provides system-independent mathematical functions.
 * - \link Modules::mouse mouse \endlink Provides an interface to the user's mouse.
 * - \link Modules::sound sound \endlink This module is responsible for decoding sound files.
 * - \link Modules::script script \endlink This module is responsible for interacting with the script.
 * - \link Modules::system system \endlink Provides access to information about the user's system.
 * - \link Modules::timer timer \endlink Provides high-resolution timing functionality.
 * - \link Modules::window window \endlink Provides an interface for the program's window.
 *
 */

#ifndef SRC_CHAILOVE_H_
#define SRC_CHAILOVE_H_

#define CHAILOVE_VERSION_MAJOR 0
#define CHAILOVE_VERSION_MINOR 9
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "0.9.0"

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

#endif  // SRC_CHAILOVE_H_
