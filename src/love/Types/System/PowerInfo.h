#ifndef SRC_LOVE_TYPES_SYSTEM_POWERINFO_H_
#define SRC_LOVE_TYPES_SYSTEM_POWERINFO_H_

namespace love {
namespace Types {
namespace System {

/**
 * Represents a physical joystick.
 */
struct PowerInfo {
	public:
    int state;
    int percent;
    int seconds;
};

}  // namespace System
}  // namespace Types
}  // namespace love

#endif  // SRC_LOVE_TYPES_SYSTEM_POWERINFO_H_
