#ifndef SRC_LOVE_SCRIPT_H_
#define SRC_LOVE_SCRIPT_H_

#include <string>
#include "config.h"

#ifdef __HAVE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>

// TODO(RobLoach): Fix Chai loading with the Standard Library.
// #include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace love {

/**
 * @brief Global functions and events that are called.
 */
class script {
	public:
	script(const std::string& file);

	/**
	 * @brief Modify some configuration options.
	 *
	 * @param t The config object to modify.
	 *
	 * ### Example
	 *
	 * @code
	 * def conf(t) {
	 *   t.window.width = 1024
	 *   t.window.height = 768
	 * }
	 * @endcode
	 */
	void conf(config& t);

	/**
	 * @brief This function is called exactly once at the beginning of the game.
	 *
	 * ### Example
	 *
	 * Establish some variables/resources on the game load, so that they can be used repeatedly in other functions (such as script::draw).
	 *
	 * @code
	 * global hamster
	 *
	 * def load() {
	 *   hamster = love.graphics.newImage("hamster.png")
	 * }
	 *
	 * def draw() {
	 *   love.graphics.draw(hamster, 100, 100)
	 * }
	 * @endcode
	 */
	void load();

	/**
	 * @brief Callback function used to update the state of the game every frame.
	 *
	 * @param delta Time since the last update in seconds.
	 *
	 * ### Example
	 *
	 * Change a variable var at a constant rate (+/- 3 per second in this example).
	 *
	 * @code
	 * var position = 10
	 * var rate = 3
	 *
	 * def update(dt) {
	 *   if (love.keyboard.isDown("down")) {
	 *     position -= dt * rate
	 *   }
	 *   if (love.keyboard.isDown("up")) {
	 *     position += dt * rate
	 *   }
	 * }
	 * @endcode
	 */
	void update(float delta);

	/**
	 * @brief Callback function used to draw on the screen every frame.
	 *
	 * ### Example
	 *
	 * Draw an image that was loaded in script::load (putting graphics.newImage in script::draw would cause the image to be reloaded every frame, which would cause issues).
	 *
	 * @code
	 * global hamster
	 *
	 * dev load() {
	 *   hamster = love.graphics.newImage("hamster.png")
	 * }
	 *
	 * def draw() {
	 *   love.graphics.draw(hamster, 100, 100)
	 * }
	 * @endcode
	 */
	void draw();

	/**
	 * @brief Called when the game is requested to be reset.
	 *
	 * ### Example
	 *
	 * @code
	 * global textX = 10
	 *
	 * dev update(dt) {
	 *   textX += dt * 20
	 * }
	 *
	 * def draw() {
	 *   love.graphics.print("Hello World", textX, 100)
	 * }
	 *
	 * def reset() {
	 *   textX = 10
	 * }
	 * @endcode
	 */
	void reset();

	bool loadModule(const std::string& moduleName);

	/**
	 * @brief Called when a joystick button is pressed.
	 *
	 * @param joystick The joystick number.
	 * @param button The name of which button was released.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonPressed = ""
	 *
	 * def draw() {
	 *   love.graphics.print("Button Pressed: " + buttonPressed, 100, 100)
	 * }
	 *
	 * def joystickpressed(joy, button) {
	 *   buttonPressed = button
	 * }
	 * @endcode
	 */
	void joystickpressed(int joystick, const std::string& button);

	/**
	 * @brief Called when a joystick button is released.
	 *
	 * @param joystick The joystick number.
	 * @param button The name of which button was released.
	 *
	 * ### Example
	 *
	 * @code
	 * global buttonReleased = ""
	 *
	 * def draw() {
	 *   love.graphics.print("Button Released: " + buttonReleased, 100, 100)
	 * }
	 *
	 * def joystickreleased(joy, button) {
	 *   buttonReleased = button
	 * }
	 * @endcode
	 */
	void joystickreleased(int joystick, const std::string& button);

	/**
	 * @brief Called when a mouse button is pressed.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param button The mouse button name of which was pressed.
	 */
	void mousepressed(int x, int y, const std::string& button);

	/**
	 * @brief Called when a mouse button is released.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param button The mouse button name of which was released.
	 */
	void mousereleased(int x, int y, const std::string& button);

	/**
	 * @brief Called when the mouse is moved.
	 *
	 * @param x The mouse position on the x-axis.
	 * @param y The mouse position on the y-axis.
	 * @param dx The amount moved along the x-axis since the last time love.mousemoved was called.
	 * @param dy The amount moved along the y-axis since the last time love.mousemoved was called.
	 */
	void mousemoved(int x, int y, int dx, int dy);

	/**
	 * @brief Called when a key on the keyboard has been pressed.
	 *
	 * @param key The name of the key that was pressed.
	 * @param scancode The scancode of the key that was pressed.
	 */
	void keypressed(const std::string& key, int scancode);

	/**
	 * @brief Called when a key on the keyboard is released.
	 *
	 * @param key The name of the key that was released.
	 * @param scancode The scancode of the key that was released.
	 */
	void keyreleased(const std::string& key, int scancode);

	/**
	 * @brief Called when requested to save the current state.
	 *
	 * @return string A JSON array representing the current state.
	 */
	std::string savestate();

	/**
	 * @brief Called when requested to load a state.
	 *
	 * @param data A JSON array representing the state to load.
	 *
	 * @return bool True if loading the state succeeded.
	 */
	bool loadstate(const std::string& data);

	chaiscript::Boxed_Value eval(const std::string& code, const std::string& filename);
	std::string evalString(const std::string& code, const std::string& filename);

	#ifdef __HAVE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	std::function<void()> chaiload;
	std::function<void(config&)> chaiconf;
	std::function<void(float)> chaiupdate;
	std::function<void()> chaidraw;
	std::function<void()> chaireset;
	std::function<bool(std::string)> chailoadstate;
	std::function<std::string()> chaisavestate;
	std::function<void(int, const std::string&)> chaijoystickpressed;
	std::function<void(int, const std::string&)> chaijoystickreleased;
	std::function<void(int, int, const std::string&)> chaimousepressed;
	std::function<void(int, int, const std::string&)> chaimousereleased;
	std::function<void(int, int, int, int)> chaimousemoved;
	std::function<void(const std::string&, int)> chaikeypressed;
	std::function<void(const std::string&, int)> chaikeyreleased;
	bool hasUpdate = true;
	bool hasDraw = true;
	bool hasjoystickpressed = true;
	bool hasjoystickreleased = true;
	bool hasmousepressed = true;
	bool hasmousereleased = true;
	bool hasmousemoved = true;
	bool haskeypressed = true;
	bool haskeyreleased = true;
	bool hasloadstate = true;
	bool hassavestate = true;
	bool hasload = true;
	bool hasconf = true;
	bool hasreset = true;
	#endif

	std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
};

}  // namespace love

#endif  // SRC_LOVE_SCRIPT_H_
