#ifndef CHAIGAMELOG_H
#define CHAIGAMELOG_H

#include "spdlog/spdlog.h"

namespace chaigame {
	std::shared_ptr<spdlog::logger> log();
}

#endif
