#include "system.h"
#include "../ChaiLove.h"

#include <string>
#include "libretro.h"

namespace love {

std::string system::getOS() {
	// TODO(RobLoach): Replace Macros with something more complex?
	#if (defined __HAIKU__)
	return "Linux";
	#elif((defined __BEOS__) ||(defined __beos__))
	return "Linux";
	#elif(defined _WIN32_WCE) || (defined _WIN64_WCE)
	return "Windows";
	#elif((defined WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_APP)
	return "Windows";
	#elif(((defined _WIN32) || (defined _WIN64)) && (!defined __CYGWIN__))
	return "Windows";
	#elif(defined OS2)
	return "OS X";
	#elif((defined __MACH__) && (defined __APPLE__))
	return "OS X";
	#elif defined(macintosh)
	return "OS X";
	#elif defined(ANDROID)
	return "Android";
	#elif defined(__linux)
	return "Linux";
	#elif defined(__sun) || defined(sun)
	return "Linux";
	#elif defined(__FreeBSD__) || defined(__DragonFly__)
	return "Linux";
	#elif defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
	return "Linux";
	#elif defined(unix) || defined(__unix__)
	return "Linux";
	#else
	return "Other";
	#endif
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

}  // namespace love
