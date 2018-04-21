#include <iostream>

#include "tiled.h"
#include "../ChaiLove.h"

#include "TmxMap.h"
using ::ChaiLove;

namespace love {

tiled::tiled() {
	// Nothing.
}

Tmx::Map* tiled::newMap(const std::string& filename) {
	ChaiLove* app = ChaiLove::getInstance();
	std::string contents = app->filesystem.read(filename);
	if (contents.empty()) {
		return NULL;
	}

	Tmx::Map* map = new Tmx::Map();
	map->ParseText(contents);
	return map;
}

}  // namespace love
