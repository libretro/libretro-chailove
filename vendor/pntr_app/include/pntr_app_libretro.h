#ifdef PNTR_APP_LIBRETRO
#ifndef PNTR_APP_LIBRETRO_H__
#define PNTR_APP_LIBRETRO_H__

#include <stdarg.h> // va_start, va_end
#include <string.h> // memset
#include <stdio.h>  // vfprintf
#include <time.h> // time()

#ifndef PNTR_APP_LIBRETRO_H
    #define PNTR_APP_LIBRETRO_H "libretro.h"
#endif  // PNTR_APP_LIBRETRO_H
#include PNTR_APP_LIBRETRO_H

// libretro has its own entry point
#ifndef PNTR_APP_NO_ENTRY
    #define PNTR_APP_NO_ENTRY
#endif  // PNTR_APP_NO_ENTRY

typedef struct pntr_app_libretro_platform {
    // Input
    int16_t mouseButtonState[PNTR_APP_MOUSE_BUTTON_LAST];
    int16_t mouseX;
    int16_t mouseY;
    int16_t gamepadState[PNTR_APP_MAX_GAMEPADS][PNTR_APP_GAMEPAD_BUTTON_LAST];
    bool mouseHidden;

    // Audio
    float* audioSamples;
    int16_t* audioSamples2;
    int audioBufferSize;
    bool audioEnabled;
} pntr_app_libretro_platform;

/**
 * Retrieve the environment callback from libretro.
 *
 * @param app The associated pntr_app application. This call be NULL to get the global state.
 *
 * @return The environment callback.
 */
retro_environment_t pntr_app_libretro_environ_cb(pntr_app* app);

#endif  // PNTR_APP_LIBRETRO_H__

#if defined(PNTR_APP_IMPLEMENTATION) && !defined(PNTR_APP_HEADER_ONLY)
#ifndef PNTR_APP_LIBRETRO_IMPLEMENTATION_ONCE
#define PNTR_APP_LIBRETRO_IMPLEMENTATION_ONCE

#include "external/pico_b64.h"

#include "audio/audio_mixer.h"
#include "audio/audio_resampler.h"
#include "audio/conversion/float_to_s16.h"

// Audio sample size
#ifndef PNTR_APP_LIBRETRO_SAMPLES
    #define PNTR_APP_LIBRETRO_SAMPLES 48000
#endif

pntr_app* pntr_app_libretro;

/**
 * Internal structure to handle libretro audio.
 *
 * @internal
 */
typedef struct pntr_sound_libretro {
    audio_mixer_sound_t* sound;
    audio_mixer_voice_t* voice;
    float volume;
    bool playing;
} pntr_sound_libretro;

/**
 * From audio_mixer.c. We include this here because the definition isn't in the .h file.
 *
 * @see https://github.com/libretro/libretro-common/blob/master/audio/audio_mixer.c#L76
 */
struct audio_mixer_sound
{
   enum audio_mixer_type type;
   void* user_data;
};

static struct retro_log_callback logging;
static retro_log_printf_t log_cb;
struct retro_vfs_interface* vfs = NULL;

#ifndef PNTR_LOAD_FILE
    /**
     * Load a file using libretro's virtual file system.
     */
    unsigned char* pntr_app_libretro_load_file(const char* fileName, unsigned int* bytesRead) {
        if (vfs == NULL) {
            return NULL;
        }

        // Open the file
        struct retro_vfs_file_handle* file = vfs->open(fileName, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);
        if (file == NULL) {
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return NULL;
        }

        // Get the size
        int64_t size = vfs->size(file);
        if (size <= 0) {
            vfs->close(file);
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return NULL;
        }

        // Prepare the data
        unsigned char* data = (unsigned char*)pntr_load_memory(size * sizeof(unsigned char) + 1);
        if (data == NULL) {
            vfs->close(file);
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return NULL;
        }

        // Read the file
        unsigned int bytes = (unsigned int)vfs->read(file, data, size);
        vfs->close(file);
        if (bytesRead != NULL) {
            *bytesRead = bytes;
        }

        return data;
    }
    #define PNTR_LOAD_FILE pntr_app_libretro_load_file
#endif

#ifndef PNTR_SAVE_FILE
    /**
     * Save a file using libretro's file system.
     */
    bool pntr_app_libretro_save_file(const char *fileName, const void *data, unsigned int bytesToWrite) {
        if (vfs == NULL) {
            return false;
        }

        // Open the file
        struct retro_vfs_file_handle* file = vfs->open(fileName, RETRO_VFS_FILE_ACCESS_WRITE, RETRO_VFS_FILE_ACCESS_HINT_NONE);
        if (file == NULL) {
            return false;
        }

        // Write the file
        int64_t bytesWritten = vfs->write(file, data, (uint64_t)bytesToWrite);
        if (bytesWritten <= 0) {
            vfs->close(file);
            return false;
        }

        // Flush the buffer and close the file.
        vfs->flush(file);
        vfs->close(file);

        return true;
    }
    #define PNTR_SAVE_FILE(fileName, data, bytesToWrite) pntr_app_libretro_save_file(fileName, data, bytesToWrite)
#endif

