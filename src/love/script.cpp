#include "script.h"
#include "../ChaiLove.h"
#include <filesystem/path.h>

#ifdef __HAVE_CHAISCRIPT__
#include "chaiscript/extras/math.hpp"
using namespace chaiscript;
#endif

using ::ChaiLove;
using love::Types::Graphics::Point;
using love::Types::Graphics::Image;
using love::Types::Graphics::Font;
using love::Types::Graphics::Point;
using love::Types::Graphics::Color;
using love::Types::System::Config;
using love::Types::Input::Joystick;
using love::Types::System::windowConfig;
using love::Types::System::moduleConfig;
using love::Types::Audio::SoundData;
using love::graphics;

namespace love {

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
			std::cout << "[ChaiLove] [script] Module " << moduleName << " not found." << std::endl;
			return false;
		}
	}

	// Load the contents of the file.
	std::string contents = app->filesystem.read(filename);

	// Make sure it was not empty.
	if (contents.empty()) {
		std::cout << "[ChaiLove] [script] Module " << moduleName << " was loaded, but empty." << std::endl;
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
	chai.add(bootstrap::standard_library::vector_type<std::vector<int>>("VectorInt"));
	chai.add(bootstrap::standard_library::vector_type<std::vector<std::string>>("StringVector"));
	chai.add(bootstrap::standard_library::map_type<std::map<std::string, bool>>("StringBoolMap"));

	// Add the "love" namespace.
	chai.register_namespace([](chaiscript::Namespace& love) {
		ChaiLove* app = ChaiLove::getInstance();
		love["audio"] = var(std::ref(app->audio));
		love["config"] = var(std::ref(app->config));
		love["event"] = var(std::ref(app->event));
		love["filesystem"] = var(std::ref(app->filesystem));
		love["font"] = var(std::ref(app->font));
		love["graphics"] = var(std::ref(app->graphics));
		love["image"] = var(std::ref(app->image));
		love["joystick"] = var(std::ref(app->joystick));
		love["keyboard"] = var(std::ref(app->keyboard));
		love["math"] = var(std::ref(app->math));
		love["mouse"] = var(std::ref(app->mouse));
		love["sound"] = var(std::ref(app->sound));
		love["system"] = var(std::ref(app->system));
		love["timer"] = var(std::ref(app->timer));
		love["window"] = var(std::ref(app->window));
	},
	"love");

	// Quad Object.
	chai.add(user_type<Quad>(), "Quad");
	chai.add(constructor<Quad()>(), "Quad");
	chai.add(fun(&Quad::x), "x");
	chai.add(fun(&Quad::y), "y");
	chai.add(fun(&Quad::width), "width");
	chai.add(fun(&Quad::height), "height");
	chai.add(fun(&Quad::sw), "sw");
	chai.add(fun(&Quad::sh), "sh");

	// Point Object.
	chai.add(user_type<Point>(), "Point");
	chai.add(fun(&Point::x), "x");
	chai.add(fun(&Point::y), "y");
	chai.add(constructor<Point()>(), "Point");
	chai.add(constructor<Point(float)>(), "Point");
	chai.add(constructor<Point(float, float)>(), "Point");

	// Color Object.
	chai.add(user_type<Color>(), "Color");
	chai.add(fun(&Color::r), "r");
	chai.add(fun(&Color::g), "g");
	chai.add(fun(&Color::b), "b");
	chai.add(fun(&Color::a), "a");
	chai.add(constructor<Color()>(), "Color");
	chai.add(constructor<Color(int, int, int)>(), "Color");
	chai.add(constructor<Color(int, int, int, int)>(), "Color");

	// Image Object.
	chai.add(user_type<Image>(), "Image");
	chai.add(fun(&Image::getWidth), "getWidth");
	chai.add(fun(&Image::getHeight), "getHeight");

	// SoundData Object.
	chai.add(user_type<SoundData>(), "SoundData");
	chai.add(fun(&SoundData::isLooping), "isLooping");
	chai.add(fun(&SoundData::isPlaying), "isPlaying");
	chai.add(fun(&SoundData::setLooping), "setLooping");
	chai.add(fun(&SoundData::stop), "stop");
	chai.add(fun(&SoundData::play), "play");
	chai.add(fun(&SoundData::resume), "resume");
	chai.add(fun(&SoundData::pause), "pause");
	chai.add(fun(&SoundData::setVolume), "setVolume");
	chai.add(fun(&SoundData::getVolume), "getVolume");

	// Font.
	chai.add(user_type<Font>(), "Font");
	chai.add(fun(&Font::loaded), "loaded");
	chai.add(fun<int, Font>(&Font::getHeight), "getHeight");
	chai.add(fun<int, Font, const std::string&>(&Font::getHeight), "getHeight");
	chai.add(fun<int, Font, const std::string&>(&Font::getWidth), "getWidth");

	// Config
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

	// Joystick
	chai.add(user_type<Joystick>(), "Joystick");
	chai.add(fun<bool, Joystick, const std::string&>(&Joystick::isDown), "isDown");
	chai.add(fun<bool, Joystick, int>(&Joystick::isDown), "isDown");
	chai.add(fun(&Joystick::getName), "getName");
	chai.add(fun(&Joystick::isOpen), "isOpen");

	// Graphics
	chai.add(fun(&graphics::rectangle), "rectangle");
	chai.add(fun(&graphics::newImage), "newImage");
	chai.add(fun(&graphics::print), "print");
	chai.add(fun<love::graphics&, graphics, int, int>(&graphics::point), "point");
	chai.add(fun<love::graphics&, graphics, Point*>(&graphics::point), "point");
	// chai.add(bootstrap::standard_library::vector_type<std::vector<Point*>>("VectorPointPointer"));
	// chai.add(bootstrap::standard_library::vector_type<std::vector<Point>>("VectorPoint"));
	// chai.add(fun<void, graphics, std::vector<Point*>>(&graphics::points), "points");
	// chai.add(fun<void, graphics, std::vector<Point>>(&graphics::points), "points");
	chai.add(fun(&graphics::arc), "arc");
	chai.add(fun(&graphics::ellipse), "ellipse");
	chai.add(fun(&graphics::getWidth), "getWidth");
	chai.add(fun(&graphics::getHeight), "getHeight");
	chai.add(fun(&graphics::circle), "circle");
	chai.add(fun(&graphics::line), "line");
	chai.add(fun(&graphics::newQuad), "newQuad");
	chai.add(fun(&graphics::setDefaultFilter), "setDefaultFilter");
	chai.add(fun(&graphics::getDefaultFilter), "getDefaultFilter");
	chai.add(fun<Font*, graphics, const std::string&, int>(&graphics::newFont), "newFont");
	chai.add(fun<Font*, graphics, const std::string&>(&graphics::newFont), "newFont");
	chai.add(fun<Font*, graphics, const std::string&, int, int, const std::string&>(&graphics::newFont), "newFont");
	chai.add(fun<Font*, graphics>(&graphics::newFont), "newFont");
	chai.add(fun<love::graphics&, graphics, Font*>(&graphics::setFont), "setFont");
	chai.add(fun<love::graphics&, graphics>(&graphics::setFont), "setFont");
	chai.add(fun<Font*, graphics>(&graphics::getFont), "getFont");
	chai.add(fun<love::graphics&, graphics, int, int, int, int>(&graphics::setColor), "setColor");
	chai.add(fun<love::graphics&, graphics, int, int, int>(&graphics::setColor), "setColor");
	chai.add(fun<love::graphics&, graphics, int, int, int, int>(&graphics::setBackgroundColor), "setBackgroundColor");
	chai.add(fun<love::graphics&, graphics, int, int, int>(&graphics::setBackgroundColor), "setBackgroundColor");

	chai.add(fun<love::graphics&, graphics, Image*, int, int>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, Image*, int, int, float, float, float, float, float>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, Image*, int, int, float, float, float, float>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, Image*, int, int, float, float, float>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, Image*, int, int, float, float>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, Image*, int, int, float>(&graphics::draw), "draw");

	chai.add(fun<love::graphics&, graphics, Image*, Quad, int, int>(&graphics::draw), "draw");
	chai.add(fun<love::graphics&, graphics, int, int, int, int>(&graphics::clear), "clear");
	chai.add(fun<love::graphics&, graphics, int, int, int>(&graphics::clear), "clear");
	chai.add(fun<love::graphics&, graphics>(&graphics::clear), "clear");

	// Font
	chai.add(fun(&font::isOpen), "isOpen");

	// Keyboard
	chai.add(fun<bool, keyboard, const std::string&>(&keyboard::isDown), "isDown");
	chai.add(fun(&keyboard::setKeyRepeat), "setKeyRepeat");
	chai.add(fun(&keyboard::getKeyFromScancode), "getKeyFromScancode");
	chai.add(fun(&keyboard::getScancodeFromKey), "getScancodeFromKey");

	// Event
	chai.add(fun(&event::quit), "quit");

	// Image
	chai.add(fun(&image::newImageData), "newImageData");

	// Filesystem
	chai.add(fun(&filesystem::unmount), "unmount");
	chai.add(fun(&filesystem::read), "read");
	chai.add(fun(&filesystem::isDirectory), "isDirectory");
	chai.add(fun(&filesystem::isFile), "isFile");
	chai.add(fun(&filesystem::exists), "exists");
	chai.add(fun(&filesystem::getDirectoryItems), "getDirectoryItems");
	chai.add(fun(&filesystem::mount), "mount");
	chai.add(fun<int, filesystem, const std::string&>(&filesystem::getSize), "getSize");
	chai.add(fun<std::vector<std::string>, filesystem, const std::string&>(&filesystem::lines), "lines");
	chai.add(fun<std::vector<std::string>, filesystem, const std::string&, const std::string&>(&filesystem::lines), "lines");
	chai.add(fun(&filesystem::load), "load");

	// System
	chai.add(fun(&system::getOS), "getOS");
	chai.add(fun(&system::getVersion), "getVersion");
	chai.add(fun(&system::getVersionString), "getVersionString");

	// Mouse
	chai.add(fun(&mouse::setVisible), "setVisible");
	chai.add(fun(&mouse::isVisible), "isVisible");
	chai.add(fun(&mouse::setX), "setX");
	chai.add(fun(&mouse::setY), "setY");
	chai.add(fun(&mouse::getX), "getX");
	chai.add(fun(&mouse::getY), "getY");
	chai.add(fun(&mouse::getPosition), "getPosition");
	chai.add(fun<bool, mouse, const std::string&>(&mouse::isDown), "isDown");
	chai.add(fun<bool, mouse, int>(&mouse::isDown), "isDown");

	// Sound
	chai.add(fun<SoundData*, sound, const std::string&>(&sound::newSoundData), "newSoundData");

	// Audio
	chai.add(fun(&audio::play), "play");
	chai.add(fun<SoundData*, audio, const std::string&>(&audio::newSource), "newSource");
	chai.add(fun(&audio::getVolume), "getVolume");
	chai.add(fun(&audio::setVolume), "setVolume");

	// Window
	chai.add(fun(&window::setTitle), "setTitle");
	chai.add(fun(&window::getTitle), "getTitle");

	// Timer
	chai.add(fun(&timer::getDelta), "getDelta");
	chai.add(fun(&timer::getFPS), "getFPS");
	chai.add(fun(&timer::step), "step");

	// Joystick
	chai.add(fun(&joystick::getJoysticks), "getJoysticks");
	chai.add(fun(&joystick::getJoystickCount), "getJoystickCount");
	chai.add(fun<bool, joystick, int, const std::string&>(&joystick::isDown), "isDown");
	chai.add(fun<bool, joystick, int, int>(&joystick::isDown), "isDown");
	chai.add(fun(&joystick::operator[]), "[]");

	// Math
	auto mathlib = chaiscript::extras::math::bootstrap();
	chai.add(mathlib);
	chai.add(fun(&math::pi), "pi");
	chai.add(fun(&math::e), "e");
	chai.add(fun(&math::rad), "rad");
	chai.add(fun(&math::degrees), "degrees");
	chai.add(fun<float, math>(&math::random), "random");
	chai.add(fun<float, math, float>(&math::random), "random");
	chai.add(fun<float, math, float, float>(&math::random), "random");
	chai.add(fun<int, math, int>(&math::random), "random");
	chai.add(fun<int, math, int, int>(&math::random), "random");
	chai.add(fun<double, math, double>(&math::random), "random");
	chai.add(fun<double, math, double, double>(&math::random), "random");
	chai.add(fun<love::math&, math, int, int>(&math::setRandomSeed), "setRandomSeed");
	chai.add(fun<love::math&, math, int>(&math::setRandomSeed), "setRandomSeed");
	chai.add(fun(&math::getRandomSeed), "getRandomSeed");
	chai.add(fun<std::string, math, const std::string&>(&math::compress), "compress");
	chai.add(fun<std::string, math, const std::string&, int>(&math::compress), "compress");
	chai.add(fun(&math::decompress), "decompress");

	// Ensure the love namespace is imported and ready.
	chai.import("love");

	// Load main.chai if it's a ChaiLove file.
	::filesystem::path p(file.c_str());
	std::string extension(p.extension());
	if (extension == "chailove" || file.empty() || extension == "chaigame") {
		loadModule("main.chai");
	} else {
		// Otherwise, load the actual file.
		std::string filename(p.filename());
		loadModule(filename);
	}

	// Find the game functions.
	try {
		chaiload = chai.eval<std::function<void()> >("load");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] load() " << e.what() << std::endl;
		hasload = false;
	}
	try {
		chaireset = chai.eval<std::function<void()> >("reset");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] reset() " << e.what() << std::endl;
		hasreset = false;
	}
	try {
		chaiupdate = chai.eval<std::function<void(float)> >("update");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] update(delta) " << e.what() << std::endl;
		hasUpdate = false;
	}
	try {
		chaiconf = chai.eval<std::function<void(Config&)> >("conf");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] conf(t) " << e.what() << std::endl;
		hasconf = false;
	}
	try {
		chaidraw = chai.eval<std::function<void()> >("draw");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] draw() " << e.what() << std::endl;
		hasDraw = false;
	}
	try {
		chaijoystickpressed = chai.eval<std::function<void(int, const std::string&)> >("joystickpressed");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] joystickpressed() " << e.what() << std::endl;
		hasjoystickpressed = false;
	}
	try {
		chaijoystickreleased = chai.eval<std::function<void(int, const std::string&)> >("joystickreleased");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] joystickreleased() " << e.what() << std::endl;
		hasjoystickreleased = false;
	}
	try {
		chaimousepressed = chai.eval<std::function<void(int, int, int)> >("mousepressed");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] mousepressed() " << e.what() << std::endl;
		hasmousepressed = false;
	}
	try {
		chaimousereleased = chai.eval<std::function<void(int, int, int)> >("mousereleased");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] mousereleased() " << e.what() << std::endl;
		hasmousereleased = false;
	}
	try {
		chaimousemoved = chai.eval<std::function<void(int, int)> >("mousemoved");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] mousemoved() " << e.what() << std::endl;
		hasmousemoved = false;
	}
	try {
		chaikeypressed = chai.eval<std::function<void(const std::string&, int)> >("keypressed");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] keypressed() " << e.what() << std::endl;
		haskeypressed = false;
	}
	try {
		chaikeyreleased = chai.eval<std::function<void(const std::string&, int)> >("keyreleased");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] keyreleased() " << e.what() << std::endl;
		haskeyreleased = false;
	}
	try {
		chailoadstate = chai.eval<std::function<bool(std::string)> >("loadstate");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] loadstate() " << e.what() << std::endl;
		hasloadstate = false;
	}
	try {
		chaisavestate = chai.eval<std::function<std::string()> >("savestate");
	}
	catch (const std::exception& e) {
		std::cout << "[ChaiLove] [script] savestate() " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to invoke conf(t): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call load(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call reset(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call update(delta): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call draw(): " << e.what() << std::endl;
			hasDraw = false;
		}
	} else {
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
			std::cout << "[ChaiLove] [script] Failed to call joystickpressed(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call joystickreleased(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call mousepressed(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call mousereleased(): " << e.what() << std::endl;
			hasmousereleased = false;
		}
	}
	#endif
}

