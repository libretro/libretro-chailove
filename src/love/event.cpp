#include "event.h"

namespace love {

void event::quit() {
	m_shouldclose = true;
}

}  // namespace love
