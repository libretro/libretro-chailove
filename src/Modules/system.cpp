#include "system.h"
#include "../ChaiLove.h"

#include <string>

namespace Modules {
	std::string system::getOS() {
		// TODO Resolve the actual current OS.
		return "libretro";
	}

	std::vector<int> system::getVersion() {
		std::vector<int> version;
		version.push_back(CHAILOVE_VERSION_MAJOR);
		version.push_back(CHAILOVE_VERSION_MINOR);
		version.push_back(CHAILOVE_VERSION_PATCH);
		return version;
	}

	std::string system::getVersionString() {
		return CHAILOVE_VERSION_STRING;
	}
}
