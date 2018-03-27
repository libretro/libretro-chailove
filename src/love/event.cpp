#include "event.h"

namespace love {

void event::quit() {
	m_quitstatus = true;
}

}  // namespace love
