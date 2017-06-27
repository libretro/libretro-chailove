#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <physfs.h>

namespace chaigame {
	class filesystem {
	public:
		bool load(std::string file);
		bool unload();
	};
}

#endif