pntr_app_gamepad_button pntr_app_libretro_gamepad_button(int button) {
    switch (button) {
        case RETRO_DEVICE_ID_JOYPAD_UP: return PNTR_APP_GAMEPAD_BUTTON_UP;
        case RETRO_DEVICE_ID_JOYPAD_RIGHT: return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
        case RETRO_DEVICE_ID_JOYPAD_DOWN: return PNTR_APP_GAMEPAD_BUTTON_DOWN;
        case RETRO_DEVICE_ID_JOYPAD_LEFT: return PNTR_APP_GAMEPAD_BUTTON_LEFT;
        case RETRO_DEVICE_ID_JOYPAD_X: return PNTR_APP_GAMEPAD_BUTTON_Y;
        case RETRO_DEVICE_ID_JOYPAD_A: return PNTR_APP_GAMEPAD_BUTTON_B;
        case RETRO_DEVICE_ID_JOYPAD_B: return PNTR_APP_GAMEPAD_BUTTON_A;
        case RETRO_DEVICE_ID_JOYPAD_Y: return PNTR_APP_GAMEPAD_BUTTON_X;
        case RETRO_DEVICE_ID_JOYPAD_L: return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
        case RETRO_DEVICE_ID_JOYPAD_L2: return PNTR_APP_GAMEPAD_BUTTON_LEFT_TRIGGER;
        case RETRO_DEVICE_ID_JOYPAD_R: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
        case RETRO_DEVICE_ID_JOYPAD_R2: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_TRIGGER;
        case RETRO_DEVICE_ID_JOYPAD_SELECT: return PNTR_APP_GAMEPAD_BUTTON_SELECT;
        case RETRO_DEVICE_ID_JOYPAD_START: return PNTR_APP_GAMEPAD_BUTTON_START;
        case RETRO_DEVICE_ID_JOYPAD_L3: return PNTR_APP_GAMEPAD_BUTTON_LEFT_THUMB;
        case RETRO_DEVICE_ID_JOYPAD_R3: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_THUMB;
        //case RETRO_DEVICE_ID_JOYPAD_L3: return PNTR_APP_GAMEPAD_BUTTON_MENU;
    }

    return PNTR_APP_GAMEPAD_BUTTON_UNKNOWN;
}

