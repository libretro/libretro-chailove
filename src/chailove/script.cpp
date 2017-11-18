#include "script.h"
#include "../ChaiLove.h"
#include <filesystem/path.h>

#ifdef __HAVE_CHAISCRIPT__
#include "chaiscript/extras/math.hpp"
using namespace chaiscript;
#endif

namespace chailove {
	bool script::loadModule(const std::string& moduleName) {
		#ifdef __HAVE_CHAISCRIPT__
		ChaiLove* app = ChaiLove::getInstance();

		// Store a filename for the module.
		std::string filename = moduleName;

		// Make sure it exists.
		if (!app->filesystem.exists(filename)) {
			// See if we are to append .chai.
			filename = filename + ".chai";
			if (!app->filesystem.exists(filename)) {
				std::cout << "[script] Module " << moduleName << " not found." << std::endl;
				return false;
			}
		}

		// Load the contents of the file.
		std::string contents = app->filesystem.read(filename);

		// Make sure it was not empty.
		if (contents.empty()) {
			std::cout << "[script] Module " << moduleName << " was loaded, but empty." << std::endl;
			return false;
		}

		// Replace possible problematic tabs, and evaluate the script.
		contents = replaceString(contents, "\t", "  ");
		chai.eval(contents, Exception_Handler(), filename);
		return true;

		#endif
		return false;
	}

