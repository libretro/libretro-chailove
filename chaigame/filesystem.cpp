
#include <physfs.h>

#include "filesystem.h"
#include "../Application.h"

namespace chaigame {
	bool filesystem::load() {
		PHYSFS_init(NULL);
	}
}
