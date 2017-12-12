#include "Config.h"
#include "../../ChaiLove.h"

namespace love {
namespace Types {
namespace System {

Config::Config() {
	options["alphablending"] = true;
	options["highquality"] = true;
	version = CHAILOVE_VERSION_STRING;
}

}  // namespace System
}  // namespace Types
}  // namespace love
