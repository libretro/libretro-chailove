#ifndef SRC_LIBRETROLOG_H_
#define SRC_LIBRETROLOG_H_

#include "libretro.h"

extern retro_log_printf_t log_cb;

#ifdef __cplusplus

#include <ostream>
#include <sstream>

class LibretroLog {
public:
	static std::ostream &log(enum retro_log_level level);
	static void flushLog();

private:
	class LoggerBuf : public std::stringbuf
	{
	public:
		virtual int sync();

		LoggerBuf(enum retro_log_level level_in) : level(level_in) {}
	private:
		enum retro_log_level level;
	};
};

#endif

#endif
