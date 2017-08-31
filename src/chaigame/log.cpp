#include "log.h"

namespace chaigame {
	std::shared_ptr<spdlog::logger> log() {
		static std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("ChaiGame");
		return logger;
	}
}