	script::script(const std::string& file) {
		#ifdef __HAVE_CHAISCRIPT__
		ChaiLove* app = ChaiLove::getInstance();

		// ChaiScript Standard Library Additions
		// This adds some basic type definitions to ChaiScript.
		chai.add(bootstrap::standard_library::vector_type<std::vector<std::string>>("StringVector"));
		chai.add(bootstrap::standard_library::map_type<std::map<std::string, bool>>("StringBoolMap"));

		// Add the Quad.
		chai.add(user_type<Quad>(), "Quad");
		chai.add(constructor<Quad()>(), "Quad");
		chai.add(fun(&Quad::x), "x");
		chai.add(fun(&Quad::y), "y");
		chai.add(fun(&Quad::width), "width");
		chai.add(fun(&Quad::height), "height");
		chai.add(fun(&Quad::sw), "sw");
		chai.add(fun(&Quad::sh), "sh");

		// Add the Point.
		chai.add(user_type<Point>(), "Point");
		chai.add(fun(&Point::x), "x");
		chai.add(fun(&Point::y), "y");
		chai.add(constructor<Point()>(), "Point");
		chai.add(constructor<Point(float)>(), "Point");
		chai.add(constructor<Point(float, float)>(), "Point");

		// Add ImageData.
		chai.add(user_type<ImageData>(), "ImageData");
		chai.add(fun(&ImageData::getWidth), "getWidth");
		chai.add(fun(&ImageData::getHeight), "getHeight");

		// Add SoundData.
		chai.add(user_type<SoundData>(), "SoundData");
		chai.add(fun(&SoundData::isLooping), "isLooping");
		chai.add(fun(&SoundData::setLooping), "setLooping");
		chai.add(fun(&SoundData::stop), "stop");
		chai.add(fun(&SoundData::play), "play");

		// Add Font.
		chai.add(user_type<Font>(), "Font");
		chai.add(fun(&Font::loaded), "loaded");
		chai.add(fun<int, Font>(&Font::getHeight), "getHeight");
		chai.add(fun<int, Font, const std::string&>(&Font::getHeight), "getHeight");
		chai.add(fun<int, Font, const std::string&>(&Font::getWidth), "getWidth");

		// Add the Config.
		chai.add(user_type<windowConfig>(), "windowConfig");
		chai.add(fun(&windowConfig::width), "width");
		chai.add(fun(&windowConfig::height), "height");
		chai.add(fun(&windowConfig::bbp), "bbp");
		chai.add(fun(&windowConfig::title), "title");
		chai.add(fun(&windowConfig::asyncblit), "asyncblit");
		chai.add(fun(&windowConfig::hwsurface), "hwsurface");
		chai.add(fun(&windowConfig::doublebuffering), "doublebuffering");
		chai.add(user_type<moduleConfig>(), "moduleConfig");
		chai.add(fun(&moduleConfig::sound), "sound");
		chai.add(user_type<Config>(), "Config");
		chai.add(fun(&Config::identity), "identity");
		chai.add(fun(&Config::version), "version");
		chai.add(fun(&Config::window), "window");
		chai.add(fun(&Config::modules), "modules");
		chai.add(fun(&Config::options), "options");
		chai.add_global(var(std::ref(app->config)), "config");

		// Add Joystick.
		chai.add(user_type<Joystick>(), "Joystick");
		chai.add(fun<bool, Joystick, const std::string&>(&Joystick::isDown), "isDown");
		chai.add(fun<bool, Joystick, int>(&Joystick::isDown), "isDown");
		chai.add(fun(&Joystick::getName), "getName");
		chai.add(fun(&Joystick::isOpen), "isOpen");

		// Register the Graphics module.
		chai.add(fun(&graphics::rectangle), "rectangle");
		chai.add(fun(&graphics::newImage), "newImage");
		chai.add(fun(&graphics::print), "print");
		chai.add(fun<void, graphics, int, int>(&graphics::point), "point");
		chai.add(fun<void, graphics, Point*>(&graphics::point), "point");
		//chai.add(bootstrap::standard_library::vector_type<std::vector<Point*>>("VectorPointPointer"));
		//chai.add(bootstrap::standard_library::vector_type<std::vector<Point>>("VectorPoint"));
		//chai.add(fun<void, graphics, std::vector<Point*>>(&graphics::points), "points");
		//chai.add(fun<void, graphics, std::vector<Point>>(&graphics::points), "points");
		chai.add(fun(&graphics::arc), "arc");
		chai.add(fun(&graphics::ellipse), "ellipse");
		chai.add(fun(&graphics::getWidth), "getWidth");
		chai.add(fun(&graphics::getHeight), "getHeight");
		chai.add(fun(&graphics::circle), "circle");
		chai.add(fun(&graphics::line), "line");
		chai.add(fun(&graphics::newQuad), "newQuad");
		chai.add(fun<Font*, graphics, const std::string&, int>(&graphics::newFont), "newFont");
		chai.add(fun<Font*, graphics, const std::string&>(&graphics::newFont), "newFont");
		chai.add(fun<Font*, graphics, const std::string&, int, int, const std::string&>(&graphics::newFont), "newFont");
		chai.add(fun<Font*, graphics>(&graphics::newFont), "newFont");
		chai.add(fun<void, graphics, Font*>(&graphics::setFont), "setFont");
		chai.add(fun<void, graphics>(&graphics::setFont), "setFont");
		chai.add(fun<void, graphics, int, int, int, int>(&graphics::setColor), "setColor");
		chai.add(fun<void, graphics, int, int, int>(&graphics::setColor), "setColor");
		chai.add(fun<void, graphics, int, int, int, int>(&graphics::setBackgroundColor), "setBackgroundColor");
		chai.add(fun<void, graphics, int, int, int>(&graphics::setBackgroundColor), "setBackgroundColor");
		chai.add(fun<void, graphics, ImageData*, int, int>(&graphics::draw), "draw");
		chai.add(fun<void, graphics, ImageData*, Quad, int, int>(&graphics::draw), "draw");
		chai.add(fun<void, graphics, int, int, int, int>(&graphics::clear), "clear");
		chai.add(fun<void, graphics, int, int, int>(&graphics::clear), "clear");
		chai.add(fun<void, graphics>(&graphics::clear), "clear");
		chai.add_global(var(std::ref(app->graphics)), "graphics");

		// Register the Font module.
		chai.add(fun(&font::isOpen), "isOpen");
		chai.add_global(var(std::ref(app->font)), "font");

		// Register the Keyboard module.
		chai.add(fun<bool, keyboard, const std::string&>(&keyboard::isDown), "isDown");
		chai.add(fun(&keyboard::setKeyRepeat), "setKeyRepeat");
		chai.add_global(var(std::ref(app->keyboard)), "keyboard");

		// Register the Event module.
		chai.add(fun(&event::quit), "quit");
		chai.add_global(var(std::ref(app->event)), "event");

		// Register the Image module.
		chai.add(fun(&image::newImageData), "newImageData");
		chai.add_global(var(std::ref(app->image)), "image");

		// Register the Filesystem module.
		chai.add(fun(&filesystem::read), "read");
		chai.add(fun(&filesystem::isDirectory), "isDirectory");
		chai.add(fun(&filesystem::isFile), "isFile");
		chai.add(fun(&filesystem::exists), "exists");
		chai.add(fun(&filesystem::getDirectoryItems), "getDirectoryItems");
		chai.add(fun(&filesystem::mount), "mount");
		chai.add(fun<int, filesystem, const std::string&>(&filesystem::getSize), "getSize");
		chai.add(fun(&filesystem::load), "load");
		chai.add_global(var(std::ref(app->filesystem)), "filesystem");

		// Register the System module.
		chai.add(fun(&system::getOS), "getOS");
		chai.add_global(var(std::ref(app->system)), "system");

		// Register the Mouse module.
		chai.add(fun(&mouse::setVisible), "setVisible");
		chai.add(fun(&mouse::isVisible), "isVisible");
		chai.add(fun(&mouse::setX), "setX");
		chai.add(fun(&mouse::setY), "setY");
		chai.add(fun(&mouse::getX), "getX");
		chai.add(fun(&mouse::getY), "getY");
		chai.add(fun(&mouse::getPosition), "getPosition");
		chai.add(fun<bool, mouse, const std::string&>(&mouse::isDown), "isDown");
		chai.add(fun<bool, mouse, int>(&mouse::isDown), "isDown");
		chai.add_global(var(std::ref(app->mouse)), "mouse");

		// Register the Sound module.
		chai.add(fun<SoundData*, sound, const std::string&>(&sound::newSoundData), "newSoundData");
		chai.add_global(var(std::ref(app->sound)), "sound");

		// Register the Audio module.
		chai.add(fun(&audio::play), "play");
		chai.add(fun<SoundData*, audio, const std::string&>(&audio::newSource), "newSource");
		chai.add(fun(&audio::getVolume), "getVolume");
		chai.add(fun(&audio::setVolume), "setVolume");
		chai.add_global(var(std::ref(app->audio)), "audio");

		// Register the Window module.
		chai.add(fun(&window::setTitle), "setTitle");
		chai.add(fun(&window::getTitle), "getTitle");
		chai.add_global(var(std::ref(app->window)), "window");

		// Register the Timer module.
		chai.add(fun(&timer::getDelta), "getDelta");
		chai.add(fun(&timer::getFPS), "getFPS");
		chai.add(fun(&timer::step), "step");
		chai.add_global(var(std::ref(app->timer)), "timer");

		// Register the Joystick module.
		chai.add(fun(&joystick::getJoysticks), "getJoysticks");
		chai.add(fun(&joystick::getJoystickCount), "getJoystickCount");
		chai.add(fun<bool, joystick, int, const std::string&>(&joystick::isDown), "isDown");
		chai.add(fun<bool, joystick, int, int>(&joystick::isDown), "isDown");
		chai.add(fun(&joystick::operator[]), "[]");
		chai.add_global(var(std::ref(app->joystick)), "joystick");

		// Register the Math module.
		auto mathlib = chaiscript::extras::math::bootstrap();
		chai.add(mathlib);
		chai.add(fun(&math::pi), "pi");
		chai.add(fun(&math::e), "e");
		chai.add(fun<double, math>(&math::random), "random");
		chai.add(fun<int, math, int>(&math::random), "random");
		chai.add(fun<int, math, int, int>(&math::random), "random");
		chai.add(fun<void, math, int>(&math::setRandomSeed), "setRandomSeed");
		chai.add(fun<void, math, int, int>(&math::setRandomSeed), "setRandomSeed");
		chai.add(fun(&math::getRandomSeed), "getRandomSeed");
		chai.add_global(var(std::ref(app->math)), "math");

		// Load main.chai if it's a ChaiLove file.
		::filesystem::path p(file.c_str());
		std::string extension(p.extension());
		if (extension == "chailove" || file.empty() || extension == "chaigame") {
			loadModule("main.chai");
		}
		else {
			// Otherwise, load the actual file.
			std::string filename(p.filename());
			loadModule(filename);
		}

		// Find the game functions.
		try {
			chaiload = chai.eval<std::function<void ()> >("load");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping load() " << e.what() << std::endl;
			hasload = false;
		}
		try {
			chaireset = chai.eval<std::function<void ()> >("reset");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping reset() " << e.what() << std::endl;
			hasreset = false;
		}
		try {
			chaiupdate = chai.eval<std::function<void (float)> >("update");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping update(delta) " << e.what() << std::endl;
			hasUpdate = false;
		}
		try {
			chaiconf = chai.eval<std::function<void (Config&)> >("conf");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping conf(t) " << e.what() << std::endl;
			hasconf = false;
		}
		try {
			chaidraw = chai.eval<std::function<void ()> >("draw");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping draw() " << e.what() << std::endl;
			hasDraw = false;
		}
		try {
			chaijoystickpressed = chai.eval<std::function<void (int, const std::string&)> >("joystickpressed");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping joystickpressed() " << e.what() << std::endl;
			hasjoystickpressed = false;
		}
		try {
			chaijoystickreleased = chai.eval<std::function<void (int, const std::string&)> >("joystickreleased");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping joystickreleased() " << e.what() << std::endl;
			hasjoystickreleased = false;
		}
		try {
			chaimousepressed = chai.eval<std::function<void (int, int, int)> >("mousepressed");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping mousepressed() " << e.what() << std::endl;
			hasmousepressed = false;
		}
		try {
			chaimousereleased = chai.eval<std::function<void (int, int, int)> >("mousereleased");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping mousereleased() " << e.what() << std::endl;
			hasmousereleased = false;
		}
		try {
			chaimousemove = chai.eval<std::function<void (int, int)> >("mousemove");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping mousemove() " << e.what() << std::endl;
			hasmousemove = false;
		}
		try {
			chailoadstate = chai.eval<std::function<bool (std::string)> >("loadstate");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping loadstate() " << e.what() << std::endl;
			hasloadstate = false;
		}
		try {
			chaisavestate = chai.eval<std::function<std::string ()> >("savestate");
		}
		catch (const std::exception& e) {
			std::cout << "[script] Skipping savestate() " << e.what() << std::endl;
			hassavestate = false;
		}
		#endif
	}

