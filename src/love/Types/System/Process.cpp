#include "Process.h"

#include "process.h"

#include <string>
#include <sstream>

namespace love {
namespace Types {
namespace System {

Process::Process(const std::string& command) {
	const char* const commandLine[] = {command.c_str(), 0};

	process_create(commandLine, 0, &m_process);
}

Process::~Process() {
	process_destroy(&m_process);
}
}
}

}
