#ifdef PNTR_APP_WEB
#ifndef PNTR_APP_WEB_H__
#define PNTR_APP_WEB_H__

#include <emscripten.h>
#include <emscripten/html5.h>

#include "external/emscripten_clipboard.h"

typedef struct pntr_app_platform_emscripten {
    emscripten_clipboard clipboard;
} pntr_app_platform_emscripten;

#endif  // PNTR_APP_WEB_H__

#if defined(PNTR_APP_IMPLEMENTATION) && !defined(PNTR_APP_HEADER_ONLY)
#ifndef PNTR_APP_WEB_IMPLEMENTATION_ONCE
#define PNTR_APP_WEB_IMPLEMENTATION_ONCE

#define EMSCRIPTEN_CLIPBOARD_IMPLEMENTATION
#include "external/emscripten_clipboard.h"

#ifndef PNTR_APP_LOG
    #include <emscripten/console.h> // emscripten_console_log(), emscripten_console_warn(), etc.

    /**
     * Outputs to the console using emscripten's console.h.
     */
    void pntr_app_emscripten_log(pntr_app_log_type type, const char* message) {
        switch (type) {
            case PNTR_APP_LOG_INFO:
                emscripten_console_log(message);
            break;
            case PNTR_APP_LOG_WARNING:
                emscripten_console_warn(message);
            break;
            case PNTR_APP_LOG_ERROR:
                emscripten_console_error(message);
            break;
            case PNTR_APP_LOG_DEBUG:
                emscripten_dbg(message);
            break;
        }
    }
    #define PNTR_APP_LOG pntr_app_emscripten_log
#endif

#ifndef PNTR_APP_SHOW_MOUSE
    bool pntr_app_platform_show_mouse(pntr_app* app, bool show) {
        (void)app;
        if (!show) {
            return emscripten_request_pointerlock("!canvas", true) == EMSCRIPTEN_RESULT_SUCCESS;
        }
        return emscripten_exit_pointerlock() == EMSCRIPTEN_RESULT_SUCCESS;
    }
    #define PNTR_APP_SHOW_MOUSE pntr_app_platform_show_mouse
#endif

// this is cheap/simple but magic-bytes is better
// https://github.com/konsumer/emscripten_browser_sound/blob/main/browser_sound.h#L50-L64

#define PNTR_APP_LOAD_SOUND_FROM_MEMORY pntr_app_web_load_sound_from_memory
EM_JS(pntr_sound*, pntr_app_web_load_sound_from_memory, (pntr_app_sound_type type, unsigned char* dataPtr, unsigned int dataSize), {
    // Get the sound's mime type.
    let mimeType;
    switch (type) {
        case 1: mimeType = 'audio/wav'; break;
        case 2: mimeType = 'audio/ogg'; break;
        default: return 0;
    }

    const data = HEAPU8.slice(dataPtr, dataPtr + dataSize);
    const audio = new Audio();
    audio.src = URL.createObjectURL(new Blob([data], { type }));
    Module.pntr_sounds = Module.pntr_sounds || [];
    Module.pntr_sounds.push(audio);

    // Return the length instead of length - 1, as 0 or NULL is how to depict a failed load.
    return Module.pntr_sounds.length;
})

#define PNTR_APP_PLAY_SOUND pntr_app_web_play_sound
EM_JS(void, pntr_app_web_play_sound, (pntr_sound* sound, bool loop), {
    const audio = Module.pntr_sounds[sound - 1];
    if (!audio) {
        console.log('play: sound not loaded', {sound, pntr_sounds: Module.pntr_sound});
        return;
    }

    audio.loop = loop;
    audio.currentTime = 0;
    let result = audio.play();

    if (result !== undefined) {
        // If it couldn't play the audio because of the autoplay policy, try to play it again after waiting a bit.
        // https://developer.mozilla.org/en-US/docs/Web/Media/Autoplay_guide#example_handling_play_failures
        result.catch((error) => {
            if (error.name === "NotAllowedError") {
                setTimeout(function() {
                    // TODO: Figure out a clean way to handle delayed sounds with currentTime.
                    pntr_play_sound(sound, loop);
                }, 500);
            }
        });
    }
})

#define PNTR_APP_STOP_SOUND pntr_app_web_stop_sound
EM_JS(void, pntr_app_web_stop_sound, (pntr_sound* sound), {
    const audio = Module.pntr_sounds[sound - 1];
    if (audio) {
        audio.pause();
        audio.currentTime = 0;
    }
})

