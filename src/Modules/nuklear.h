#ifndef SRC_MODULES_NUKLEAR_H_
#define SRC_MODULES_NUKLEAR_H_

#include <string>

#include "SDL.h"
#include "../../vendor/nuklear_sdl_12/nuklear/nuklear.h"

namespace Modules {

/**
 * @brief Provides an interface to the user's mouse.
 */
class nuklear {
	public:
	bool load();
	void unload();

	void inputBegin();
	void inputHandleEvent(SDL_Event *event);
	void inputEnd();

	void setStyle(int style);

	void draw();

	struct nk_context *ctx;
};

}  // namespace Modules

#endif  // SRC_MODULES_NUKLEAR_H_