pntr_app_key pntr_app_libretro_key(int key) {
    switch (key) {
        case RETROK_UNKNOWN: return PNTR_APP_KEY_INVALID;
        case RETROK_BACKSPACE: return PNTR_APP_KEY_BACKSPACE;
        case RETROK_TAB: return PNTR_APP_KEY_TAB;
        //case RETROK_CLEAR: return PNTR_APP_KEY_CLEAR;
        case RETROK_RETURN: return PNTR_APP_KEY_ENTER;
        //case RETROK_PAUSE: return PNTR_APP_KEY_PAUSE;
        case RETROK_ESCAPE: return PNTR_APP_KEY_ESCAPE;
        case RETROK_SPACE: return PNTR_APP_KEY_SPACE;
        // case RETROK_EXCLAIM: return PNTR_APP_KEY_EXCLAIM;
        // case RETROK_QUOTEDBL: return PNTR_APP_KEY_D;
        // case RETROK_HASH: return PNTR_APP_KEY_HASH;
        // case RETROK_DOLLAR: return PNTR_APP_KEY_DOLLAR;
        // case RETROK_AMPERSAND: return PNTR_APP_KEY_AMPERSAND;
        // case RETROK_QUOTE: return PNTR_APP_KEY_QUOTE;
        // case RETROK_LEFTPAREN: return PNTR_APP_KEY_LEFTPAREN;
        // case RETROK_RIGHTPAREN: return PNTR_APP_KEY_RIGHTPAREN;
        // case RETROK_ASTERISK: return PNTR_APP_KEY_ASTERISK;
        // case RETROK_PLUS: return PNTR_APP_KEY_PLUS;
        case RETROK_COMMA: return PNTR_APP_KEY_COMMA;
        case RETROK_MINUS: return PNTR_APP_KEY_MINUS;
        case RETROK_PERIOD: return PNTR_APP_KEY_PERIOD;
        case RETROK_SLASH: return PNTR_APP_KEY_SLASH;
        case RETROK_0: return PNTR_APP_KEY_0;
        case RETROK_1: return PNTR_APP_KEY_1;
        case RETROK_2: return PNTR_APP_KEY_2;
        case RETROK_3: return PNTR_APP_KEY_3;
        case RETROK_4: return PNTR_APP_KEY_4;
        case RETROK_5: return PNTR_APP_KEY_5;
        case RETROK_6: return PNTR_APP_KEY_6;
        case RETROK_7: return PNTR_APP_KEY_7;
        case RETROK_8: return PNTR_APP_KEY_8;
        case RETROK_9: return PNTR_APP_KEY_9;
        //case RETROK_COLON: return PNTR_APP_KEY_COLON;
        case RETROK_SEMICOLON: return PNTR_APP_KEY_SEMICOLON;
        case RETROK_LESS: return PNTR_APP_KEY_MINUS;
        case RETROK_EQUALS: return PNTR_APP_KEY_EQUAL;
        //case RETROK_GREATER: return PNTR_APP_KEY_GREATER;
        //case RETROK_QUESTION: return PNTR_APP_KEY_QUESTION;
        //case RETROK_AT: return PNTR_APP_KEY_AT;
        case RETROK_LEFTBRACKET: return PNTR_APP_KEY_LEFT_BRACKET;
        case RETROK_BACKSLASH: return PNTR_APP_KEY_BACKSLASH;
        case RETROK_RIGHTBRACKET: return PNTR_APP_KEY_RIGHT_BRACKET;
        //case RETROK_CARET: return PNTR_APP_KEY_CARET;
        //case RETROK_UNDERSCORE: return PNTR_APP_KEY_UNDERSCORE;
        //case RETROK_BACKQUOTE: return PNTR_APP_KEY_BACKQUOTE;
        case RETROK_a: return PNTR_APP_KEY_A;
        case RETROK_b: return PNTR_APP_KEY_B;
        case RETROK_c: return PNTR_APP_KEY_C;
        case RETROK_d: return PNTR_APP_KEY_D;
        case RETROK_e: return PNTR_APP_KEY_E;
        case RETROK_f: return PNTR_APP_KEY_F;
        case RETROK_g: return PNTR_APP_KEY_G;
        case RETROK_h: return PNTR_APP_KEY_H;
        case RETROK_i: return PNTR_APP_KEY_I;
        case RETROK_j: return PNTR_APP_KEY_J;
        case RETROK_k: return PNTR_APP_KEY_K;
        case RETROK_l: return PNTR_APP_KEY_L;
        case RETROK_m: return PNTR_APP_KEY_M;
        case RETROK_n: return PNTR_APP_KEY_N;
        case RETROK_o: return PNTR_APP_KEY_O;
        case RETROK_p: return PNTR_APP_KEY_P;
        case RETROK_q: return PNTR_APP_KEY_Q;
        case RETROK_r: return PNTR_APP_KEY_R;
        case RETROK_s: return PNTR_APP_KEY_S;
        case RETROK_t: return PNTR_APP_KEY_T;
        case RETROK_u: return PNTR_APP_KEY_U;
        case RETROK_v: return PNTR_APP_KEY_V;
        case RETROK_w: return PNTR_APP_KEY_W;
        case RETROK_x: return PNTR_APP_KEY_X;
        case RETROK_y: return PNTR_APP_KEY_Y;
        case RETROK_z: return PNTR_APP_KEY_Z;
        case RETROK_LEFTBRACE: return PNTR_APP_KEY_LEFT_BRACKET;
        //case RETROK_BAR: return PNTR_APP_KEY_BAR;
        case RETROK_RIGHTBRACE: return PNTR_APP_KEY_RIGHT_BRACKET;
        case RETROK_TILDE: return PNTR_APP_KEY_GRAVE_ACCENT;
        case RETROK_DELETE: return PNTR_APP_KEY_DELETE;
        case RETROK_KP0: return PNTR_APP_KEY_KP_0;
        case RETROK_KP1: return PNTR_APP_KEY_KP_1;
        case RETROK_KP2: return PNTR_APP_KEY_KP_2;
        case RETROK_KP3: return PNTR_APP_KEY_KP_3;
        case RETROK_KP4: return PNTR_APP_KEY_KP_4;
        case RETROK_KP5: return PNTR_APP_KEY_KP_5;
        case RETROK_KP6: return PNTR_APP_KEY_KP_6;
        case RETROK_KP7: return PNTR_APP_KEY_KP_7;
        case RETROK_KP8: return PNTR_APP_KEY_KP_8;
        case RETROK_KP9: return PNTR_APP_KEY_KP_9;
        case RETROK_KP_PERIOD: return PNTR_APP_KEY_KP_DECIMAL;
        case RETROK_KP_DIVIDE: return PNTR_APP_KEY_KP_DIVIDE;
        case RETROK_KP_MULTIPLY: return PNTR_APP_KEY_KP_MULTIPLY;
        case RETROK_KP_MINUS: return PNTR_APP_KEY_KP_SUBTRACT;
        case RETROK_KP_PLUS: return PNTR_APP_KEY_KP_ADD;
        case RETROK_KP_ENTER: return PNTR_APP_KEY_KP_ENTER;
        case RETROK_KP_EQUALS: return PNTR_APP_KEY_KP_EQUAL;
        case RETROK_UP: return PNTR_APP_KEY_UP;
        case RETROK_DOWN: return PNTR_APP_KEY_DOWN;
        case RETROK_RIGHT: return PNTR_APP_KEY_RIGHT;
        case RETROK_LEFT: return PNTR_APP_KEY_LEFT;
        case RETROK_INSERT: return PNTR_APP_KEY_INSERT;
        case RETROK_HOME: return PNTR_APP_KEY_HOME;
        case RETROK_END: return PNTR_APP_KEY_END;
        case RETROK_PAGEUP: return PNTR_APP_KEY_PAGE_UP;
        case RETROK_PAGEDOWN: return PNTR_APP_KEY_PAGE_DOWN;
        case RETROK_F1: return PNTR_APP_KEY_F1;
        case RETROK_F2: return PNTR_APP_KEY_F2;
        case RETROK_F3: return PNTR_APP_KEY_F3;
        case RETROK_F4: return PNTR_APP_KEY_F4;
        case RETROK_F5: return PNTR_APP_KEY_F5;
        case RETROK_F6: return PNTR_APP_KEY_F6;
        case RETROK_F7: return PNTR_APP_KEY_F7;
        case RETROK_F8: return PNTR_APP_KEY_F8;
        case RETROK_F9: return PNTR_APP_KEY_F9;
        case RETROK_F10: return PNTR_APP_KEY_F10;
        case RETROK_F11: return PNTR_APP_KEY_F11;
        case RETROK_F12: return PNTR_APP_KEY_F12;
        case RETROK_F13: return PNTR_APP_KEY_F13;
        case RETROK_F14: return PNTR_APP_KEY_F14;
        case RETROK_F15: return PNTR_APP_KEY_F15;
        case RETROK_NUMLOCK: return PNTR_APP_KEY_NUM_LOCK;
        case RETROK_CAPSLOCK: return PNTR_APP_KEY_CAPS_LOCK;
        case RETROK_SCROLLOCK: return PNTR_APP_KEY_SCROLL_LOCK;
        case RETROK_RSHIFT: return PNTR_APP_KEY_RIGHT_SHIFT;
        case RETROK_LSHIFT: return PNTR_APP_KEY_LEFT_SHIFT;
        case RETROK_RCTRL: return PNTR_APP_KEY_RIGHT_CONTROL;
        case RETROK_LCTRL: return PNTR_APP_KEY_LEFT_CONTROL;
        case RETROK_RALT: return PNTR_APP_KEY_RIGHT_ALT;
        case RETROK_LALT: return PNTR_APP_KEY_LEFT_ALT;
        // case RETROK_RMETA: return PNTR_APP_KEY_RMETA;
        // case RETROK_LMETA: return PNTR_APP_KEY_LMETA;
        // case RETROK_LSUPER: return PNTR_APP_KEY_LSUPER;
        // case RETROK_RSUPER: return PNTR_APP_KEY_RSUPER;
    }

    return PNTR_APP_KEY_INVALID;
}

