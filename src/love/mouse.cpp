#include "mouse.h"

#include <string>

#include "libretro.h"
#include "Types/Graphics/Point.h"
#include "../ChaiLove.h"

#include "pntr_app.h"

using love::Types::Graphics::Point;
using ::ChaiLove;

namespace love {

bool mouse::load(pntr_app* app) {
	m_app = app;
	return true;
}

float mouse::getX() {
	return pntr_app_mouse_x(m_app);
}

float mouse::getY() {
	return pntr_app_mouse_y(m_app);
}

bool mouse::isDown(int button) {
	if (button == RETRO_DEVICE_ID_MOUSE_WHEELUP) {
		return pntr_app_mouse_wheel(m_app) < 0;
	}
	else if (button == RETRO_DEVICE_ID_MOUSE_WHEELDOWN) {
		return pntr_app_mouse_wheel(m_app) > 0;
	}
	else if (button < PNTR_APP_MOUSE_BUTTON_FIRST) {
		return false;
	}
	else if (button >= PNTR_APP_MOUSE_BUTTON_LAST) {
		return false;
	}

	return pntr_app_key_down(m_app, (pntr_app_key)button);
}
bool mouse::isDown(const std::string& button) {
	return isDown(getButtonKey(button));
}

int mouse::getButtonKey(const std::string& button) {
	if (button == "left" || button == "l") {
		return PNTR_APP_MOUSE_BUTTON_LEFT;
	} else if (button == "right" || button == "r") {
		return PNTR_APP_MOUSE_BUTTON_RIGHT;
	} else if (button == "middle" || button == "m") {
		return PNTR_APP_MOUSE_BUTTON_MIDDLE;
	} else if (button == "wheelup" || button == "wu") {
		return RETRO_DEVICE_ID_MOUSE_WHEELUP;
	} else if (button == "wheeldown" || button == "wd") {
		return RETRO_DEVICE_ID_MOUSE_WHEELDOWN;
	}

	return -1;
}

std::string mouse::getButtonName(int button) {
	switch (button) {
		case PNTR_APP_MOUSE_BUTTON_LEFT:
			return "l";
		case PNTR_APP_MOUSE_BUTTON_RIGHT:
			return "r";
		case PNTR_APP_MOUSE_BUTTON_MIDDLE:
			return "m";
		case RETRO_DEVICE_ID_MOUSE_WHEELUP:
			return "wd";
		case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
			return "wu";
	}
	return "unknown";
}

void mouse::update() {
	// int16_t state, dx, dy;

	// // Update the x/y coordinates.
	// dx = ChaiLove::input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
	// dy = ChaiLove::input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
	// if (dx != 0 || dy != 0) {
	// 	m_x = m_x + dx;
	// 	m_y = m_y + dy;
	// 	mousemoved(m_x, m_y, dx, dy);
	// }

	// // Update all buttons.
	// for (int i = RETRO_DEVICE_ID_MOUSE_LEFT; i <= RETRO_DEVICE_ID_MOUSE_BUTTON_5; i++) {
	// 	state = ChaiLove::input_state_cb(0, RETRO_DEVICE_MOUSE, 0, i);

	// 	if (state != m_buttonState[i]) {
	// 		m_buttonState[i] = state;
	// 		if (m_buttonState[i] == 0) {
	// 			mousereleased(m_x, m_y, getButtonName(i));
	// 		} else {
	// 			mousepressed(m_x, m_y, getButtonName(i));
	// 		}
	// 	}
	// }
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
	return Point(pntr_app_mouse_x(m_app), pntr_app_mouse_y(m_app));
}

}  // namespace love
