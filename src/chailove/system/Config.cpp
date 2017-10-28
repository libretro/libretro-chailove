#include "Config.h"
#include "../../ChaiLove.h"

namespace chailove {
	Config::Config() {
		options["alphablending"] = true;
		options["highquality"] = true;
		version = CHAILOVE_VERSION_STRING;
	}
}
