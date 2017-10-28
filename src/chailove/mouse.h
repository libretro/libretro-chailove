#ifndef CHAILOVE_MOUSE_H
#define CHAILOVE_MOUSE_H

#include <SDL.h>
#include <string>
#include "graphics/Point.h"

namespace chailove {
	class mouse {
	public:
		bool load();
		void setVisible(bool enable);
		bool isVisible();

		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		Point getPosition();

		bool isDown(int button);
		bool isDown(const std::string& button);

		int getButtonKey(const std::string& button);
		std::string getButtonName(int button);

		int m_x, m_y;
		int buttonState[20];

		void moveEvent(SDL_MouseMotionEvent event);
		void buttonEvent(SDL_MouseButtonEvent event);
	};
}

#endif
