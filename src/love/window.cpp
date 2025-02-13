#include "window.h"
#include <string>
#include "../ChaiLove.h"

#include "pntr_app.h"
#include "config.h"
#include "libretro.h"
#include "Types/Graphics/Point.h"

using ::ChaiLove;
using love::Types::Graphics::Point;

namespace love {

bool window::load(pntr_app* app, const config& conf) {
	m_app = app;

	// Title
	setTitle(conf.window.title);

	// Size
	pntr_app_set_size(app, conf.window.width, conf.window.height);
	return true;
}

bool window::unload() {
	return true;
}

std::string window::getTitle() {
	return m_title;
}

window& window::setTitle(const std::string& title) {
	if (m_app != NULL) {
		pntr_app_set_title(m_app, title.c_str());
	}
	m_title = title;
	return *this;
}

window& window::showMessageBox(const std::string& msg, int frames) {
	retro_message retroMessage;
	retroMessage.msg = msg.c_str();
	retroMessage.frames = frames;
	retro_environment_t environ_cb = pntr_app_libretro_environ_cb(NULL);
	if (environ_cb == NULL) {
		pntr_app_log(PNTR_APP_LOG_ERROR, "[ChaiLove] Environment callback not set for showMessageBox");
		return *this;
	}
	environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &retroMessage);
	return *this;
}

window& window::showMessageBox(const std::string& msg) {
	showMessageBox(msg, 500);
	return *this;
}

}  // namespace love
