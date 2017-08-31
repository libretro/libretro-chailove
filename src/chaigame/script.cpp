#include "script.h"
#include "log.h"
#include "../Game.h"
//#include "SDL.h"

#ifdef __HAVE_CHAISCRIPT__
#include "chaiscript/extras/math.hpp"
using namespace chaiscript;
#endif

namespace chaigame {
	bool script::loadModule(const std::string& moduleName) {
		#ifdef __HAVE_CHAISCRIPT__
		Game* app = Game::getInstance();
		std::string contents = app->filesystem.read(moduleName);
		if (!contents.empty()) {
			// TODO: Are tabs problematic?
			contents = replaceString(contents, "\t", "  ");
			chai.eval(contents, Exception_Handler(), moduleName);
			return true;
		}
		else {
			log()->error("Module {} was empty.", moduleName);
		}
		#endif
		return false;
	}

	script::script() {
		#ifdef __HAVE_CHAISCRIPT__
		Game* app = Game::getInstance();

		// Add the Quad.
		chai.add(user_type<Quad>(), "Quad");
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

		// Add ImageData.
		chai.add(user_type<ImageData>(), "ImageData");
		chai.add(fun(&ImageData::getWidth), "getWidth");
		chai.add(fun(&ImageData::getHeight), "getHeight");

		// Add Font.
		chai.add(user_type<Font>(), "Font");
		chai.add(fun(&Font::loaded), "loaded");
		chai.add(fun(&Font::getHeight), "getHeight");
		chai.add(fun(&Font::getWidth), "getWidth");

		// Add the Config.
		chai.add(user_type<windowConfig>(), "windowConfig");
		chai.add(fun(&windowConfig::width), "width");
		chai.add(fun(&windowConfig::height), "height");
		chai.add(fun(&windowConfig::bbp), "bbp");
		chai.add(fun(&windowConfig::title), "title");
		chai.add(user_type<moduleConfig>(), "moduleConfig");
		chai.add(fun(&moduleConfig::sound), "sound");
		chai.add(user_type<Config>(), "Config");
		chai.add(fun(&Config::window), "window");
		chai.add(fun(&Config::modules), "modules");

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
		chai.add(fun(&graphics::point), "point");
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
		chai.add(fun(&filesystem::exists), "exists");
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
		chai.add(fun(&mouse::isDown), "isDown");
		chai.add_global(var(std::ref(app->mouse)), "mouse");

		// Register the Sound module.
		chai.add(fun<SoundData*, sound, const std::string&, const std::string&>(&sound::newSoundData), "newSoundData");
		chai.add(fun<SoundData*, sound, const std::string&>(&sound::newSoundData), "newSoundData");
		chai.add_global(var(std::ref(app->sound)), "sound");

		// Register the Audio module.
		chai.add(fun(&audio::play), "play");
		chai.add(fun<SoundData*, audio, const std::string&, const std::string&>(&audio::newSource), "newSource");
		chai.add(fun<SoundData*, audio, const std::string&>(&audio::newSource), "newSource");
		chai.add_global(var(std::ref(app->audio)), "audio");

		// Register the Window module.
		chai.add(fun(&window::setTitle), "setTitle");
		chai.add(fun(&window::getTitle), "getTitle");
		chai.add_global(var(std::ref(app->window)), "window");

		// Register the Timer module.
		chai.add(fun(&timer::getDelta), "getDelta");
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
		chai.add_global(var(std::ref(app->math)), "math");

		// Load main.chai.
		loadModule("main.chai");

		// Find the game functions.
		try {
			chaiload = chai.eval<std::function<void ()> >("load");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping load() - {}", e.what());
		}
		try {
			chaiupdate = chai.eval<std::function<void (float)> >("update");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping update(delta) - {}", e.what());
		}
		try {
			chaiconf = chai.eval<std::function<void (Config&)> >("conf");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping conf(t) - {}", e.what());
		}
		try {
			chaidraw = chai.eval<std::function<void ()> >("draw");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping draw() - {}", e.what());
		}
		try {
			chaijoystickpressed = chai.eval<std::function<void (int, int)> >("joystickpressed");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping joystickpressed() - {}", e.what());
		}
		try {
			chaijoystickreleased = chai.eval<std::function<void (int, int)> >("joystickreleased");
		}
		catch (std::exception& e) {
			log()->warn("[script] Skipping joystickreleased() - {}", e.what());
		}
		#endif
	}

	void script::conf(Config& t) {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			chaiconf(t);
		}
		catch (chaiscript::exception::dispatch_error& e) {
			log()->warn("[script] Failed to invoke call to conf(t): {}", e.what());
		}
		catch (const chaiscript::exception::eval_error &e) {
			log()->warn("[script] Failed to invoke call to conf(): {}", e.what());
		}
		catch (std::exception& e) {
			log()->warn("[script] Failed to invoke conf(t): {}", e.what());
		}
		catch (...) {
			log()->warn("[script] Failed to invoke conf(t)");
		}
		#endif
	}

	void script::load() {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			chaiload();
		}
		catch (chaiscript::exception::dispatch_error& e) {
			log()->warn("[script] Failed to invoke call to load(): {}", e.what());
		}
		catch (const chaiscript::exception::eval_error &e) {
			log()->warn("[script] Failed calling load(): {}", e.what());
		}
		catch (...) {
			log()->warn("[script] Failed to invoke load()");
		}
		#endif
	}

	void script::update(float delta) {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			if (hasUpdate) {
				chaiupdate(delta);
			}
		}
		catch (chaiscript::exception::dispatch_error& e) {
			hasUpdate = false;
			log()->error("[script] Failed to invoke call to update(): {}", e.what());
		}
		catch (const chaiscript::exception::eval_error &e) {
			hasUpdate = false;
			log()->error("[script] Failed to invoke call to update(): {}", e.what());
		}
		catch (std::exception& e) {
			hasUpdate = false;
			log()->error("[script] Failed to call update(t): {}", e.what());
		}
		catch (...) {
			hasUpdate = false;
			log()->error("[script] Unhandled exception in update()");
		}
		#endif
	}

	void script::draw() {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			if (hasDraw) {
				chaidraw();
			}
		}
		catch (chaiscript::exception::dispatch_error& e) {
			hasDraw = false;
			log()->warn("[script] Failed to invoke call to draw(): {}", e.what());
		}
		catch (const chaiscript::exception::eval_error &e) {
			hasDraw = false;
			log()->warn("[script] Failed to invoke call to update(): {}", e.what());
		}
		catch (std::exception& e) {
			log()->warn("[script] Failed to call update(t): {}", e.what());
		}
		catch (...) {
			log()->warn("[script] Unhandled exception in draw()");
		}
		#endif
	}

	void script::joystickpressed(int joystick, int button) {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			if (hasjoystickpressed) {
				chaijoystickpressed(joystick, button);
			}
		}
		catch (...) {
			hasjoystickpressed = false;
		}
		#endif
	}

	void script::joystickreleased(int joystick, int button) {
		#ifdef __HAVE_CHAISCRIPT__
		try {
			if (hasjoystickreleased) {
				chaijoystickreleased(joystick, button);
			}
		}
		catch (...) {
			hasjoystickreleased = false;
		}
		#endif
	}

	std::string script::replaceString(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			 subject.replace(pos, search.length(), replace);
			 pos += replace.length();
		}
		return subject;
	}
}
