#ifndef CHAILOVE_FONT_H
#define CHAILOVE_FONT_H

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
}

#endif
