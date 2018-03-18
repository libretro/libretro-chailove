/**
 * \mainpage ChaiLove API
 *
 * This is the API documentation for [ChaiLove](https://github.com/libretro/libretro-chailove). For more information about ChaiLove itself, see the [ChaiLove homepage](https://github.com/libretro/libretro-chailove).
 *
 * When beginning to write games using ChaiLove, the most important parts of the API are the callbacks: `load` to do one-time setup of your game, `update` which is used to manage your game's state frame-to-frame, and `draw` which is used to render the game state onto the screen.
 *
 * @code
 * global logo
 * global x
 * global y
 *
 * def load() {
 *     love.graphics.setBackgroundColor(54, 172, 248)
 *     logo = love.graphics.newImage("logo.png")
 *     x = 10.0f
 *     y = 10.0f
 * }
 *
 * def update(dt) {
 *     x += dt * 60.0f
 *     y += dt * 30.0f
 * }
 *
 * def draw() {
 *     love.graphics.print("Hello World!", 100, 100)
 *     love.graphics.draw(logo, x, y)
 * }
 * @endcode
 *
 * ## Modules
 *
 * - \link love::audio audio \endlink Provides an interface to output sound to the user's speakers.
 * - \link love::config config \endlink Global ChaiLove configuration.
 * - \link love::console console \endlink The in-game debugging console.
 * - \link love::event event \endlink Manages events, like keypresses.
 * - \link love::filesystem filesystem \endlink Provides an interface to the user's filesystem.
 * - \link love::font font \endlink Allows you to work with fonts.
 * - \link love::graphics graphics \endlink Drawing of shapes and images, management of screen geometry.
 * - \link love::image image \endlink Provides an interface to decode encoded image data.
 * - \link love::joystick joystick \endlink Provides an interface to connected joysticks.
 * - \link love::keyboard keyboard \endlink Provides an interface to the user's keyboard.
 * - \link love::math math \endlink Provides system-independent mathematical functions.
 * - \link love::mouse mouse \endlink Provides an interface to the user's mouse.
 * - \link love::script script \endlink This module is responsible for callback events.
 * - \link love::sound sound \endlink This module is responsible for decoding sound files.
 * - \link love::system system \endlink Provides access to information about the user's system.
 * - \link love::timer timer \endlink Provides high-resolution timing functionality.
 * - \link love::window window \endlink Provides an interface for the program's window.
 *
 * ## Callbacks
 *
 * - \link love::script::conf conf(t) \endlink Global configuration callback.
 * - \link love::script::load load() \endlink This function is called exactly once at the beginning of the game.
 * - \link love::script::update update(dt) \endlink Callback function used to update the state of the game every frame.
 * - \link love::script::draw draw() \endlink Callback function used to draw on the screen every frame.
 * - \link love::script::reset reset() \endlink Callback function used when the frontend requests to reset the game.
 * - \link love::script::joystickpressed joystickpressed(joy, button) \endlink Called when a joystick button is pressed.
 * - \link love::script::joystickreleased joystickreleased(joy, button) \endlink Called when a joystick button is released.
 * - \link love::script::mousepressed mousepressed(x, y, button) \endlink Called when a mouse button is pressed.
 * - \link love::script::mousereleased mousereleased(x, y, button) \endlink Called when a mouse button is released.
 * - \link love::script::mousemoved mousemoved(x, y, dx, dy) \endlink Callback function triggered when the mouse is moved.
 * - \link love::script::keypressed keypressed(key, scancode) \endlink Callback function triggered when a key is pressed.
 * - \link love::script::keyreleased keyreleased(key, scancode) \endlink Callback function triggered when a key is released.
 * - \link love::script::savestate savestate() \endlink Callback function triggered to export JSON serialized data of the game state.
 * - \link love::script::loadstate loadstate(jsonData) \endlink Callback function triggered to load the given JSON serialized data.
 *
 */

#ifndef SRC_CHAILOVE_H_
#define SRC_CHAILOVE_H_

#define CHAILOVE_VERSION_MAJOR 0
#define CHAILOVE_VERSION_MINOR 17
#define CHAILOVE_VERSION_PATCH 0
#define CHAILOVE_VERSION_STRING "0.17.0"

#include "SDL.h"
#include "libretro.h"
#include "love/keyboard.h"
#include "love/config.h"
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
