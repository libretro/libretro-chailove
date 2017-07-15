#ifndef CHAIGAME_FONT_H
#define CHAIGAME_FONT_H

#include "src/Font.h"

namespace chaigame {
	class font {
	public:
		bool load();
		bool isOpen();
		bool unload();
	};
}

#endif
