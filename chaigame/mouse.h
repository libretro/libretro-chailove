#ifndef CHAIGAME_MOUSE_H
#define CHAIGAME_MOUSE_H

//#include "SDL.h"
#include "src/Point.h"

namespace chaigame {
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

		int m_x, m_y;
		int buttonState[20];

		//void motionEvent(SDL_MouseMotionEvent event);
		//void buttonEvent(SDL_MouseButtonEvent event);
	};
}

#endif