static void fallback_log(enum retro_log_level level, const char *fmt, ...) {
    (void)level;
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
}

#ifndef PNTR_APP_LOG
    void pntr_app_libretro_log(pntr_app_log_type type, const char* message) {
        #ifdef NDEBUG
        if (type == PNTR_APP_LOG_DEBUG) {
            return;
        }
        #endif

        enum retro_log_level logLevel;
        switch (type) {
            case PNTR_APP_LOG_INFO: logLevel = RETRO_LOG_INFO; break;
            case PNTR_APP_LOG_WARNING: logLevel = RETRO_LOG_WARN; break;
            case PNTR_APP_LOG_ERROR: logLevel = RETRO_LOG_ERROR; break;
            case PNTR_APP_LOG_DEBUG: logLevel = RETRO_LOG_INFO; break;
        }

        if (log_cb != NULL) {
            log_cb(logLevel, "%s\n", message);
        }
        else {
            fallback_log(logLevel, "%s\n", message);
        }
    }
    #define PNTR_APP_LOG pntr_app_libretro_log
#endif

void retro_init(void) {
    // Nothing.
}

void retro_deinit(void) {
    // Nothing.
}

unsigned retro_api_version(void) {
    return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
    log_cb(RETRO_LOG_INFO, "Plugging device %u into port %u.\n", device, port);
}

void retro_get_system_info(struct retro_system_info *info) {
    if (info == NULL) {
        return;
    }

    memset(info, 0, sizeof(*info));

    // Get the library name for the application.
    if (pntr_app_libretro == NULL) {
        char* argv[1];
        argv[0] = "pntr_app";
        pntr_app app = PNTR_APP_MAIN(1, argv);
        info->library_name = app.title;
        info->valid_extensions = app.extensions;
    }
    else if (pntr_app_libretro->title != NULL) {
        info->library_name = pntr_app_libretro->title;
        info->valid_extensions = pntr_app_libretro->extensions;
    }
    else {
        info->library_name = "pntr_app";
        info->valid_extensions = NULL;
    }

    // Grab a version from the application.
    #ifndef PROJECT_VERSION
        #define PROJECT_VERSION "0.0.1"
    #endif
    #ifndef GIT_VERSION
        #define GIT_VERSION ""
    #endif
    info->library_version  = PROJECT_VERSION GIT_VERSION;
    info->need_fullpath    = false;
}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

retro_environment_t pntr_app_libretro_environ_cb(pntr_app* app) {
    (void)app;
    return environ_cb;
}

void retro_get_system_av_info(struct retro_system_av_info *info) {
    int fps = 60;
    unsigned int width = 640;
    unsigned int height = 480;

    if (pntr_app_libretro == NULL) {
        char* argv[2] = {
            "./pntr_app",
            NULL
        };
        pntr_app app = PNTR_APP_MAIN(1, argv);
        fps = app.fps;
        width = app.width;
        height = app.height;
    }
    else {
        fps = pntr_app_libretro->fps;
        width = (unsigned int)pntr_app_libretro->width;
        height = (unsigned int)pntr_app_libretro->height;
    }

    if (height <= 0) {
        height = 480;
    }

    if (width <= 0) {
        width = 640;
    }

    // TODO: libretro: Allow for variable framerates with FPS 0.
    info->timing = (struct retro_system_timing) {
        .fps = (fps > 0) ? (double)fps : 60,
        .sample_rate = PNTR_APP_LIBRETRO_SAMPLES,
    };
    info->geometry = (struct retro_game_geometry) {
        .base_width   = width,
        .base_height  = height,
        .max_width    = width,
        .max_height   = height,
        .aspect_ratio = (float)width / (float)height,
    };
}

void retro_set_environment(retro_environment_t cb) {
    environ_cb = cb;

    // Allow loading without any content.
    bool no_content = true;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_content);

    // Set up the logging interface.
    if (cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &logging)) {
        log_cb = logging.log;
    }
    else {
        log_cb = fallback_log;
    }

    // File System
    #if ((PNTR_LOAD_FILE == pntr_app_libretro_load_file) || (PNTR_SAVE_FILE == pntr_app_libretro_save_file))
        struct retro_vfs_interface_info vfs_interface_info;
        vfs_interface_info.required_interface_version = 1;
        vfs_interface_info.iface = NULL;
        if (cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &vfs_interface_info)) {
            vfs = vfs_interface_info.iface;
        }
        else {
            vfs = NULL;
        }
    #endif
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
    audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
    audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb) {
    input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb) {
    input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb) {
    video_cb = cb;
}

void retro_reset(void) {
    // Nothing
}