void script::mousemoved(int x, int y) {
	#ifdef __HAVE_CHAISCRIPT__
	if (hasmousemoved) {
		try {
			chaimousemoved(x, y);
		}
		catch (const std::exception& e) {
			std::cout << "[ChaiLove] [script] Failed to call mousemoved(): " << e.what() << std::endl;
			hasmousemoved = false;
		}
	}
	#endif
}

void script::keypressed(const std::string& key, int scancode) {
	#ifdef __HAVE_CHAISCRIPT__
	if (haskeypressed) {
		try {
			chaikeypressed(key, scancode);
		}
		catch (const std::exception& e) {
			std::cout << "[ChaiLove] [script] Failed to call keypressed(): " << e.what() << std::endl;
			haskeypressed = false;
		}
	}
	#endif
}

void script::keyreleased(const std::string& key, int scancode) {
	#ifdef __HAVE_CHAISCRIPT__
	if (haskeyreleased) {
		try {
			chaikeyreleased(key, scancode);
		}
		catch (const std::exception& e) {
			std::cout << "[ChaiLove] [script] Failed to call keyreleased(): " << e.what() << std::endl;
			haskeyreleased = false;
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
			std::cout << "[ChaiLove] [script] Failed to call savestate(): " << e.what() << std::endl;
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
			std::cout << "[ChaiLove] [script] Failed to call loadstate(): " << e.what() << std::endl;
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

}  // namespace love
