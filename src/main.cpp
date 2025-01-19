#include <string>
#include <iostream> // TODO: Remove this

#define PNTR_PHYSFS_IMPLEMENTATION
#include "pntr_physfs.h"

#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_MATH
#define PNTR_NO_STDIO
#define PNTR_NO_SAVE_IMAGE
#include "pntr_app.h"

#include "LibretroLog.h"

#include "ChaiLove.h"

bool Init(pntr_app* app) {
    ChaiLove::environ_cb = pntr_app_libretro_environ_cb(app);

    // Initialize PhysFS
    if (PHYSFS_init((const char*)ChaiLove::environ_cb) == 0) {
        pntr_app_log(PNTR_APP_LOG_ERROR, "PHYSFS_init() failed");
        return false;
    }

    // Set up the chailove instance.
    ChaiLove* chailove = ChaiLove::getInstance();
    if (chailove == NULL) {
        PHYSFS_deinit();
        return false;
    }

    // Load
    std::string argFile = app->argFile == NULL ? "" : app->argFile;
    if (!chailove->load(argFile, app->argFileData, app->argFileDataSize)) {
        ChaiLove::destroy();
        PHYSFS_deinit();
        return false;
    }
    pntr_app_set_userdata(app, (void*)chailove);

    return true;
}

void Event(pntr_app* app, pntr_app_event* event) {
    ChaiLove* chailove = (ChaiLove*)pntr_app_userdata(app);

    switch (event->type) {
        case PNTR_APP_EVENTTYPE_KEY_DOWN: {
            chailove->keyboard.eventKeyPressed(event->key);
        }
        break;

        case PNTR_APP_EVENTTYPE_KEY_UP: {
            chailove->keyboard.eventKeyReleased(event->key);
        }
        break;

        // case PNTR_APP_EVENTTYPE_MOUSE_WHEEL: {
        //     pntr_app_log_ex(PNTR_APP_LOG_INFO, "Wheel: %d", event->mouseWheel);
        // }
        // break;

        // case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN:
        // case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP: {
        //     const char* buttonDown = event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN ? "Pressed" : "Released";

        //     const char* button;
        //     switch (event->mouseButton) {
        //         case PNTR_APP_MOUSE_BUTTON_LEFT: button = "left"; break;
        //         case PNTR_APP_MOUSE_BUTTON_RIGHT: button = "right"; break;
        //         case PNTR_APP_MOUSE_BUTTON_MIDDLE: button = "middle"; break;
        //         case PNTR_APP_MOUSE_BUTTON_LAST:
        //         case PNTR_APP_MOUSE_BUTTON_UNKNOWN: button = "unknown"; break;
        //     }
        //     pntr_app_log_ex(PNTR_APP_LOG_INFO, "Mouse Button %s: %s", buttonDown, button);

        //     if (event->type == PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN) {
        //         if (event->mouseButton == PNTR_APP_MOUSE_BUTTON_LEFT) {
        //             pntr_play_sound(appData->sound, false);
        //         }
        //         else if (event->mouseButton == PNTR_APP_MOUSE_BUTTON_RIGHT) {
        //             pntr_stop_sound(appData->music);
        //             pntr_play_sound(appData->music, true);
        //         }
        //     }
        // }
        // break;

        // case PNTR_APP_EVENTTYPE_MOUSE_MOVE: {
        //     //pntr_app_log_ex(PNTR_APP_LOG_INFO, "Mouse Move: (%d, %d) | (%d, %d)", event->mouseX, event->mouseY, event->mouseDeltaX, event->mouseDeltaY);
        // }
        // break;

        // case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP:
        // case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN: {
        //     pntr_app_log_ex(PNTR_APP_LOG_INFO, "Gamepad: %d. Button: %d %s", event->gamepad, event->gamepadButton, event->type == PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN ? "Pressed" : "Released");
        // }
        // break;

        // case PNTR_APP_EVENTTYPE_FILE_DROPPED: {
        //     sprintf(message, "File Dropped: %s", event->fileDropped);
        //     pntr_app_log(PNTR_APP_LOG_INFO, message);

        //     if (appData->droppedImage != NULL) {
        //         pntr_unload_image(appData->droppedImage);
        //     }

        //     appData->droppedImage = pntr_load_image(event->fileDropped);
        // }
        // break;

        // default: {
        //     pntr_app_log_ex(PNTR_APP_LOG_INFO, "Unknown event: %d", event->type);
        // }
        // break;
    }
}

bool Update(pntr_app* app, pntr_image* screen) {
    ChaiLove* chailove = (ChaiLove*)pntr_app_userdata(app);
    chailove->screen = screen;
    if (chailove == NULL) {
        return false;
    }

	// Update the game.
    pntr_app_log(PNTR_APP_LOG_INFO, "OMGOMGOMG");
	chailove->update();
    pntr_app_log(PNTR_APP_LOG_INFO, "OMGOMGOMG2222");

    if (chailove->event.m_shouldclose) {
        return false;
    }

    pntr_app_log(PNTR_APP_LOG_INFO, "drawing");
	// Render the game.
	chailove->draw();

    return true;
}

void Close(pntr_app* app) {
    ChaiLove::destroy();
    PHYSFS_deinit();
}

pntr_app Main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    return (pntr_app) {
        .width = 640,
        .height = 480,
        .title = "ChaiLove",
        .init = Init,
        .update = Update,
        .close = Close,
        .event = Event,
        .fps = 0,
    };
}

int LibretroLog::LoggerBuf::sync() {
	const std::string &s = str();
	if (!s.empty()) {
		if (s[s.length() - 1] == '\n')
			log_cb(level, "%s", s.c_str());
		else
			log_cb(level, "%s\n", s.c_str());
	}
	str() = "";
	return 0;
}

std::ostream &LibretroLog::log(enum retro_log_level level) {
	static LibretroLog::LoggerBuf *bufs[RETRO_LOG_ERROR + 1] = {0};
	static std::ostream *streams[RETRO_LOG_ERROR + 1] = {0};
	if (!bufs[level]) {
		bufs[level] = new LibretroLog::LoggerBuf(level);
		streams[level] = new std::ostream(bufs[level]);
	}
	return *streams[level];
}
