#include "mouse.h"

#include <SDL.h>
#include "src/Point.h"

namespace chaigame {

	bool mouse::load() {
		setVisible(false);
		return true;
	}

	bool mouse::isVisible() {
		return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
	}

	void mouse::setVisible(bool enable) {
		SDL_ShowCursor(enable ? SDL_ENABLE : SDL_DISABLE);
	}

	void mouse::setX(int x) {
		m_x = x;
		SDL_WarpMouse(m_x, m_y);
	}

	void mouse::setY(int y) {
		m_y = y;
		SDL_WarpMouse(m_x, m_y);
	}

	int mouse::getX() {
		return m_x;
	}

	int mouse::getY() {
		return m_y;
	}

	bool mouse::isDown(int button) {
		// Switch the secondary and middle indexes to match LOVE:
		// https://love2d.org/wiki/love.mouse.isDown
		if (button == 2) {
			button = 3;
		}
		else if (button == 3) {
			button = 2;
		}
		return buttonState[button] == true;
	}

	void mouse::motionEvent(SDL_MouseMotionEvent event) {
		m_x = event.x;
		m_y = event.y;
		// TODO: Trigger mouse event.
	}
void mouse::buttonEvent(SDL_MouseButtonEvent event) {
		buttonState[event.button] = event.state;

		// TODO: Trigger mouse button event.
	}

	Point mouse::getPosition() {
		return Point(m_x, m_y);
	}
}
