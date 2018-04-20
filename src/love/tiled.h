#ifndef SRC_LOVE_CONFIG_H_
#define SRC_LOVE_CONFIG_H_

#include <map>
#include <string>

#include "TmxMap.h"

#include "Types/Config/ModuleConfig.h"
#include "Types/Config/WindowConfig.h"

using love::Types::Config::ModuleConfig;

namespace love {

/**
 * Tiled support for ChaiLove.
 */
class tiled {
	public:
	tiled();

	Tmx::Map* newMap(const std::string& filename);
};

}  // namespace love

#endif  // SRC_LOVE_CONFIG_H_
