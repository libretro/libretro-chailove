#ifndef SRC_LOVE_TILED_H_
#define SRC_LOVE_TILED_H_

#include <map>
#include <string>

#include "TmxMap.h"

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

#endif  // SRC_LOVE_TILED_H_
