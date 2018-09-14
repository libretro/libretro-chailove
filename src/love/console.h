#ifndef SRC_LOVE_CONSOLE_H_
#define SRC_LOVE_CONSOLE_H_

#include <string>
#include <vector>
#include "config.h"

namespace love {

/**
 * In-game console for ChaiLove.
 *
 * To enable the console, you must trigger: `love.console.setEnabled(true)` or toggle the console in `love.conf`.
 *
 * Once enabled, display the console by pressing the tilde key on your keyboard. Running commands will execute ChaiScript. For example, try running `love.system.getOS()`.
 *
 * @see love.config
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
	 * Checks to see if the console is enabled.
	 *
	 * @see setEnabled
	 */
	bool isEnabled();

	/**
	 * Enable or disable the console.
	 *
	 * @see isEnabled
	 */
	bool setEnabled(bool enabled);

	/**
	 * Checks whether or not the console is being displayed.
	 */
	bool isShown();

	void execute(const std::string& entry);
};

}  // namespace love

#endif  // SRC_LOVE_CONSOLE_H_
