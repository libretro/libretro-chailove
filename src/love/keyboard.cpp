#include "keyboard.h"

#include <string>
#include <iostream>
#include "../ChaiLove.h"
#include "SDL.h"

namespace love {

bool keyboard::isDown(int key) {
	return static_cast<bool>(keys[key]);
}

bool keyboard::isDown(const std::string& key) {
	return isDown(getScancodeFromKey(key));
}

keyboard& keyboard::setKeyRepeat(int delay, int interval) {
	/*if (SDL_EnableKeyRepeat(delay, interval) == -1) {
		std::cout << "[ChaiLove] Error setting KeyRepeat." << std::endl;
	}*/

	return *this;
}

bool keyboard::load() {
	//SDL_EnableUNICODE(1);
/*
	// Construct the keycode map.
	for (int i = 0; i < SDLK_LAST; i++) {
		std::string name(SDL_GetKeyName((SDL_Keycode)i));
		if (!name.empty()) {
			keyCodes[name] = i;
		}
	}

	// Set the initial set of keys.
	keys = SDL_GetKeyboardState(NULL);
*/
	return true;
}

int keyboard::getScancodeFromKey(const std::string& name) {
	return 0;
	//return keyCodes[name];
}

std::string keyboard::getKeyFromScancode(int scancode) {
	return "NULL";
	//std::string name(SDL_GetKeyName((SDL_Keycode)scancode));
	//return name;
}

bool keyboard::update() {
	//keys = SDL_GetKeyboardState(NULL);
	return true;
}

void keyboard::eventKeyPressed(SDL_Keycode key) {
	std::string name = getKeyFromScancode(key);
	ChaiLove* app = ChaiLove::getInstance();
	app->script->keypressed(name, static_cast<int>(key));
}

void keyboard::eventKeyReleased(SDL_Keycode key) {
	std::string name = getKeyFromScancode(key);
	ChaiLove* app = ChaiLove::getInstance();
	app->script->keyreleased(name, static_cast<int>(key));
}

}  // namespace love
