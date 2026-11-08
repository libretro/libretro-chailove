#include <string>
#include <list>
#include "pntr_app.h"
#include "font.h"
#include "Types/Graphics/Font.h"

namespace love {

font::~font() {
	unload();
}

bool font::load() {
	return true;
}

bool font::unload() {
	for (std::list<Font*>::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it) {
		if (*it != NULL) {
			delete *it;
		}
	}
	m_fonts.clear();
	return true;
}

Font* font::add(Font* newFont) {
	if (newFont != NULL && newFont->loaded()) {
		m_fonts.push_back(newFont);
		return newFont;
	}
	delete newFont;
	return NULL;
}

bool font::isOpen() {
	return true;
}

}  // namespace love
