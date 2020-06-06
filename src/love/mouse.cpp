#include "mouse.h"

#include <string>

#include "libretro.h"
#include "Types/Graphics/Point.h"
#include "../ChaiLove.h"
#include "../libretro-bridge.h"

using love::Types::Graphics::Point;
using ::ChaiLove;

namespace love {

bool mouse::load() {
	return true;
}

int mouse::getX() {
	return m_x;
}

int mouse::getY() {
	return m_y;
}

bool mouse::isDown(int button) {
	return m_buttonState[button] != 0;
}
bool mouse::isDown(const std::string& button) {
	return isDown(getButtonKey(button));
}

int mouse::getButtonKey(const std::string& button) {
	if (button == "left" || button == "l") {
		return RETRO_DEVICE_ID_MOUSE_LEFT;
	} else if (button == "right" || button == "r") {
		return RETRO_DEVICE_ID_MOUSE_RIGHT;
	} else if (button == "middle" || button == "m") {
		return RETRO_DEVICE_ID_MOUSE_MIDDLE;
	} else if (button == "wheelup" || button == "wu") {
		return RETRO_DEVICE_ID_MOUSE_WHEELUP;
	} else if (button == "wheeldown" || button == "wd") {
		return RETRO_DEVICE_ID_MOUSE_WHEELDOWN;
	} else if (button == "hwu") {
		return RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP;
	} else if (button == "hwd") {
		return RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN;
	} else if (button == "x1") {
		return RETRO_DEVICE_ID_MOUSE_BUTTON_4;
	} else if (button == "x2") {
		return RETRO_DEVICE_ID_MOUSE_BUTTON_5;
	}
	return -1;
}

std::string mouse::getButtonName(int button) {
	switch (button) {
		case RETRO_DEVICE_ID_MOUSE_LEFT:
			return "l";
		case RETRO_DEVICE_ID_MOUSE_RIGHT:
			return "r";
		case RETRO_DEVICE_ID_MOUSE_MIDDLE:
			return "m";
		case RETRO_DEVICE_ID_MOUSE_WHEELUP:
			return "wd";
		case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
			return "wu";
		case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
			return "hwu";
		case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
			return "hwd";
		case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
			return "x1";
		case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
			return "x2";
	}
	return "unknown";
}

void mouse::update() {
	int16_t state, dx, dy;

	// Update the x/y coordinates.
	dx = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
	dy = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
	if (dx != 0 || dy != 0) {
		m_x = m_x + dx;
		m_y = m_y + dy;
		mousemoved(m_x, m_y, dx, dy);
	}

	// Update all buttons.
	for (int i = RETRO_DEVICE_ID_MOUSE_LEFT; i <= RETRO_DEVICE_ID_MOUSE_BUTTON_5; i++) {
		state = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, i);

		if (state != m_buttonState[i]) {
			m_buttonState[i] = state;
			if (m_buttonState[i] == 0) {
				mousereleased(m_x, m_y, getButtonName(i));
			} else {
				mousepressed(m_x, m_y, getButtonName(i));
			}
		}
	}
}

void mouse::mousemoved(int x, int y, int dx, int dy) {
	ChaiLove::getInstance()->script->mousemoved(x, y, dx, dy);
}

void mouse::mousepressed(int x, int y, const std::string& button) {
	ChaiLove::getInstance()->script->mousepressed(x, y, button);
}

void mouse::mousereleased(int x, int y, const std::string& button) {
	ChaiLove::getInstance()->script->mousereleased(x, y, button);
}

Point mouse::getPosition() {
	return Point(m_x, m_y);
}

}  // namespace love
