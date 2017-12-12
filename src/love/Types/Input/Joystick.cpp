#include "Joystick.h"
#include "SDL.h"
#include "../../../ChaiLove.h"
#include <string>

namespace love {
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

Joystick::Joystick() {
	name = "RetroPad";
	index = 0;
}

Joystick::Joystick(int i) {
	index = i;
	name = "RetroPad";
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
}  // namespace love