#define PNTR_APP_SET_VOLUME pntr_app_web_set_volume
EM_JS(void, pntr_app_web_set_volume, (pntr_sound* sound, float volume), {
    const audio = Module.pntr_sounds[sound - 1];
    if (audio) {
        audio.volume = volume;
    }
})

#define PNTR_APP_SOUND_PLAYING pntr_app_web_sound_playing
EM_JS(bool, pntr_app_web_sound_playing, (pntr_sound* sound), {
    const audio = Module.pntr_sounds[sound - 1];
    if (audio) {
        return !audio.paused;
    }
    return false;
})

#define PNTR_APP_UNLOAD_SOUND pntr_app_web_unload_sound
EM_JS(void, pntr_app_web_unload_sound, (pntr_sound* sound), {
    const audio = Module.pntr_sounds[sound - 1];
    if (audio) {
        audio.pause();
        audio.currentTime = 0;
        URL.revokeObjectURL(audio.src);
    }
})

/**
 * : Initializes the canvas context.
 *
 * @param width The desired width of the context.
 * @param height The desired height of the context.
 */
EM_JS(bool, pntr_app_platform_set_size, (pntr_app* app, int width, int height), {
    Module.canvas.width = width;
    Module.canvas.height = height;
    Module.ctx = Module.canvas.getContext('2d');
    Module.screen = Module.ctx.getImageData(0, 0, width, height);
    specialHTMLTargets["!canvas"] = Module.canvas;

    return true;
})

EM_JS(int, pntr_app_platform_get_width, (pntr_app* app), {
    return Module.canvas.width;
})

EM_JS(int, pntr_app_platform_get_height, (pntr_app* app), {
    return Module.canvas.height;
})

/**
 * Renders the given pixel data onto the emscripten canvas context.
 *
 * @param data Pointer to the pixel data.
 * @param dataSize The size of the pixel data.
 * @param width The width of the image.
 * @param height The height of the image.
 */
EM_JS(void, pntr_app_platform_render_js, (void* data, int dataSize, int width, int height), {
    Module.screen.data.set(HEAPU8.subarray(data, data + dataSize));
    Module.ctx.putImageData(Module.screen, 0, 0);
})

/**
 * Ports an emscripten gamepad button mapping to pntr.
 *
 * @see https://w3c.github.io/gamepad/#remapping
 */
pntr_app_gamepad_button pntr_app_emscripten_gamepad_button(int button) {
    // TODO: emscripten: Determine the correct gamepad mappings? This is an Xbox controller.
    // TODO: Emscripten: Adopt a "standard" mapping? https://w3c.github.io/gamepad/#remapping
    switch (button) {
        case 0: return PNTR_APP_GAMEPAD_BUTTON_A;
        case 1: return PNTR_APP_GAMEPAD_BUTTON_B;
        case 2: return PNTR_APP_GAMEPAD_BUTTON_X;
        case 3: return PNTR_APP_GAMEPAD_BUTTON_Y;
        case 4: return PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER;
        case 5: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER;
        case 6: return PNTR_APP_GAMEPAD_BUTTON_SELECT;
        case 7: return PNTR_APP_GAMEPAD_BUTTON_START;
        case 8: return PNTR_APP_GAMEPAD_BUTTON_MENU;
        case 9: return PNTR_APP_GAMEPAD_BUTTON_LEFT_THUMB;
        case 10: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_THUMB;
        case 11: return PNTR_APP_GAMEPAD_BUTTON_RIGHT_THUMB;
        case 12: return PNTR_APP_GAMEPAD_BUTTON_UP;
        case 13: return PNTR_APP_GAMEPAD_BUTTON_DOWN;
        case 14: return PNTR_APP_GAMEPAD_BUTTON_RIGHT;
        case 15: return PNTR_APP_GAMEPAD_BUTTON_LEFT;
    }

    return PNTR_APP_GAMEPAD_BUTTON_UNKNOWN;
}

/**
 * Process the given gamepad event.
 */