	void script::conf(Config& t) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasconf) {
			try {
				chaiconf(t);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to invoke conf(t): " << e.what() << std::endl;
				hasconf = false;
			}
		}
		#endif
	}

	void script::load() {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasload) {
			try {
				chaiload();
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call load(): " << e.what() << std::endl;
				hasload = false;
			}
		}
		#endif
	}

	void script::reset() {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasreset) {
			try {
				chaireset();
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call reset(): " << e.what() << std::endl;
				hasreset = false;
			}
		}
		#endif
	}

	void script::update(float delta) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasUpdate) {
			try {
				chaiupdate(delta);
			}
			catch (const std::exception& e) {
				hasUpdate = false;
				std::cout << "[script] Failed to call update(delta): " << e.what() << std::endl;
			}
		}
		#endif
	}

	void script::draw() {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasDraw) {
			try {
				chaidraw();
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call draw(): " << e.what() << std::endl;
				hasDraw = false;
			}
		}
		else {
			ChaiLove::getInstance()->graphics.print("ChaiLove: def draw() not found.", 100, 100);
		}
		#endif
	}

	void script::joystickpressed(int joystick, const std::string& button) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasjoystickpressed) {
			try {
				chaijoystickpressed(joystick, button);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call joystickpressed(): " << e.what() << std::endl;
				hasjoystickpressed = false;
			}
		}
		#endif
	}

	void script::joystickreleased(int joystick, const std::string& button) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasjoystickreleased) {
			try {
				chaijoystickreleased(joystick, button);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call joystickreleased(): " << e.what() << std::endl;
				hasjoystickreleased = false;
			}
		}
		#endif
	}

	void script::mousepressed(int x, int y, int button) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasmousepressed) {
			try {
				chaimousepressed(x, y, button);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call mousepressed(): " << e.what() << std::endl;
				hasmousepressed = false;
			}
		}
		#endif
	}

	void script::mousereleased(int x, int y, int button) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasmousereleased) {
			try {
				chaimousereleased(x, y, button);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call mousereleased(): " << e.what() << std::endl;
				hasmousereleased = false;
			}
		}
		#endif
	}

	void script::mousemove(int x, int y) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasmousemove) {
			try {
				chaimousemove(x, y);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call mousemove(): " << e.what() << std::endl;
				hasmousemove = false;
			}
		}
		#endif
	}

	/**
	 * Call the script's savestate() function and retrieve a string.
	 */
	std::string script::savestate() {
		#ifdef __HAVE_CHAISCRIPT__
		if (hassavestate) {
			try {
				return chaisavestate();
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call savestate(): " << e.what() << std::endl;
				hassavestate = false;
			}
		}
		#endif

		// If there is no state data, return an empty string.
		return std::string("");
	}

	/**
	 * Pass the state data string over to the script, asking it to load the state.
	 */
	bool script::loadstate(const std::string& data) {
		#ifdef __HAVE_CHAISCRIPT__
		if (hasloadstate) {
			try {
				return chailoadstate(data);
			}
			catch (const std::exception& e) {
				std::cout << "[script] Failed to call loadstate(): " << e.what() << std::endl;
				hasloadstate = false;
			}
		}
		#endif

		// If there is an error in loading the state, return false.
		return false;
	}

	/**
	 * Replaces all instances of a string in a given subject string.
	 */
	std::string script::replaceString(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			 subject.replace(pos, search.length(), replace);
			 pos += replace.length();
		}
		return subject;
	}
}
