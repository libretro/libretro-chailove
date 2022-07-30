#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "font.h"
#include "Types/Graphics/Font.h"
#include "../LibretroLog.h"

namespace love {

font::~font() {
	unload();
}

bool font::load() {
	int result = TTF_Init();
	if(result == -1) {
		const char* errorChar = TTF_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		LibretroLog::log(RETRO_LOG_ERROR) << "[ChaiLove] TTF_Init failed to initialize font system: {}" << errString << std::endl;
		return false;
	}
	return true;
}

bool font::unload() {
	if (isOpen()) {
		TTF_Quit();
	}
	return true;
}

bool font::isOpen() {
	return TTF_WasInit();
}

}  // namespace love