static void check_variables(void) {
     // Nothing.
}

/**
 * libretro callback; Step the audio forwards a step.
 */
void pntr_app_libretro_audio_cb() {
    pntr_app* app = (pntr_app*)pntr_app_libretro;
    if (app == NULL) {
        return;
    }

    pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
    if (platform == NULL) {
        return;
    }

    // Make sure the initial mixed buffer data is empty.
    memset(platform->audioSamples, 0, sizeof(float) * platform->audioBufferSize * 2);

    // Mix the audio into the audio batch.
    audio_mixer_mix(platform->audioSamples, platform->audioBufferSize, 1.0, false);
    convert_float_to_s16(platform->audioSamples2, platform->audioSamples, platform->audioBufferSize * 2);
    audio_batch_cb(platform->audioSamples2, platform->audioBufferSize);
}

int pntr_app_libretro_mouse_button_to_retro(pntr_app_mouse_button button) {
    switch (button) {
        case PNTR_APP_MOUSE_BUTTON_LEFT: return RETRO_DEVICE_ID_MOUSE_LEFT;
        case PNTR_APP_MOUSE_BUTTON_RIGHT: return RETRO_DEVICE_ID_MOUSE_RIGHT;
        case PNTR_APP_MOUSE_BUTTON_MIDDLE: return RETRO_DEVICE_ID_MOUSE_MIDDLE;
        default:
            return -1;
    }
}

/**
 * Converts a Pointer API coordinates to screen pixel position.
 *
 * @see RETRO_DEVICE_POINTER
 */
float pntr_app_libretro_mouse_pointer_convert(float coord, float full) {
	float max = (float)0x7fff;
	return (((coord + max) / (max * 2.0f) ) * full) + 0.5f;
}

bool pntr_app_platform_events(pntr_app* app) {
    // Tell the frontend to update its input state.
    if (app == NULL || input_poll_cb == NULL || input_state_cb == NULL) {
        return false;
    }

    // Ensure the platform is available.
    pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
    if (platform == NULL) {
        return false;
    }

    // Poll for new input states.
    input_poll_cb();

    // Prepare a pntr event to push.
    pntr_app_event event = {0};
    event.app = app;

    // Mouse Move
    if (!platform->mouseHidden) {
        // RETRO_DEVICE_POINTER
        int16_t mouseX = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
        int16_t mouseY = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
        event.mouseX = pntr_app_libretro_mouse_pointer_convert((float)mouseX, app->width);
        event.mouseY = pntr_app_libretro_mouse_pointer_convert((float)mouseY, app->height);

        if (platform->mouseX != event.mouseX || platform->mouseY != event.mouseY) {
            event.type = PNTR_APP_EVENTTYPE_MOUSE_MOVE;
            platform->mouseX = event.mouseX;
            platform->mouseY = event.mouseY;
            event.mouseWheel = 0;

            // Invoke the event.
            pntr_app_process_event(app, &event);
        }
    }
    else {
        // RETRO_DEVICE_MOUSE
        int16_t mouseDeltaX = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
        int16_t mouseDeltaY = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
        if (mouseDeltaX != 0 || mouseDeltaY != 0) {
            event.type = PNTR_APP_EVENTTYPE_MOUSE_MOVE;
            event.mouseDeltaX = mouseDeltaX;
            event.mouseDeltaY = mouseDeltaY;
            pntr_app_process_event(app, &event);
        }
    }

    // Mouse Wheel
    int16_t mouseWheelUp = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_WHEELUP);
    if (mouseWheelUp > 0) {
        event.type = PNTR_APP_EVENTTYPE_MOUSE_WHEEL;
        event.mouseWheel = 1;
        pntr_app_process_event(app, &event);
    }
    else {
        int16_t mouseWheelDown = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_WHEELDOWN);
        if (mouseWheelDown > 0) {
            event.type = PNTR_APP_EVENTTYPE_MOUSE_WHEEL;
            event.mouseWheel = -1;
            pntr_app_process_event(app, &event);
        }
    }

    // Mouse Buttons
    for (int mouseButton = PNTR_APP_MOUSE_BUTTON_FIRST; mouseButton < PNTR_APP_MOUSE_BUTTON_LAST; mouseButton++) {
        int retroButton = pntr_app_libretro_mouse_button_to_retro((pntr_app_mouse_button)mouseButton);
        if (retroButton == -1) {
            continue;
        }
        int16_t currentState = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, retroButton);
        if (platform->mouseButtonState[mouseButton] != currentState) {
            event.type = (currentState == 0) ? PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP : PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN;
            platform->mouseButtonState[mouseButton] = currentState;

            // Invoke the event.
            event.mouseButton = (pntr_app_mouse_button)mouseButton;
            pntr_app_process_event(app, &event);
        }
    }

    // Gamepad Buttons
    for (event.gamepad = 0; event.gamepad < PNTR_APP_MAX_GAMEPADS; event.gamepad++) {
        // TODO: Switch to libretro gamepad bitmasks?
        for (int button = RETRO_DEVICE_ID_JOYPAD_B; button <= RETRO_DEVICE_ID_JOYPAD_R3; button++) {
            int16_t currentState = input_state_cb(event.gamepad, RETRO_DEVICE_JOYPAD, 0, button);
            if (currentState != platform->gamepadState[event.gamepad][button]) {
                event.gamepadButton = pntr_app_libretro_gamepad_button(button);
                if (event.gamepadButton == PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
                    continue;
                }

                if (currentState) {
                    event.type = PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN;
                }
                else {
                    event.type = PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
                }

                pntr_app_process_event(app, &event);
                platform->gamepadState[event.gamepad][button] = currentState;
            }
        }
    }

    return true;
}

