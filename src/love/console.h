#ifndef SRC_LOVE_CONSOLE_H_
#define SRC_LOVE_CONSOLE_H_

#include <string>
#include <vector>

namespace love {

/**
 * @brief In-game console for ChaiLove.
 *
 * Enable the console by pressing the tilde key on your keyboard. It will
 * execute ChaiScript. For example, open the console with \`, and type
 * `love.system.getOS()`.
 */
class console {
	public:
	std::vector<std::string> m_log;
	std::string m_input = std::string("");
	bool m_enabled = false;
	int m_togglescancode;
	bool load();

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
	 * @brief Toggles the console on or off.
	 *
	 * @return True if the console is toggle on, false otherwise.
	 */
	bool toggle();

	void execute(const std::string& entry);
};

}  // namespace love

#endif  // SRC_LOVE_CONSOLE_H_
