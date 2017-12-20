#include "mouse.h"

#include <SDL.h>
#include <libretro.h>
#include "Types/Graphics/Point.h"
#include "../ChaiLove.h"
#include <string>

using love::Types::Graphics::Point;
using ::ChaiLove;

namespace love {

bool mouse::load() {
	setVisible(false);
	return true;
}

bool mouse::isVisible() {
	return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

mouse& mouse::setVisible(bool visible) {
	SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
	return *this;
}

mouse& mouse::setX(int x) {
	m_x = x;
	SDL_WarpMouse(m_x, m_y);
	return *this;
}

mouse& mouse::setY(int y) {
	m_y = y;
	SDL_WarpMouse(m_x, m_y);
	return *this;
}

int mouse::getX() {
	return m_x;
}

int mouse::getY() {
	return m_y;
}

bool mouse::isDown(int button) {
	return buttonState[button] == true;
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
	} else if (button == "horizwheelup") {
		return RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP;
	} else if (button == "horizwheeldown") {
		return RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN;
	}
	return -1;
}

std::string mouse::getButtonName(int button) {
	switch (button) {
		case RETRO_DEVICE_ID_MOUSE_LEFT:
			return "left";
		case RETRO_DEVICE_ID_MOUSE_RIGHT:
			return "right";
		case RETRO_DEVICE_ID_MOUSE_MIDDLE:
			return "middle";
		case RETRO_DEVICE_ID_MOUSE_WHEELUP:
			return "wheelup";
		case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
			return "wheeldown";
		case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
			return "horizwheelup";
		case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
			return "horizwheeldown";
	}
	return "unknown";
}

void mouse::moveEvent(SDL_MouseMotionEvent event) {
	m_x = event.x;
	m_y = event.y;
	ChaiLove::getInstance()->script->mousemoved(m_x, m_y);
}

void mouse::buttonEvent(SDL_MouseButtonEvent event) {
	if (event.state == SDL_PRESSED) {
		ChaiLove::getInstance()->script->mousepressed(m_x, m_y, event.button);
	} else if (event.state == SDL_RELEASED) {
		ChaiLove::getInstance()->script->mousereleased(m_x, m_y, event.button);
	}
	buttonState[event.button] = event.state;
}

Point mouse::getPosition() {
	return Point(m_x, m_y);
}

}  // namespace love
