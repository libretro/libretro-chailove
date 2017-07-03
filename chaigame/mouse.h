#ifndef _MOUSE_H_INCLUDED_
#define _MOUSE_H_INCLUDED_

#include <SDL.h>

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

		bool isDown(int button);

		int m_x, m_y;
		Uint8 buttonState[SDL_BUTTON_X2 + 1];

		void motionEvent(SDL_MouseMotionEvent event);
		void buttonEvent(SDL_MouseButtonEvent event);
	};
}

#endif
