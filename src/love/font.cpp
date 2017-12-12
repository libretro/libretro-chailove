#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "font.h"
#include "Types/Graphics/Font.h"

namespace love {

bool font::load() {
	int result = TTF_Init();
	if(result == -1) {
		const char* errorChar = TTF_GetError();
		std::string errString("");
		if (errorChar != NULL) {
			errString = errorChar;
		}
		std::cout << "[ChaiLove] TTF_Init failed to initialize font system: {}" << errString << std::endl;
		return false;
	}
	return true;
}

bool font::unload() {
	TTF_Quit();
	return true;
}

bool font::isOpen() {
	return TTF_WasInit();
}

}  // namespace love
