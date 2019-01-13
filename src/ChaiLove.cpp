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
	std::cout << "[ChaiLove] Attempting to destroy ChaiLove" << std::endl;
	if (hasInstance()) {
		std::cout << "[ChaiLove] Destroying ChaiLove" << std::endl;
		m_instance->quit();
		delete m_instance;
		m_instance = NULL;
	}
	std::cout << "[ChaiLove] Destroyed ChaiLove" << std::endl;
}

ChaiLove* ChaiLove::getInstance() {
	if (!hasInstance()) {
		std::cout << "[ChaiLove] Initializing ChaiLove" << std::endl;
		m_instance = new ChaiLove;
	}
	return m_instance;
}

bool ChaiLove::hasInstance() {
	return m_instance != NULL;
}

ChaiLove::~ChaiLove() {
	quit();
}

void ChaiLove::quit(void) {
	// Enforce the should close flag.
	event.m_shouldclose = true;

	// Disengage the scripting language.
	if (script) {
		script->exit();
		delete script;
		script = NULL;
	}

	// Unload all the other sub-systems.
	joystick.unload();
	font.unload();
	image.unload();
	sound.unload();
	filesystem.unload();
	window.unload();
}

bool ChaiLove::load(const std::string& file, const void* data) {
	// Display a welcome message from ChaiLove.
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
	std::string version = CHAILOVE_VERSION_STRING GIT_VERSION;
	std::cout << "[ChaiLove] ChaiLove " << version.c_str() << std::endl;

	// Iniitalize some of the initial subsystems.
	sound.load();

	// Initalize the file system.
	bool loaded = filesystem.init(file, data);
	if (!loaded) {
		std::cout << "[ChaiLove] [filesystem] Error loading " << file << std::endl;
		return false;
	}

	filesystem.mountlibretro();

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

void ChaiLove::update() {
	// Update and poll all the events.
	event.update();

	// Update the input systems.
	mouse.update();
	joystick.update();
	keyboard.update();

	// Step forward the timer, and update the game.
	if (script != NULL) {
		script->update(timer.getDelta());
	}
}

/**
 * Reset the current game.
 */
void ChaiLove::reset() {
	// Tell the script that we are to reset the game.
	std::cout << "[ChaiLove] Reset" << std::endl;
	if (script != NULL) {
		script->reset();
	}
}

/**
 * Render the ChaiLove.
 */
void ChaiLove::draw() {
	if (event.m_shouldclose) {
		return;
	}

	// Clear the screen.
	graphics.clear();

	// Render the game.
	if (script != NULL) {
		script->draw();
	}

	// Render the in-game console.
	console.draw();

	// Flip the buffer.
	if (SDL_Flip(screen) == -1) {
		std::string out("[ChaiLove] Failed to swap the buffers: ");
		std::cout << out << SDL_GetError() << std::endl;
	}
}

/**
 * Tell the script to return a string representing the game data.
 */
std::string ChaiLove::savestate() {
	if (script != NULL) {
		return script->savestate();
	}
	return "";
}

/**
 * Ask the script to load the given string.
 */
bool ChaiLove::loadstate(const std::string& data) {
	if (script != NULL) {
		return script->loadstate(data);
	}
	return false;
}

/**
 * Invoke the script cheatreset hook.
 */
void ChaiLove::cheatreset() {
	if (script != NULL) {
		script->cheatreset();
	}
}

/**
 * Invoke the script cheatset hook.
 */
void ChaiLove::cheatset(int index, bool enabled, const std::string& code) {
	if (script != NULL) {
		script->cheatset(index, enabled, code);
	}
}
