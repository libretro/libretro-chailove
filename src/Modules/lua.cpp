#include "./lua.h"

#define SOL_CHECK_ARGUMENTS 1
#include <sol.hpp>

namespace Modules {

bool lua::load() {

	sol::state lua;
	// open some common libraries
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.script("print('bark bark bark!')");
	return true;
}

}