/**
 * Pushes the given image to the screen.
 */
bool pntr_app_platform_render(pntr_app* app) {
    if (app == NULL || app->screen == NULL) {
        return false;
    }

    // TODO(RobLoach): Switch to retro_framebuffer via RETRO_ENVIRONMENT_GET_CURRENT_SOFTWARE_FRAMEBUFFER.
    video_cb((void*)app->screen->data, app->screen->width, app->screen->height, app->screen->pitch);

    return true;
}

/**
 * Close the libretro application.
 */
void pntr_app_platform_close(pntr_app* app) {
    if (app == NULL) {
        return;
    }

    if (app->platform != NULL) {
        pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
        pntr_unload_memory(platform->audioSamples);
        pntr_unload_memory(platform->audioSamples2);
        pntr_unload_memory(platform);
        app->platform = NULL;
    }

    // Clear out the application memory.
    pntr_unload_memory(app);
    pntr_app_libretro = NULL;
}

void retro_run(void) {
    if (pntr_app_libretro == NULL) {
        return;
    }

    // Process all events.
    pntr_app_pre_events(pntr_app_libretro);
    if (pntr_app_platform_events(pntr_app_libretro) == false) {
        environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
        return;
    }

    // Update the game state.
    if (pntr_app_libretro->update != NULL) {
        if (pntr_app_libretro->update(pntr_app_libretro, pntr_app_libretro->screen) == false) {
            environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
            return;
        }
    }

    // Render the application.
    pntr_app_platform_render(pntr_app_libretro);

    // Update any core options.
    bool updated = false;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated) {
        check_variables();
    }
}

void pntr_app_libretro_keyboard_callback(bool down, unsigned keycode, uint32_t character, uint16_t key_modifiers) {
    if (pntr_app_libretro == NULL || pntr_app_libretro->event == NULL) {
        return;
    }

    // Find hte key that was pressed.
    pntr_app_key key = pntr_app_libretro_key(keycode);
    if (key == PNTR_APP_KEY_INVALID) {
        return;
    }

    pntr_app_event event;
    event.app = pntr_app_libretro;
    event.key = key;
    event.type = down ? PNTR_APP_EVENTTYPE_KEY_DOWN : PNTR_APP_EVENTTYPE_KEY_UP;
    pntr_app_libretro->event(pntr_app_libretro, &event);
}

/**
 * libretro callback; Load the labels for the input buttons.
 */
void pntr_app_libretro_init_descriptors() {
    #define PNTR_APP_LIBRETRO_GAMEPAD_DEF(num) \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "D-Pad Left" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "D-Pad Up" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "D-Pad Down" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "D-Pad Right" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Left Shoulder" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Right Shoulder" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select" }, \
		{ num, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start" },

    // TODO: Update the input descriptions to match the header
	struct retro_input_descriptor desc[] = {
        #if PNTR_APP_MAX_GAMEPADS > 0
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(0)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 1
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(1)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 2
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(2)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 3
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(3)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 4
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(4)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 5
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(5)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 6
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(6)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 7
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(7)
        #endif
        #if PNTR_APP_MAX_GAMEPADS > 8
            PNTR_APP_LIBRETRO_GAMEPAD_DEF(8)
        #endif

		{ 0 },
	};
    #undef PNTR_APP_LIBRETRO_GAMEPAD_DEF

    environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
}

/**
 * libretro callback: Indicate when the audio gets enabled or disabled.
 */
void pntr_app_libretro_audio_set_state(bool enabled) {
    pntr_app* app = pntr_app_libretro;
    if (app == NULL || app->platform == NULL) {
        return;
    }

    pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
    platform->audioEnabled = enabled;
}

bool pntr_app_platform_init(pntr_app* app) {
    if (app == NULL) {
        return false;
    }

    // Initialize the libretro platform.
    app->platform = pntr_load_memory(sizeof(pntr_app_libretro_platform));
    if (app->platform == NULL) {
        return false;
    }

    // Make sure the platform has clear data.
    memset(app->platform, 0, sizeof(pntr_app_libretro_platform));

    pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
    platform->audioBufferSize = PNTR_APP_LIBRETRO_SAMPLES / ((app->fps <= 0) ? 60 : app->fps);
    platform->audioSamples = (float*)pntr_load_memory(sizeof(float) * platform->audioBufferSize * 2);
    platform->audioSamples2 = (int16_t*)pntr_load_memory(sizeof(int16_t) * platform->audioBufferSize * 2);
    pntr_app_libretro = app;

    // Random Number Generator
    pntr_app_random_set_seed(app, (uint64_t)time(NULL));

    return true;
}

/**
 * Initialize a pntr_app object.
 */
pntr_app* pntr_app_libretro_load_app(pntr_app* baseApp) {
    // Copy the data to the core's app instance.
    pntr_app* app = (pntr_app*)pntr_load_memory(sizeof(pntr_app));
    if (app == NULL) {
        return NULL;
    }

    if (baseApp != NULL) {
        pntr_memory_copy(app, baseApp, sizeof(pntr_app));
    }

    return app;
}

void pntr_app_libretro_frame_time_cb(retro_usec_t usec) {
    if (pntr_app_libretro == NULL) {
        return;
    }

    pntr_app_libretro->deltaTime = usec / 1000000.0f;
    pntr_app_update_fps(pntr_app_libretro);
}

bool retro_load_game(const struct retro_game_info *info) {
    // Pixel Format
    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
        log_cb(RETRO_LOG_ERROR, "[pntr] XRGB8888 is not supported\n");
        return false;
    }

    // Keyboard callbacks
    struct retro_keyboard_callback keyboardCallback;
    keyboardCallback.callback = pntr_app_libretro_keyboard_callback;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &keyboardCallback)) {
        log_cb(RETRO_LOG_WARN, "[pntr] Failed to set keyboard callback\n");
    }

    // Set the audio callback.
	struct retro_audio_callback retro_audio = { pntr_app_libretro_audio_cb, pntr_app_libretro_audio_set_state };
	if (!environ_cb(RETRO_ENVIRONMENT_SET_AUDIO_CALLBACK, &retro_audio)) {
        log_cb(RETRO_LOG_WARN, "[pntr] Failed to set audio callback\n");
    }

    // Build the command line arguments.
    int argc = 1;
    char* argv[3] = {
        "./pntr_app",
        info != NULL ? (char*)info->path : NULL,
        NULL
    };
    if (info != NULL && info->path != NULL) {
        argc++;
    }

    // Get the pntr_app definition.
    pntr_app application = PNTR_APP_MAIN(argc, argv);

    // Create a fresh instance from it with all the primed data.
    pntr_app* app = pntr_app_libretro_load_app(&application);
    if (app == NULL) {
        return false;
    }

    // Set up the command line argument file data.
    app->argFileData = info != NULL ? (char*)info->data : NULL;
    app->argFileDataSize = info != NULL ? (unsigned int)info->size : 0;
    app->argFileDataDoNotUnload = true; // libretro owns this data

    // Set up the frame time callback.
    struct retro_frame_time_callback retro_frame_time;
    retro_frame_time.callback = pntr_app_libretro_frame_time_cb;
    if (app->fps < 1) {
        app->fps = 60; // TODO: libretro: Allow frame independent time.
    }
    retro_frame_time.reference = 1000000 / app->fps;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &retro_frame_time)) {
        log_cb(RETRO_LOG_INFO, "[pntr] Failed to set frame time callback.\n");
    }

    // Initialize the libretro platform.
    if (!pntr_app_init(app, argc, argv)) {
        pntr_app_platform_close(app);
        return NULL;
    }

    // Update the input button descriptions.
    pntr_app_libretro_init_descriptors();

    // Update any core options.
    check_variables();

    return true;
}

