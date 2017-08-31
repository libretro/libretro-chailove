#ifndef CHAIGAME_LOG_H
#define CHAIGAME_LOG_H

#include "spdlog/spdlog.h"

namespace chaigame {
	std::shared_ptr<spdlog::logger> log();
}

#endif