void pntr_app_emscripten_gamepad_event(pntr_app* app, EmscriptenGamepadEvent* ge, pntr_app_event* event) {
    // Buttons
    for (int i = 0; i < ge->numButtons; i++) {
        event->gamepadButton = pntr_app_emscripten_gamepad_button(i);
        if (event->gamepadButton != PNTR_APP_GAMEPAD_BUTTON_UNKNOWN) {
            event->type = (ge->digitalButton[i] == EM_TRUE) ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
            pntr_app_process_event(app, event);
        }
    }

    // Axis
    #define PNTR_APP_EMSCRIPTEN_GAMEPAD_AXIS_THRESHOLD 0.6
    if (ge->numAxes >= 2) {
        // Left
        event->gamepadButton = PNTR_APP_GAMEPAD_BUTTON_LEFT;
        event->type = (ge->axis[0] <= -PNTR_APP_EMSCRIPTEN_GAMEPAD_AXIS_THRESHOLD) ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
        pntr_app_process_event(app, event);

        // Right
        event->gamepadButton = PNTR_APP_GAMEPAD_BUTTON_RIGHT;
        event->type = (ge->axis[0] >= PNTR_APP_EMSCRIPTEN_GAMEPAD_AXIS_THRESHOLD) ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
        pntr_app_process_event(app, event);

        // Up
        event->gamepadButton = PNTR_APP_GAMEPAD_BUTTON_UP;
        event->type = (ge->axis[1] <= -PNTR_APP_EMSCRIPTEN_GAMEPAD_AXIS_THRESHOLD) ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
        pntr_app_process_event(app, event);

        // Down
        event->gamepadButton = PNTR_APP_GAMEPAD_BUTTON_DOWN;
        event->type = (ge->axis[1] >= PNTR_APP_EMSCRIPTEN_GAMEPAD_AXIS_THRESHOLD) ? PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN : PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP;
        pntr_app_process_event(app, event);
    }

    // TODO: Emscripten: Support Triggers on Axis 2/3, D-Pad on Axis 6/7
}

/**
 * Input: Process Gamepad events.
 *
 * @see https://emscripten.org/docs/api_reference/html5.h.html#gamepad
 */
void pntr_app_emscripten_gamepad(pntr_app* app) {
    // Ask the browser if Gamepad API is supported.
    // TODO: Cache the GamePad data so that it doesn't need to request this every frame.
    EMSCRIPTEN_RESULT res = emscripten_sample_gamepad_data();
    if (res != EMSCRIPTEN_RESULT_SUCCESS) {
        return;
    }

    // Loop through every available gamepad.
    pntr_app_event event;
    event.app = app;
    int numGamepads =  emscripten_get_num_gamepads();
    for (event.gamepad = 0; event.gamepad < numGamepads && event.gamepad < PNTR_APP_MAX_GAMEPADS; event.gamepad++) {
        EmscriptenGamepadEvent ge;

        // Get the active state from the gamepad.
        if (emscripten_get_gamepad_status(event.gamepad, &ge) != EMSCRIPTEN_RESULT_SUCCESS) {
            continue;
        }

        // Process the gamepad events for the given gamepad.
        pntr_app_emscripten_gamepad_event(app, &ge, &event);
    }
}

bool pntr_app_platform_events(pntr_app* app) {
    // Most emscripten events are handled through callbacks, except for Gamepads.
    pntr_app_emscripten_gamepad(app);

    return true;
}

bool pntr_app_platform_render(pntr_app* app) {
    if (app == NULL || app->screen == NULL) {
        return false;
    }

    pntr_app_platform_render_js((void*)app->screen->data, app->screen->pitch * app->screen->height, app->screen->width, app->screen->height);
    return true;
}

