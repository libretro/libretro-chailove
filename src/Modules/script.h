#ifndef SRC_MODULES_SCRIPT_H_
#define SRC_MODULES_SCRIPT_H_

#include <string>
#include "../Types/System/Config.h"

#ifdef __HAVE_CHAISCRIPT__
#include <chaiscript/chaiscript.hpp>

// TODO(RobLoach): Fix Chai loading with the Standard Library.
// #include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace Modules {

/**
 * @brief Global functions and events that are called.
 */
class script {
	public:
	script(const std::string& file);

	/**
	 * @brief Modify some configuration options.
	 *
	 * @param t The Config object to modify.
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
	void conf(::Types::System::Config& t);

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
	 *   hamster = graphics.newImage("hamster.png")
	 * }
	 *
	 * def draw() {
	 *   graphics.draw(hamster, 100, 100)
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
	 *   if (keyboard.isDown("down")) {
	 *     position -= dt * rate
	 *   }
	 *   if (keyboard.isDown("up")) {
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
	 *   hamster = graphics.newImage("hamster.png")
	 * }
	 *
	 * def love.draw() {
	 *   graphics.draw(hamster, 100, 100)
	 * }
	 * @endcode
	 */
	void draw();

	/**
	 * @brief Called when the game is requested to be reset.
	 */
	void reset();
	bool loadModule(const std::string& moduleName);

	/**
	 * @brief Called when a joystick button is pressed.
	 */
	void joystickpressed(int joystick, const std::string& button);

	/**
	 * @brief Called when a joystick button is released.
	 */
	void joystickreleased(int joystick, const std::string& button);

	/**
	 * @brief Called when a mouse button is pressed.
	 */
	void mousepressed(int x, int y, int button);

	/**
	 * @brief Called when a mouse button is released.
	 */
	void mousereleased(int x, int y, int button);

	/**
	 * @brief Called when the mouse is moved.
	 */
	void mousemove(int x, int y);

	/**
	 * @brief Called when a key on the keyboard has been pressed.
	 */
	void keypressed(const std::string& key, int scancode);

	/**
	 * @brief Called when a key on the keyboard is released.
	 */
	void keyreleased(const std::string& key, int scancode);

	/**
	 * @brief Called when requested to save the current state.
	 *
	 * @return A JSON array representing the current state.
	 */
	std::string savestate();

	/**
	 * @brief Called when requested to load a state.
	 *
	 * @param data A JSON array representing the state to load.
	 */
	bool loadstate(const std::string& data);

	#ifdef __HAVE_CHAISCRIPT__
	chaiscript::ChaiScript chai;
	std::function<void()> chaiload;
	std::function<void(::Types::System::Config&)> chaiconf;
	std::function<void(float)> chaiupdate;
	std::function<void()> chaidraw;
	std::function<void()> chaireset;
	std::function<bool(std::string)> chailoadstate;
	std::function<std::string()> chaisavestate;
	std::function<void(int, const std::string&)> chaijoystickpressed;
	std::function<void(int, const std::string&)> chaijoystickreleased;
	std::function<void(int, int, int)> chaimousepressed;
	std::function<void(int, int, int)> chaimousereleased;
	std::function<void(int, int)> chaimousemove;
	std::function<void(const std::string&, int)> chaikeypressed;
	std::function<void(const std::string&, int)> chaikeyreleased;
	bool hasUpdate = true;
	bool hasDraw = true;
	bool hasjoystickpressed = true;
	bool hasjoystickreleased = true;
	bool hasmousepressed = true;
	bool hasmousereleased = true;
	bool hasmousemove = true;
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

}  // namespace Modules

#endif  // SRC_MODULES_SCRIPT_H_
