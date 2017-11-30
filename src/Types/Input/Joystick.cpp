#include "Joystick.h"
#include "SDL.h"
#include "../../ChaiLove.h"
#include <string>

namespace Types {
namespace Input {

std::string Joystick::getName() {
	return name;
}

/*
Joystick::Joystick(SDL_Joystick* joystick) {
	joy = joystick;
}
*/

/*
Joystick::Joystick(int num, SDL_Joystick* joystick) {
	index = index;
	joy = joystick;
}
*/

bool Joystick::isOpen() {
	return true;
}

bool Joystick::open(int i) {
	index = i;
	name = "RetroPad";
	return true;
}

Joystick::Joystick() {
}

bool Joystick::isDown(int button) {
	return static_cast<bool>(ChaiLove::getInstance()->joystick.joystick_cache[index][button]);
}

bool Joystick::isDown(const std::string& button) {
	int key = ChaiLove::getInstance()->joystick.getButtonKey(button);
	return isDown(key);
}

void Joystick::close() {
	// Nothing.
}

}  // namespace Input
}  // namespace Types