pntr_app_key pntr_app_emscripten_key_from_event(const struct EmscriptenKeyboardEvent *keyEvent) {
    // TODO: emscripten: which/keyCode is deprecated? Do some string checkings instead.
    switch (keyEvent->which) {
        case 13: return PNTR_APP_KEY_ENTER;
        case 39: return PNTR_APP_KEY_RIGHT;
        case 38: return PNTR_APP_KEY_UP;
        case 37: return PNTR_APP_KEY_LEFT;
        case 40: return PNTR_APP_KEY_DOWN;
        case 16: return PNTR_APP_KEY_LEFT_SHIFT;
        case 17: return PNTR_APP_KEY_LEFT_CONTROL;
        case 18: return PNTR_APP_KEY_LEFT_ALT;
        case 9: return PNTR_APP_KEY_TAB;
        case 192: return PNTR_APP_KEY_GRAVE_ACCENT;
        case 96: return PNTR_APP_KEY_KP_0;
        case 97: return PNTR_APP_KEY_KP_1;
        case 98: return PNTR_APP_KEY_KP_2;
        case 99: return PNTR_APP_KEY_KP_3;
        case 100: return PNTR_APP_KEY_KP_4;
        case 101: return PNTR_APP_KEY_KP_5;
        case 102: return PNTR_APP_KEY_KP_6;
        case 103: return PNTR_APP_KEY_KP_7;
        case 104: return PNTR_APP_KEY_KP_8;
        case 105: return PNTR_APP_KEY_KP_9;
        case 173: return PNTR_APP_KEY_MINUS;
        case 61: return PNTR_APP_KEY_EQUAL;
        case 220: return PNTR_APP_KEY_BACKSLASH;
        case 219: return PNTR_APP_KEY_LEFT_BRACKET;
        case 221: return PNTR_APP_KEY_RIGHT_BRACKET;
        case 222: return PNTR_APP_KEY_APOSTROPHE;
        case 191: return PNTR_APP_KEY_SLASH;
        case 190: return PNTR_APP_KEY_PERIOD;
        case 188: return PNTR_APP_KEY_COMMA;
        case 93: return PNTR_APP_KEY_MENU;
        case 111: return PNTR_APP_KEY_KP_DIVIDE;
        case 106: return PNTR_APP_KEY_KP_MULTIPLY;
        case 109: return PNTR_APP_KEY_KP_SUBTRACT;
        case 107: return PNTR_APP_KEY_KP_ADD;
        case 112: return PNTR_APP_KEY_F1;
        case 113: return PNTR_APP_KEY_F2;
        case 114: return PNTR_APP_KEY_F3;
        case 115: return PNTR_APP_KEY_F4;
        case 116: return PNTR_APP_KEY_F5;
        case 117: return PNTR_APP_KEY_F6;
        case 118: return PNTR_APP_KEY_F7;
        case 119: return PNTR_APP_KEY_F8;
        case 120: return PNTR_APP_KEY_F9;
        case 121: return PNTR_APP_KEY_F10;
        case 122: return PNTR_APP_KEY_F11;
        case 123: return PNTR_APP_KEY_F12;
        case 144: return PNTR_APP_KEY_NUM_LOCK;
        case 110: return PNTR_APP_KEY_KP_DECIMAL;
    }

    return keyEvent->which;
}

EM_BOOL pntr_app_emscripten_key(int eventType, const struct EmscriptenKeyboardEvent *keyEvent, void *userData) {
    pntr_app* app = (pntr_app*)userData;
    if (app == NULL || app->event == NULL) {
        return EM_FALSE;
    }

    // Build the key event.
    pntr_app_event event;
    event.app = app;
    event.type = (eventType == EMSCRIPTEN_EVENT_KEYDOWN) ? PNTR_APP_EVENTTYPE_KEY_DOWN : PNTR_APP_EVENTTYPE_KEY_UP;
    event.key = pntr_app_emscripten_key_from_event(keyEvent);

    if (event.key <= 0) {
        // Ignore the event
        return EM_FALSE;
    }

    // Invoke the event
    pntr_app_process_event(app, &event);

    // Return true as we're taking over the event.
    return EM_TRUE;
}

int pntr_app_emscripten_mouse_button_from_emscripten(unsigned short button) {
    // https://developer.mozilla.org/en-US/docs/Web/API/MouseEvent/button
    switch (button) {
        case 0: return PNTR_APP_MOUSE_BUTTON_LEFT;
        case 1: return PNTR_APP_MOUSE_BUTTON_MIDDLE;
        case 2: return PNTR_APP_MOUSE_BUTTON_RIGHT;
    }
    return PNTR_APP_MOUSE_BUTTON_UNKNOWN;
}

EM_BOOL pntr_app_emscripten_mouse_wheel(int eventType, const struct EmscriptenWheelEvent *mouseEvent, void *userData) {
    (void)eventType;
    pntr_app* app = (pntr_app*)userData;
    if (app == NULL || mouseEvent->deltaY == 0) {
        return EM_FALSE;
    }

    pntr_app_event event;
    event.app = app;
    event.type = PNTR_APP_EVENTTYPE_MOUSE_WHEEL;
    event.mouseWheel = mouseEvent->deltaY > 0 ? 1 : -1;
    pntr_app_process_event(app, &event);

    return EM_TRUE;
}

EM_JS(void, pntr_app_emscripten_set_app, (void* app), {
    Module.pntr_app = app;
})

