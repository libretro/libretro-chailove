#include <string>
#include <map>
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
	for (std::map<std::string, Font*>::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it) {
		delete it->second;
	}
	m_fonts.clear();
	return true;
}

Font* font::get(const std::string& key, const std::function<Font*()>& create) {
	std::map<std::string, Font*>::iterator it = m_fonts.find(key);
	if (it != m_fonts.end()) {
		return it->second;
	}

	Font* newFont = create();
	if (newFont != NULL && newFont->loaded()) {
		m_fonts[key] = newFont;
		return newFont;
	}
	delete newFont;
	return NULL;
}

bool font::isOpen() {
	return true;
}

}  // namespace love
