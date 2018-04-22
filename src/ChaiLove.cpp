#include "ChaiLove.h"
#include <libretro.h>
#include <SDL.h>
#include <iostream>
#include <string>

ChaiLove* ChaiLove::m_instance = NULL;
retro_input_state_t ChaiLove::input_state_cb = NULL;
retro_input_poll_t ChaiLove::input_poll_cb = NULL;
retro_environment_t ChaiLove::environ_cb = NULL;

void ChaiLove::destroy() {
	m_instance = NULL;
}

ChaiLove* ChaiLove::getInstance() {
	if (!m_instance) {
		m_instance = new ChaiLove;
	}
	return m_instance;
}

void ChaiLove::quit(void) {
	// Quit all the subsystems.
	joystick.unload();
	font.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
	std::cout << "[ChaiLove] Unloaded ChaiLove" << std::endl;
}

bool ChaiLove::load(const std::string& file) {
	// Display a welcome message from ChaiLove.
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
	std::string version = CHAILOVE_VERSION_STRING GIT_VERSION;
	std::cout << "[ChaiLove] ChaiLove " << version.c_str() << std::endl;

	// Initalize the file system.
	bool loaded = filesystem.init(file);
	if (!loaded) {
		std::cout << "[ChaiLove] [filesystem] Error loading " << file << std::endl;
		return false;
	}

	// Initialize the scripting system.
	script = new love::script(file);
	if (!script->mainLoaded) {
		std::cout << "[ChaiLove] [script] Error loading " << file << std::endl;
		return false;
	}
	script->conf(config);
	system.load(config);

	// Load up the window dimensions.
	window.load(config);

	// Initialize the soud, if needed.
	if (config.modules.sound) {
		sound.load();
	}

	console.load(config);
	graphics.load();
	image.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	font.load();

	// Now that all subsystems are loaded, start the script.
	script->load();

	return true;
}

std::string ChaiLove::demo() {
	// Provides a demo screen that's presented when the core is loaded without content.
	std::string output = R"DEMO(
		global x = 200.0f
		global y = 0.0f
		global defaultFont
		global text = "ChaiLove " + love.system.getVersionString() + " - No Game!"
		global speed = 20.0f

		def load() {
			defaultFont = love.graphics.getFont()
			x = love.graphics.getWidth() / 2.0f - defaultFont.getWidth(text) / 2.0f
			y = love.graphics.getHeight() / 2.0f
		}

		def conf(t) {
			t.window.width = 640
			t.window.height = 480
			t.console = true
		}

		def draw() {
			love.graphics.setBackgroundColor(122, 179, 222)

			// Draw a little circle.
			love.graphics.setColor(192, 219, 157)
			love.graphics.circle("fill", 120, 70, 50)
			love.graphics.setColor(0, 0, 0)
			love.graphics.circle("line", 120, 70, 50)

			// Draw the text.
			love.graphics.setColor(255, 255, 255)
			love.graphics.print(text, x, y)
		}

		def update(dt) {
			y = y - speed * dt
			if (y + defaultFont.getHeight(text) < 0.0f) {
				y = love.graphics.getHeight()
			}
		}
	)DEMO";
	return output;
}

bool ChaiLove::update() {
	// Poll all the inputs.
	ChaiLove::input_poll_cb();

	// Poll all SDL events.
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				event.quit();
				return !event.m_shouldclose;
				break;
		}
	}

	// Update the input systems.
	mouse.update();
	joystick.update();
	keyboard.update();

	// Step forward the timer, and update the game.
	script->update(timer.getDelta());

	return !event.m_shouldclose;
}

/**
 * Reset the current game.
 */
void ChaiLove::reset() {
	// Tell the script that we are to reset the game.
	std::cout << "[ChaiLove] Reset" << std::endl;
	script->reset();
}

/**
 * Render the ChaiLove.
 */
void ChaiLove::draw() {
	if (!event.m_quitstatus) {
		// Clear the screen.
		graphics.clear();

		// Render the game.
		script->draw();

		// Render the in-game console.
		console.draw();

		// Flip the buffer.
		if (SDL_Flip(screen) == -1) {
			std::string out("[ChaiLove] Failed to swap the buffers: ");
			std::cout << out << SDL_GetError() << std::endl;
		}
	}
}

/**
 * Tell the script to return a string representing the game data.
 */
std::string ChaiLove::savestate() {
	return script->savestate();
}

/**
 * Ask the script to load the given string.
 */
bool ChaiLove::loadstate(const std::string& data) {
	return script->loadstate(data);
}
