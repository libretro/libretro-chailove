#ifndef SRC_MODULES_FONT_H_
#define SRC_MODULES_FONT_H_

#include "../Types/Graphics/Font.h"

namespace Modules {
/**
 * @brief Allows you to work with fonts.
 */
class font {
	public:
	bool load();

	/**
	 * @brief Retrieves whether or not all sub-systems have been loaded.
	 */
	bool isOpen();

	bool unload();
};

}  // namespace Modules

#endif  // SRC_MODULES_FONT_H_
