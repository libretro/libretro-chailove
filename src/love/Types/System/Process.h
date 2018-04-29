#ifndef SRC_LOVE_TYPES_SYSTEM_PROCESS_H_
#define SRC_LOVE_TYPES_SYSTEM_PROCESS_H_

#include <string>
#include "process.h"

namespace love {
namespace Types {
namespace System {

class Process {
public:
	Process(const std::string& command);
	~Process();

private:
	struct process_s m_process;
};

}
}
}

#endif  // SRC_LOVE_TYPES_SYSTEM_PROCESS_H_
