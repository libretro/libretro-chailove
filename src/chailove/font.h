#ifndef CHAILOVE_FONT_H
#define CHAILOVE_FONT_H

#include "graphics/Font.h"

namespace chailove {
	class font {
	public:
		bool load();
		bool isOpen();
		bool unload();
	};
}

#endif
