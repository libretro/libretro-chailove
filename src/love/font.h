#ifndef SRC_LOVE_FONT_H_
#define SRC_LOVE_FONT_H_

#include "Types/Graphics/Font.h"

namespace love {
/**
 * Allows you to work with fonts.
 */
class font {
	public:
	~font();
	bool load();

	/**
	 * Retrieves whether or not all sub-systems have been loaded.
	 *
	 * @return True if the Font sub-system has been loaded.
	 */
	bool isOpen();

	bool unload();
};

}  // namespace love

#endif  // SRC_LOVE_FONT_H_
