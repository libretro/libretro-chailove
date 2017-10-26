#include <string>
#include "SDL.h"

#include "libretro.h"
#include "ChaiGame.h"
#include "chaigame/log.h"

ChaiGame* ChaiGame::m_instance = NULL;
retro_input_state_t ChaiGame::input_state_cb = NULL;
retro_input_poll_t ChaiGame::input_poll_cb = NULL;

void ChaiGame::destroy() {
	m_instance = NULL;
}

ChaiGame* ChaiGame::getInstance() {
	if (!m_instance) {
		m_instance = new ChaiGame;
	}
	return m_instance;
}

void ChaiGame::quit(void) {
	// Quit all the subsystems.
	joystick.unload();
	font.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
	chaigame::log()->info("Finish");
}

bool ChaiGame::load(const std::string& file) {
	// Display a welcome message from ChaiGame.
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
	std::string version = CHAIGAME_VERSION_STRING GIT_VERSION;
	chaigame::log()->info("ChaiGame {0}", version);

	// Initalize all the subsystems.
	filesystem.init(file);
	script = new chaigame::script(file);
	script->conf(config);

	#ifdef __HAVE_TESTS__
	test.conf(config);
	#endif

	window.load(config);

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
	script->load();

	#ifdef __HAVE_TESTS__
	test.load();
	#endif

	return true;
}

bool ChaiGame::update() {
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
void ChaiGame::reset() {
	// Tell the script that we are to reset the game.
	chaigame::log()->info("[game] Reset");
	script->reset();
}

/**
 * Render the ChaiGame.
 */
void ChaiGame::draw() {
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
			chaigame::log()->error("Failed to swap the buffers: {}", SDL_GetError());
		}
	}
}

/**
 * Tell the script to return a string representing the game data.
 */
std::string ChaiGame::savestate() {
	return script->savestate();
}

/**
 * Ask the script to load the given string.
 */
bool ChaiGame::loadstate(const std::string& data) {
	return script->loadstate(data);
}
