#ifndef _FONT_H_INCLUDED_
#define _FONT_H_INCLUDED_

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