void retro_unload_game(void) {
    if (pntr_app_libretro == NULL) {
        return;
    }

    pntr_app_close(pntr_app_libretro);
}

unsigned retro_get_region(void) {
    return RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num) {
    (void)type;
    (void)num;
    return retro_load_game(info);
}

size_t retro_serialize_size(void) {
    return 4096; // PNTR_APP_SAVE_SIZE;
}

bool retro_serialize(void *data, size_t size) {
    if (pntr_app_libretro == NULL || size < retro_serialize_size()) {
        return false;
    }

    pntr_app_event event;
    event.type = PNTR_APP_EVENTTYPE_SAVE;
    event.save = data;
    event.save_size = size;
    pntr_app_process_event(pntr_app_libretro, &event);

    return true;
}

bool retro_unserialize(const void *data, size_t size) {
    if (pntr_app_libretro == NULL || size < retro_serialize_size()) {
        return false;
    }

    pntr_app_event event;
    event.type = PNTR_APP_EVENTTYPE_LOAD;
    event.save = (void*)data;
    event.save_size = size;
    pntr_app_process_event(pntr_app_libretro, &event);

    return true;
}

void *retro_get_memory_data(unsigned id) {
    (void)id;
    return NULL;
}

size_t retro_get_memory_size(unsigned id) {
    (void)id;
    return 0;
}

void retro_cheat_reset(void) {
    // Nothing.
}

void retro_cheat_set(unsigned index, bool enabled, const char *code) {
    if (!enabled || pntr_app_libretro == NULL) {
        return;
    }

    pntr_app_event event;
    event.type = PNTR_APP_EVENTTYPE_CHEAT;
    event.cheat = code;
    pntr_app_process_event(pntr_app_libretro, &event);
}

#ifndef PNTR_APP_SHOW_MOUSE
    bool pntr_app_platform_show_mouse(pntr_app* app, bool show) {
        if (app == NULL || app->platform == NULL) {
            return false;
        }

        pntr_app_libretro_platform* platform = (pntr_app_libretro_platform*)app->platform;
        platform->mouseHidden = !show;
        return true;
    }
    #define PNTR_APP_SHOW_MOUSE pntr_app_platform_show_mouse
#endif

#ifndef PNTR_APP_INIT_AUDIO
#define PNTR_APP_INIT_AUDIO pntr_app_libretro_init_audio
void pntr_app_libretro_init_audio(pntr_app* app) {
    audio_mixer_init(PNTR_APP_LIBRETRO_SAMPLES);
}
#endif

#ifndef PNTR_APP_CLOSE_AUDIO
#define PNTR_APP_CLOSE_AUDIO pntr_app_libretro_close_audio
void pntr_app_libretro_close_audio(pntr_app* app) {
    audio_mixer_done();
}
#endif