EM_BOOL pntr_app_emscripten_mouse(int eventType, const struct EmscriptenMouseEvent *mouseEvent, void *userData) {
    pntr_app* app = (pntr_app*)userData;
    if (app == NULL) {
        return EM_FALSE;
    }

    // Build the key event.
    pntr_app_event event = {0};
    event.app = app;
    switch (eventType) {
        case EMSCRIPTEN_EVENT_MOUSEDOWN: event.type = PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN; break;
        case EMSCRIPTEN_EVENT_MOUSEUP: event.type = PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP; break;
        case EMSCRIPTEN_EVENT_MOUSEMOVE: event.type = PNTR_APP_EVENTTYPE_MOUSE_MOVE; break;
        default: {
            return EM_FALSE;
        }
    }

    switch (event.type) {
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN:
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP: {
            event.mouseButton = pntr_app_emscripten_mouse_button_from_emscripten(mouseEvent->button);
            if (event.mouseButton != PNTR_APP_MOUSE_BUTTON_UNKNOWN) {
                pntr_app_process_event(app, &event);
            }
        }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_MOVE: {
            event.mouseX = (float)mouseEvent->targetX / (float)pntr_app_platform_get_width(app) * (float)app->width;
            event.mouseY = (float)mouseEvent->targetY / (float)pntr_app_platform_get_height(app) * (float)app->height;
            pntr_app_process_event(app, &event);
        }
        break;
        default: {
            return EM_FALSE;
        }
    }

    return EM_TRUE;
}

/**
 * @see https://stackoverflow.com/questions/69935188/open-a-file-in-emscripten-using-browser-file-selector-dialogue
 */
EMSCRIPTEN_KEEPALIVE int pntr_app_emscripten_file_dropped(void* app, const char* fileName, void *buffer, size_t size) {
  if (!pntr_save_file(fileName, buffer, size)) {
    pntr_app_log(PNTR_APP_LOG_ERROR, "[pntr_app] Failed to save file");
    return 0;
  }

  pntr_app_event event;
  event.app = app;
  event.type = PNTR_APP_EVENTTYPE_FILE_DROPPED;
  event.fileDropped = fileName;
  pntr_app_process_event(app, &event);

  return 1;
}

EMSCRIPTEN_KEEPALIVE void* pntr_app_emscripten_load_memory(size_t size) {
    return pntr_load_memory(size);
}

EMSCRIPTEN_KEEPALIVE void pntr_app_emscripten_unload_memory(void* ptr) {
    pntr_unload_memory(ptr);
}

EMSCRIPTEN_KEEPALIVE void pntr_app_emscripten_load_state(void* app) {
    pntr_app_event event;
    event.type = PNTR_APP_EVENTTYPE_LOAD;
    pntr_app_manual_save_load_data((pntr_app*)app, &event, PNTR_APP_SAVE_FILENAME);
}

EMSCRIPTEN_KEEPALIVE void pntr_app_emscripten_save_state(void* app) {
    pntr_app_event event;
    event.type = PNTR_APP_EVENTTYPE_SAVE;
    pntr_app_manual_save_load_data((pntr_app*)app, &event, PNTR_APP_SAVE_FILENAME);
}

EM_JS(void, pntr_app_emscripten_init_filedropped, (void* app), {
    const stringToNewUTF8Local = s => {
        const buff_ptr = Module._pntr_app_emscripten_load_memory(s.length+1);
        Module.HEAPU8.set((new TextEncoder()).encode(s + '\0'), buff_ptr);
        return buff_ptr;
    };
    Module.canvas.addEventListener('dragover', e => e.preventDefault());
    Module.canvas.addEventListener('drop', e => {
        e.preventDefault();
        for (const file of e.dataTransfer.files) {
            const reader = new FileReader();
            reader.addEventListener('load', e => {
                const bytes = new Uint8Array(event.target.result);
                const data_ptr = Module._pntr_app_emscripten_load_memory(bytes.byteLength);
                Module.HEAPU8.set(bytes, data_ptr);
                Module._pntr_app_emscripten_file_dropped(app, stringToNewUTF8Local(file.name), data_ptr, bytes.byteLength);
                Module._pntr_app_emscripten_unload_memory(data_ptr);
            });
            reader.readAsArrayBuffer(file);
        }
    });
})

/**
 * pntr_app_emscripten_get_time: Retrieves the high performance timer.
 */
