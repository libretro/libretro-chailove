#ifndef SRC_LOVE_CONSOLE_H_
#define SRC_LOVE_CONSOLE_H_

#include <string>
#include <vector>
#include "config.h"

namespace love {

/**
 * @brief In-game console for ChaiLove.
 *
 * Enable the console by pressing the tilde key on your keyboard. It will
 * execute ChaiScript. For example, open the console with \`, and type
 * `love.system.getOS()`.
 *
 * To enable the console, you must trigger: love.console.setEnabled(true)
 */
class console {
	public:
	std::vector<std::string> m_log;
	std::string m_input = std::string("");
	bool m_enabled = false;
	bool m_shown = false;
	int m_togglescancode;
	bool load(const config& conf);

	void keypressed(std::string key, int scancode);
	void draw();

	/**
	 * @brief Checks to see if the console is enabled.
	 */
	bool isEnabled();

	/**
	 * @brief Enable or disable the console.
	 */
	bool setEnabled(bool enabled);

	/**
	 * @brief Checks whether or not the console is being displayed.
	 */
	bool isShown();

	void execute(const std::string& entry);
};

}  // namespace love

#endif  // SRC_LOVE_CONSOLE_H_
