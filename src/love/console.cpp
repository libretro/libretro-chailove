#include "console.h"
#include "../ChaiLove.h"
#include "Types/Graphics/Font.h"

#include <iostream>
#include <string>
#include <vector>

using love::Types::Graphics::Font;

namespace love {

bool console::load(const config& conf) {
	// Use ` for the toggling key.
	m_togglescancode = 96;
	m_enabled = conf.console;
	m_shown = false;
	return true;
}

bool console::isShown() {
	return m_shown;
}

void console::keypressed(std::string key, int scancode) {
	// Test scancode and key input.
	// ChaiLove::log(RETRO_LOG_DEBUG) << "Key: " << key << std::endl << "Cod: " << scancode << std::endl << m_togglescancode;

	// Only use the console if it is available.
	if (!isEnabled()) {
		return;
	}

	// Toggle the console.
	if (scancode == m_togglescancode) {
		m_shown = !m_shown;
		return;
	}

	// Don't act on key presses if the console is not shown.
	if (!isShown()) {
		return;
	}

	// Interpret a key press as ascii character entry.
	ChaiLove* app = ChaiLove::getInstance();
	bool shiftDown = app->keyboard.isDown("shift") || app->keyboard.isDown("lshift") || app->keyboard.isDown("rshift");
	if (key.size() == 1) {
		if (scancode >= 97 && scancode <= 122) {
			if (shiftDown) {
				m_input += (char)(scancode - 32);
			} else {
				m_input += key;
			}
		} else if (scancode == 43) {
			// Nothing.
		} else if (scancode == 61) {
			if (!shiftDown) {
				m_input += "=";
			} else {
				m_input += "+";
			}
		} else if (scancode == 45) {
			// Nothing.
		} else if (scancode == 95) {
			if (!shiftDown) {
				m_input += "-";
			} else {
				m_input += "_";
			}
		} else if (scancode == 33 || scancode == 64 || scancode == 35 || scancode == 36 || scancode == 38 || scancode == 42) {
			// Nothing.
		} else if (scancode >= 48 && scancode <= 57) {
			if (!shiftDown) {
				m_input += key;
			} else {
				switch (scancode) {
					case 48:
						m_input += ")";
						break;
					case 49:
						m_input += "!";
						break;
					case 50:
						m_input += "@";
						break;
					case 51:
						m_input += "#";
						break;
					case 52:
						m_input += "$";
						break;
					case 53:
						m_input += "%";
						break;
					case 54:
						m_input += "^";
						break;
					case 55:
						m_input += "&";
						break;
					case 56:
						m_input += "*";
						break;
					case 57:
						m_input += "(";
						break;
				}
			}
		} else if (scancode == 39) {
			// Nothing
		} else if (scancode == 34) {
			if (shiftDown) {
				m_input += '"';
			} else {
				m_input += '\'';
			}
		} else if (scancode == 47) {
			// Nothing.
		} else if (scancode == 63) {
			if (shiftDown) {
				m_input += '?';
			} else {
				m_input += '/';
			}
		} else if (scancode == 46) {
			// Nothing.
		} else if (scancode == 62) {
			if (shiftDown) {
				m_input += '>';
			} else {
				m_input += '.';
			}
		} else if (scancode == 58) {
			// Nothing.
		} else if (scancode == 59) {
			if (shiftDown) {
				m_input += ':';
			} else {
				m_input += ';';
			}
		} else if (scancode == 91) {
			if (shiftDown) {
				m_input += "{";
			} else {
				m_input += "[";
			}
		} else if (scancode == 93) {
			if (shiftDown) {
				m_input += "}";
			} else {
				m_input += "]";
			}
		} else {
			m_input += key;
		}
	} else if (key == "space") {
		m_input += " ";
	} else if (key == "backspace") {
		if (m_input.size() > 0) {
			m_input.pop_back();
		}
	} else if (key == "return") {
		execute(m_input);
		m_input = "";
	}
}

void console::draw() {
	if (!isShown()) {
		return;
	}

	ChaiLove* app = ChaiLove::getInstance();
	int bottom = app->graphics.getHeight() - app->graphics.getHeight() / 3;

	// Retrieve the detault font.
	Font* font = app->graphics.setFont().getFont();
	app->graphics.setColor(0, 0, 0, 200);
	app->graphics.rectangle("fill", 0, 0, app->graphics.getWidth(), bottom);
	app->graphics.setColor(255, 255, 255);
	app->graphics.print("> " + m_input, 0, bottom - font->getHeight());

	// Display the log, starting 2 lines up from the bottom.
	int numEntry = 2;
	for (std::vector<std::string>::reverse_iterator i = m_log.rbegin(); i != m_log.rend(); ++i) {
		app->graphics.print(*i, 0, bottom - font->getHeight() * numEntry++);
	}
}

void console::execute(const std::string& entry) {
	m_log.push_back(entry);
	ChaiLove* app = ChaiLove::getInstance();
	try {
		std::string out = app->script->evalString(entry, "__EVAL__");
		if (!out.empty()) {
			m_log.push_back(out);
		}
	}
	catch (const chaiscript::exception::eval_error &e) {
		m_log.push_back(e.what());
	} catch (const std::exception &e) {
		m_log.push_back(e.what());
	}
}

bool console::isEnabled() {
	return m_enabled;
}

bool console::setEnabled(bool enabled) {
	return m_enabled = enabled;
}

}  // namespace love