#ifndef PNTR_APP_LOAD_SOUND_FROM_MEMORY
#define PNTR_APP_LOAD_SOUND_FROM_MEMORY pntr_app_platform_load_sound_from_memory
pntr_sound* pntr_app_platform_load_sound_from_memory(pntr_app_sound_type type, unsigned char* data, unsigned int dataSize) {
    if (type == PNTR_APP_SOUND_TYPE_UNKNOWN) {
        return pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    if (pntr_app_libretro == NULL) {
        // libretro needs to be initialized before usage.
        return pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
    }

    // Load the sound.
    audio_mixer_sound_t* sound = NULL;
    switch (type) {
        case PNTR_APP_SOUND_TYPE_WAV:
            sound = audio_mixer_load_wav(data, dataSize, "audio", RESAMPLER_QUALITY_DONTCARE);

            // File data isn't required anymore for wavs.
            pntr_unload_file(data);
            data = NULL;
            break;
        case PNTR_APP_SOUND_TYPE_OGG:
            sound = audio_mixer_load_ogg(data, dataSize);
            break;
    }

    if (sound == NULL) {
        log_cb(RETRO_LOG_INFO, "[pntr] Failed to load audio data%s\n");
        pntr_unload_file(data);
        return NULL;
    }

    pntr_sound_libretro* output = (pntr_sound_libretro*)pntr_load_memory(sizeof(pntr_sound_libretro));
    if (output == NULL) {
        pntr_unload_file(data);
        audio_mixer_destroy(sound);
        return NULL;
    }

    output->sound = sound;
    sound->user_data = (void*)output;
    output->voice = NULL;
    output->volume = 1.0f;
    output->playing = false;

    return (pntr_sound*)output;
}
#endif

#ifndef PNTR_APP_UNLOAD_SOUND
#define PNTR_APP_UNLOAD_SOUND(sound) pntr_app_libretro_unload_sound(sound)
void pntr_app_libretro_unload_sound(pntr_sound* sound) {
    pntr_sound_libretro* audio = (pntr_sound_libretro*)sound;
    pntr_stop_sound(sound);
    audio_mixer_destroy(audio->sound);
    audio->sound = NULL;
    audio->voice = NULL;
    pntr_unload_memory(audio);
}
#endif

#ifndef PNTR_APP_PLAY_SOUND

void pntr_app_libretro_sound_stop_cb(audio_mixer_sound_t* sound, unsigned reason) {
    if (sound == NULL || sound->user_data == NULL) {
        return;
    }
    pntr_sound_libretro* currentsound = (pntr_sound_libretro*)sound->user_data;
    switch (reason) {
        case AUDIO_MIXER_SOUND_FINISHED:
        case AUDIO_MIXER_SOUND_STOPPED:
            currentsound->playing = false;
            currentsound->voice = NULL;
            break;
        case AUDIO_MIXER_SOUND_REPEATED:
            currentsound->playing = true;
            break;
    }
}

#define PNTR_APP_PLAY_SOUND(sound, loop) pntr_app_libretro_play_sound(sound, loop)
void pntr_app_libretro_play_sound(pntr_sound* sound, bool loop) {
    pntr_sound_libretro* audio = (pntr_sound_libretro*)sound;
    audio->voice = audio_mixer_play(audio->sound, loop, audio->volume, "audio", RESAMPLER_QUALITY_DONTCARE, pntr_app_libretro_sound_stop_cb);
    if (audio->voice != NULL) {
        audio->playing = true;
    }
}
#endif

#ifndef PNTR_APP_SET_VOLUME
#define PNTR_APP_SET_VOLUME(sound, volume) pntr_app_libretro_set_volume(sound, volume)
void pntr_app_libretro_set_volume(pntr_sound* sound, float volume) {
    pntr_sound_libretro* audio = (pntr_sound_libretro*)sound;
    if (audio == NULL) {
        return;
    }
    audio->volume = volume;
    if (audio->voice != NULL) {
        audio_mixer_voice_set_volume(audio->voice, volume);
	}
}
#endif

#ifndef PNTR_APP_SOUND_PLAYING
#define PNTR_APP_SOUND_PLAYING(sound) pntr_app_libretro_sound_playing(sound)
bool pntr_app_libretro_sound_playing(pntr_sound* sound) {
    pntr_sound_libretro* audio = (pntr_sound_libretro*)sound;
    return audio->playing;
}
#endif

#ifndef PNTR_APP_STOP_SOUND
#define PNTR_APP_STOP_SOUND(sound) pntr_app_libretro_stop_sound(sound)
void pntr_app_libretro_stop_sound(pntr_sound* sound) {
    pntr_sound_libretro* audio = (pntr_sound_libretro*)sound;
    audio_mixer_stop(audio->voice);
    audio->voice = NULL;
    audio->playing = false;
}
#endif

bool pntr_app_platform_update_delta_time(pntr_app* app) {
    // Nothing, using retro_frame_time_cb() instead.
    return true;
}

PNTR_APP_API void pntr_app_set_title(pntr_app* app, const char* title) {
    if (app == NULL) {
        return;
    }

    app->title = title;
}

PNTR_APP_API void pntr_app_set_icon(pntr_app* app, pntr_image* icon) {
    // Nothing.
    (void)app;
    (void)icon;
}

bool pntr_app_platform_set_size(pntr_app* app, int width, int height) {
    if (app == NULL || app->platform == NULL || width <= 0 || height <= 0) {
        return false;
    }

    struct retro_game_geometry geometry;
    geometry.base_width = width;
    geometry.base_height = height;
    geometry.max_width = width;
    geometry.max_height = height;
    geometry.aspect_ratio = (float)width / (float)height;

    if (!environ_cb) {
        return false;
    }

    if (!environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &geometry)) {
        return false;
    }

    return true;
}

#endif  // PNTR_APP_LIBRETRO_IMPLEMENTATION_ONCE
#endif  // PNTR_APP_LIBRETRO_IMPLEMENTATION
#endif  // PNTR_APP_LIBRETRO
