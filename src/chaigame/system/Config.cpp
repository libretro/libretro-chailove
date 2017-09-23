#include "Config.h"
#include "../../ChaiGame.h"

namespace chaigame {
	Config::Config() {
		options["alphablending"] = true;
		options["highquality"] = true;
		version = CHAIGAME_VERSION_STRING;
	}
}
