#include <string>
#include <iostream>
#include "SDL.h"

#include "libretro.h"
#include "ChaiLove.h"

ChaiLove* ChaiLove::m_instance = NULL;
retro_input_state_t ChaiLove::input_state_cb = NULL;
retro_input_poll_t ChaiLove::input_poll_cb = NULL;

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
	std::cout << "[ChaiLove] Unloaded all systems" << std::endl;
}

bool ChaiLove::load(const std::string& file) {
	// Display a welcome message from ChaiLove.
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
	std::string version = CHAILOVE_VERSION_STRING GIT_VERSION;
	std::cout << "[ChaiLove] ChaiLove " << version.c_str() << std::endl;

	// Initalize the file system.
	filesystem.init(file);

	// Initialize the scripting system.
	script = new Modules::script(file);
	script->conf(config);

	// Testing.
	#ifdef __HAVE_TESTS__
	test.conf(config);
	#endif

	// Load up the window dimensions.
	window.load(config);

	// Initialize the soud, if needed.
	if (config.modules.sound) {
		sound.load();
	}

	graphics.load();
	image.load();
	keyboard.load();
	joystick.load();
	math.load();
	mouse.load();
	font.load();

	// Now that all subsystems are loaded, start the script.
	script->load();

	#ifdef __HAVE_TESTS__
	test.load();
	#endif

	return true;
}

bool ChaiLove::update() {
	if (event.quitstatus) {
		return false;
	}

	sound.update();

	// Poll all SDL events.
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				event.quit();
				return !event.quitstatus;
				break;
			case SDL_MOUSEMOTION:
				mouse.moveEvent(sdlEvent.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouse.buttonEvent(sdlEvent.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.buttonEvent(sdlEvent.button);
				break;
		}
	}

	// Update some of the sub-systems.
	joystick.update();
	keyboard.update();

	// Step forward the timer, and update the game.
	script->update(timer.getDelta());

	#ifdef __HAVE_TESTS__
	test.update(timer.getDelta());
	#endif

	return !event.quitstatus;
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
	if (!event.quitstatus) {
		// Clear the screen.
		graphics.clear();

		// Render the game.
		script->draw();

		#ifdef __HAVE_TESTS__
		test.draw();
		#endif

		// Flip the buffer.
		if (SDL_Flip(screen) == -1) {
			std::cout << "[ChaiLove] Failed to swap the buffers: " << SDL_GetError() << std::endl;
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