EM_JS(unsigned int, pntr_app_emscripten_get_time, (void), {
    return performance.now();
})

bool pntr_app_platform_init(pntr_app* app) {
    if (app == NULL) {
        return false;
    }

    pntr_app_platform_emscripten* platform = pntr_load_memory(sizeof(pntr_app_platform_emscripten));
    if (platform == NULL) {
        return false;
    }
    app->platform = (void*)platform;

    // Initialize the context
    pntr_app_platform_set_size(app, app->width, app->height);

    // Window title
    pntr_app_set_title(app, app->title);

    // Keyboard
    emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, app, true, pntr_app_emscripten_key);
    emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, app, true, pntr_app_emscripten_key);

    // Mouse
    emscripten_set_mousedown_callback("!canvas", app, true, pntr_app_emscripten_mouse);
    emscripten_set_mouseup_callback("!canvas", app, true, pntr_app_emscripten_mouse);
    emscripten_set_mousemove_callback("!canvas", app, true, pntr_app_emscripten_mouse);
    emscripten_set_wheel_callback("!canvas", app, true, pntr_app_emscripten_mouse_wheel);

    // File Drop
    pntr_app_emscripten_init_filedropped((void*)app);

    // Timer
    app->deltaTime = 0;
    app->deltaTimeCounter = pntr_app_emscripten_get_time();

    // Random Number Generator
    pntr_app_random_set_seed(app, (uint64_t)(emscripten_random() * (float)PRAND_RAND_MAX));

    // Intialize the clipboard
    emscripten_clipboard_init(&platform->clipboard);

    // Set the global application state.
    pntr_app_emscripten_set_app(app);

    return true;
}

void pntr_app_platform_close(pntr_app* app) {
    if (app == NULL) {
        return;
    }

    if (app->platform != NULL) {
        pntr_unload_memory(app->platform);
        app->platform = NULL;
    }

    // TODO: Close the context, and delete the canvas.
}

bool pntr_app_platform_update_delta_time(pntr_app* app) {
    if (app == NULL) {
        return false;
    }

    unsigned int now = pntr_app_emscripten_get_time();
    unsigned int delta = now - app->deltaTimeCounter;

    // Check if it's time to run the update.
    if (app->fps <= 0 || ((int)delta >= (1000 / app->fps))) {
        app->deltaTimeCounter = now;
        app->deltaTime = (float)delta / 1000.0f;
        return true;
    }

    // Not time to run an update yet.
    return false;
}

PNTR_APP_API void pntr_app_set_icon(pntr_app* app, pntr_image* icon) {
    (void)app;
    (void)icon;
    // TODO: Add base64 version of the icon.
    // <link href="data:image/x-icon;base64,BASE64STRINGHERE" rel="icon" type="image/x-icon" />
}

void pntr_app_set_title(pntr_app* app, const char* title) {
    if (app != NULL) {
        app->title = title;
    }

    emscripten_set_window_title(title);
}

#ifndef PNTR_APP_CLIPBOARD
    const char* pntr_app_platform_clipboard(pntr_app* app) {
        if (app == NULL || app->platform == NULL) {
            return NULL;
        }

        pntr_app_platform_emscripten* platform = (pntr_app_platform_emscripten*)app->platform;
        const char* text = emscripten_clipboard_get(&platform->clipboard);

        if (text == NULL || text[0] == '\0') {
            return NULL;
        }

        int length = strlen(text);
        char* output = pntr_load_memory(length + 1);
        if (output == NULL) {
            return NULL;
        }

        memcpy((void*)output, text, length);
        output[length] = '\0';
        return output;
    }
    #define PNTR_APP_CLIPBOARD pntr_app_platform_clipboard
#endif

#ifndef PNTR_APP_SET_CLIPBOARD
    void pntr_app_platform_set_clipboard(pntr_app* app, const char* text) {
        if (app == NULL || app->platform == NULL) {
            return;
        }

        pntr_app_platform_emscripten* platform = (pntr_app_platform_emscripten*)app->platform;
        emscripten_clipboard_set(&platform->clipboard, text);
    }
    #define PNTR_APP_SET_CLIPBOARD pntr_app_platform_set_clipboard
#endif

#endif  // PNTR_APP_WEB_IMPLEMENTATION_ONCE
#endif  // PNTR_APP_IMPLEMENTATION && !PNTR_APP_HEADER_ONLY
#endif  // PNTR_APP_WEB
