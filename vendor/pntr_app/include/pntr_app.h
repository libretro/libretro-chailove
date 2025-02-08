/**********************************************************************************************
*
*   pntr_app - Manage a pntr application for a number of different platforms.
*
*   Copyright 2023 Rob Loach (@RobLoach)
*
*   DEPENDENCIES:
*       pntr https://github.com/robloach/pntr
*
*   CONFIGURATION:
*       PNTR_APP_CLI
*       PNTR_APP_SDL
*       PNTR_APP_LIBRETRO
*       PNTR_APP_RAYLIB
*       PNTR_APP_WEB
*
*   LICENSE: zlib/libpng
*
*   pntr_app is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef PNTR_APP_H__
#define PNTR_APP_H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Platform Detection
#include "pntr_app_platform.h"

// pntr.h
#ifndef PNTR_APP_PNTR_H
    #define PNTR_APP_PNTR_H "pntr.h"
#endif
#ifdef PNTR_IMPLEMENTATION
    // The PNTR_IMPLEMENTATION is handled later on in with PNTR_APP_IMPLEMENTATION.
    #undef PNTR_IMPLEMENTATION
#endif
#include PNTR_APP_PNTR_H

#include <stdint.h> // uint64_t

// Random Number Generator
#include "external/prand.h"

#ifndef PNTR_APP_API
    #define PNTR_APP_API PNTR_API
#endif

/**
 * Key code.
 */
typedef enum pntr_app_key {
    PNTR_APP_KEY_INVALID          = 0,
    PNTR_APP_KEY_FIRST            = 32,
    PNTR_APP_KEY_SPACE            = 32,
    PNTR_APP_KEY_APOSTROPHE       = 39,  /* ' */
    PNTR_APP_KEY_COMMA            = 44,  /* , */
    PNTR_APP_KEY_MINUS            = 45,  /* - */
    PNTR_APP_KEY_PERIOD           = 46,  /* . */
    PNTR_APP_KEY_SLASH            = 47,  /* / */
    PNTR_APP_KEY_0                = 48,
    PNTR_APP_KEY_1                = 49,
    PNTR_APP_KEY_2                = 50,
    PNTR_APP_KEY_3                = 51,
    PNTR_APP_KEY_4                = 52,
    PNTR_APP_KEY_5                = 53,
    PNTR_APP_KEY_6                = 54,
    PNTR_APP_KEY_7                = 55,
    PNTR_APP_KEY_8                = 56,
    PNTR_APP_KEY_9                = 57,
    PNTR_APP_KEY_SEMICOLON        = 59,  /* ; */
    PNTR_APP_KEY_EQUAL            = 61,  /* = */
    PNTR_APP_KEY_A                = 65,
    PNTR_APP_KEY_B                = 66,
    PNTR_APP_KEY_C                = 67,
    PNTR_APP_KEY_D                = 68,
    PNTR_APP_KEY_E                = 69,
    PNTR_APP_KEY_F                = 70,
    PNTR_APP_KEY_G                = 71,
    PNTR_APP_KEY_H                = 72,
    PNTR_APP_KEY_I                = 73,
    PNTR_APP_KEY_J                = 74,
    PNTR_APP_KEY_K                = 75,
    PNTR_APP_KEY_L                = 76,
    PNTR_APP_KEY_M                = 77,
    PNTR_APP_KEY_N                = 78,
    PNTR_APP_KEY_O                = 79,
    PNTR_APP_KEY_P                = 80,
    PNTR_APP_KEY_Q                = 81,
    PNTR_APP_KEY_R                = 82,
    PNTR_APP_KEY_S                = 83,
    PNTR_APP_KEY_T                = 84,
    PNTR_APP_KEY_U                = 85,
    PNTR_APP_KEY_V                = 86,
    PNTR_APP_KEY_W                = 87,
    PNTR_APP_KEY_X                = 88,
    PNTR_APP_KEY_Y                = 89,
    PNTR_APP_KEY_Z                = 90,
    PNTR_APP_KEY_LEFT_BRACKET     = 91,  /* [ */
    PNTR_APP_KEY_BACKSLASH        = 92,  /* \ */
    PNTR_APP_KEY_RIGHT_BRACKET    = 93,  /* ] */
    PNTR_APP_KEY_GRAVE_ACCENT     = 96,  /* ` */
    PNTR_APP_KEY_WORLD_1          = 161, /* non-US #1 */
    PNTR_APP_KEY_WORLD_2          = 162, /* non-US #2 */
    PNTR_APP_KEY_ESCAPE           = 256,
    PNTR_APP_KEY_ENTER            = 257,
    PNTR_APP_KEY_TAB              = 258,
    PNTR_APP_KEY_BACKSPACE        = 259,
    PNTR_APP_KEY_INSERT           = 260,
    PNTR_APP_KEY_DELETE           = 261,
    PNTR_APP_KEY_RIGHT            = 262,
    PNTR_APP_KEY_LEFT             = 263,
    PNTR_APP_KEY_DOWN             = 264,
    PNTR_APP_KEY_UP               = 265,
    PNTR_APP_KEY_PAGE_UP          = 266,
    PNTR_APP_KEY_PAGE_DOWN        = 267,
    PNTR_APP_KEY_HOME             = 268,
    PNTR_APP_KEY_END              = 269,
    PNTR_APP_KEY_CAPS_LOCK        = 280,
    PNTR_APP_KEY_SCROLL_LOCK      = 281,
    PNTR_APP_KEY_NUM_LOCK         = 282,
    PNTR_APP_KEY_PRINT_SCREEN     = 283,
    PNTR_APP_KEY_PAUSE            = 284,
    PNTR_APP_KEY_F1               = 290,
    PNTR_APP_KEY_F2               = 291,
    PNTR_APP_KEY_F3               = 292,
    PNTR_APP_KEY_F4               = 293,
    PNTR_APP_KEY_F5               = 294,
    PNTR_APP_KEY_F6               = 295,
    PNTR_APP_KEY_F7               = 296,
    PNTR_APP_KEY_F8               = 297,
    PNTR_APP_KEY_F9               = 298,
    PNTR_APP_KEY_F10              = 299,
    PNTR_APP_KEY_F11              = 300,
    PNTR_APP_KEY_F12              = 301,
    PNTR_APP_KEY_F13              = 302,
    PNTR_APP_KEY_F14              = 303,
    PNTR_APP_KEY_F15              = 304,
    PNTR_APP_KEY_F16              = 305,
    PNTR_APP_KEY_F17              = 306,
    PNTR_APP_KEY_F18              = 307,
    PNTR_APP_KEY_F19              = 308,
    PNTR_APP_KEY_F20              = 309,
    PNTR_APP_KEY_F21              = 310,
    PNTR_APP_KEY_F22              = 311,
    PNTR_APP_KEY_F23              = 312,
    PNTR_APP_KEY_F24              = 313,
    PNTR_APP_KEY_F25              = 314,
    PNTR_APP_KEY_KP_0             = 320,
    PNTR_APP_KEY_KP_1             = 321,
    PNTR_APP_KEY_KP_2             = 322,
    PNTR_APP_KEY_KP_3             = 323,
    PNTR_APP_KEY_KP_4             = 324,
    PNTR_APP_KEY_KP_5             = 325,
    PNTR_APP_KEY_KP_6             = 326,
    PNTR_APP_KEY_KP_7             = 327,
    PNTR_APP_KEY_KP_8             = 328,
    PNTR_APP_KEY_KP_9             = 329,
    PNTR_APP_KEY_KP_DECIMAL       = 330,
    PNTR_APP_KEY_KP_DIVIDE        = 331,
    PNTR_APP_KEY_KP_MULTIPLY      = 332,
    PNTR_APP_KEY_KP_SUBTRACT      = 333,
    PNTR_APP_KEY_KP_ADD           = 334,
    PNTR_APP_KEY_KP_ENTER         = 335,
    PNTR_APP_KEY_KP_EQUAL         = 336,
    PNTR_APP_KEY_LEFT_SHIFT       = 340,
    PNTR_APP_KEY_LEFT_CONTROL     = 341,
    PNTR_APP_KEY_LEFT_ALT         = 342,
    PNTR_APP_KEY_LEFT_SUPER       = 343,
    PNTR_APP_KEY_RIGHT_SHIFT      = 344,
    PNTR_APP_KEY_RIGHT_CONTROL    = 345,
    PNTR_APP_KEY_RIGHT_ALT        = 346,
    PNTR_APP_KEY_RIGHT_SUPER      = 347,
    PNTR_APP_KEY_MENU             = 348,
    PNTR_APP_KEY_LAST
} pntr_app_key;

#ifndef PNTR_APP_MAX_GAMEPADS
/**
 * The maximum number of supported gamepads
 */
#define PNTR_APP_MAX_GAMEPADS 4
#endif

/**
 * Gamepad button.
 */
typedef enum pntr_app_gamepad_button {
    PNTR_APP_GAMEPAD_BUTTON_UNKNOWN = 0,        // Unknown button, just for error checking
    PNTR_APP_GAMEPAD_BUTTON_FIRST = 1,
    PNTR_APP_GAMEPAD_BUTTON_UP = 1,             // Gamepad left DPAD up button
    PNTR_APP_GAMEPAD_BUTTON_RIGHT,              // Gamepad left DPAD right button
    PNTR_APP_GAMEPAD_BUTTON_DOWN,               // Gamepad left DPAD down button
    PNTR_APP_GAMEPAD_BUTTON_LEFT,               // Gamepad left DPAD left button
    PNTR_APP_GAMEPAD_BUTTON_Y,                  // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    PNTR_APP_GAMEPAD_BUTTON_B,                  // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    PNTR_APP_GAMEPAD_BUTTON_A,                  // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    PNTR_APP_GAMEPAD_BUTTON_X,                  // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    PNTR_APP_GAMEPAD_BUTTON_LEFT_SHOULDER,      // Gamepad top/back trigger left (first), it could be a trailing button
    PNTR_APP_GAMEPAD_BUTTON_LEFT_TRIGGER,       // Gamepad top/back trigger left (second), it could be a trailing button
    PNTR_APP_GAMEPAD_BUTTON_RIGHT_SHOULDER,     // Gamepad top/back trigger right (one), it could be a trailing button
    PNTR_APP_GAMEPAD_BUTTON_RIGHT_TRIGGER,      // Gamepad top/back trigger right (second), it could be a trailing button
    PNTR_APP_GAMEPAD_BUTTON_SELECT,             // Gamepad center buttons, left one (i.e. PS3: Select)
    PNTR_APP_GAMEPAD_BUTTON_MENU,               // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    PNTR_APP_GAMEPAD_BUTTON_START,              // Gamepad center buttons, right one (i.e. PS3: Start)
    PNTR_APP_GAMEPAD_BUTTON_LEFT_THUMB,         // Gamepad joystick pressed button left
    PNTR_APP_GAMEPAD_BUTTON_RIGHT_THUMB,        // Gamepad joystick pressed button right
    PNTR_APP_GAMEPAD_BUTTON_LAST
} pntr_app_gamepad_button;

/**
 * Mouse button.
 */
typedef enum pntr_app_mouse_button {
    PNTR_APP_MOUSE_BUTTON_UNKNOWN = 0,
    PNTR_APP_MOUSE_BUTTON_FIRST = 1,
    PNTR_APP_MOUSE_BUTTON_LEFT = 1,
    PNTR_APP_MOUSE_BUTTON_RIGHT = 2,
    PNTR_APP_MOUSE_BUTTON_MIDDLE = 3,
    PNTR_APP_MOUSE_BUTTON_LAST
} pntr_app_mouse_button;

/**
 * A list of events that are passed through pntr_app::event.
 *
 * @see pntr_app::event
 * @see pntr_app_event
 */
typedef enum pntr_app_event_type {
    PNTR_APP_EVENTTYPE_UNKNOWN = 0,
    PNTR_APP_EVENTTYPE_KEY_DOWN,
    PNTR_APP_EVENTTYPE_KEY_UP,
    PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN,
    PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP,
    PNTR_APP_EVENTTYPE_MOUSE_MOVE,
    PNTR_APP_EVENTTYPE_MOUSE_WHEEL,
    PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN,
    PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP,

    /**
     * Evoked when a file is drag and dropped onto the application.
     *
     * @see pntr_app_event::fileDropped
     */
    PNTR_APP_EVENTTYPE_FILE_DROPPED,

    /**
     * Evoked when a cheat is entered into the application.
     *
     * @see pntr_app_event::cheat
     * TODO: Add cheat support to CLI, raylib, SDL, web.
     */
    PNTR_APP_EVENTTYPE_CHEAT,

    /**
     * Evoked when the application is requested to save its current state.
     *
     * The `pntr_app_event::save` `void*` variable will point to a memory bucket where the sta
     *
     * @see pntr_app_event::save
     * @see pntr_app_event::save_size
     */
    PNTR_APP_EVENTTYPE_SAVE,

    /**
     * The application requests to load the active state from the from the `pntr_app_event::save` variable.
     *
     * The `pntr_app_event::save` `void*` variable aill point to the memory bucket where the save data is to be loaded from.
     *
     * @see pntr_app_event::save
     * @see pntr_app_event::save_size
     */
    PNTR_APP_EVENTTYPE_LOAD,
} pntr_app_event_type;

typedef enum pntr_app_sound_type {
    PNTR_APP_SOUND_TYPE_UNKNOWN = 0,
    PNTR_APP_SOUND_TYPE_WAV,
    PNTR_APP_SOUND_TYPE_OGG
} pntr_app_sound_type;

/**
 * Priority level for logging.
 *
 * @see pntr_app_log()
 */
typedef enum pntr_app_log_type {
    PNTR_APP_LOG_DEBUG = 0,
    PNTR_APP_LOG_INFO,
    PNTR_APP_LOG_WARNING,
    PNTR_APP_LOG_ERROR
} pntr_app_log_type;

typedef struct pntr_app pntr_app;

typedef struct pntr_app_event {
    pntr_app* app; /** The application associated with the event. */
    pntr_app_event_type type; /** The type of the event that has been pushed. */
    pntr_app_key key; /** With `PNTR_APP_EVENTTYPE_KEY_DOWN` or `PNTR_APP_EVENTTYPE_KEY_UP`, will determine the key that was affected. */

    // Mouse
    pntr_app_mouse_button mouseButton; /** `PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN` or `PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP` */
    float mouseX;
    float mouseY;
    float mouseDeltaX;
    float mouseDeltaY;
    int mouseWheel; /** When type is PNTR_APP_EVENTTYPE_MOUSE_WHEEL, mouseWheel will be -1 when the mouse wheel is scrolling up, and 1 when scrolling down. */

    // Gamepad
    pntr_app_gamepad_button gamepadButton;
    int gamepad;

    /**
     * Invoked when a file is drag and dropped on the application, this contains the path to the file.
     *
     * @see PNTR_APP_EVENTTYPE_DRAG_AND_DROP
     */
    const char* fileDropped;

    /**
     * Cheat code that has been entered.
     *
     * @see PNTR_APP_EVENTTYPE_CHEAT
     */
    const char* cheat;

    /**
     * The unserialized save data.
     *
     * @see PNTR_APP_EVENTTYPE_SAVE
     * @see PNTR_APP_EVENTTYPE_LOAD
     */
    void* save;

    /**
     * The size of the save data.
     *
     * @see PNTR_APP_EVENTTYPE_SAVE
     * @see PNTR_APP_EVENTTYPE_LOAD
     */
    size_t save_size;
} pntr_app_event;

/**
 * Application definition.
 */
struct pntr_app {
    int width;                      // The pixel width of the application.
    int height;                     // The pixel height of the application.
    const char* title;              // The name of the application, which will usually become the window title.
    bool (*init)(pntr_app* app);
    bool (*update)(pntr_app* app, pntr_image* screen);
    void (*close)(pntr_app* app);
    void (*event)(pntr_app* app, pntr_app_event* event);
    int fps;                        // The desired framerate. Use 0 for a variable framerate.
    int actualFPS;                  // The actual calculated FPS. @see pntr_app_fps()
    void* userData;                 // A pointer to a custom state in memory that is passed across all pntr_app callbacks.
    pntr_image* screen;             // The screen buffer to render to.
    void* platform;                 // Custom data that is specific to the platform.
    float deltaTime;                /** The amount of seconds between the previous frame and the current one. @see pntr_app_delta_time() */
    unsigned int deltaTimeCounter;  // TODO: Move deltaTimeCounter to pntr_app_web platform data.

    // Input state

    // Keyboard
    bool keysChanged;
    bool keysDown[PNTR_APP_KEY_LAST];
    bool keysDownLast[PNTR_APP_KEY_LAST];

    // Gamepad
    int gamepadButtonState[PNTR_APP_MAX_GAMEPADS];
    int gamepadButtonStatePrevious[PNTR_APP_MAX_GAMEPADS];

    // Mouse
    float mouseX;
    float mouseY;
    float mouseDeltaX;
    float mouseDeltaY;
    int mouseWheel;
    bool mouseWheelChanged;
    bool mouseChanged;
    bool mouseButtonsDown[PNTR_APP_MOUSE_BUTTON_LAST];
    bool mouseButtonsDownLast[PNTR_APP_MOUSE_BUTTON_LAST];
    bool mouseButtonsChanged;

    // Command Line Arguments
    const char* argFile; /** The first argument passed to the command line argument. @see pntr_app_load_arg_file() */
    void* argFileData; /** The file data from argFile. @see pntr_app_load_arg_file() */
    unsigned int argFileDataSize; /** The file size of the argFile. @see pntr_app_load_arg_file() */
    bool argFileDataDoNotUnload; /** When true, will indicate that argFile should NOT be unloaded on exit. @see pntr_app_load_arg_file() */

    /**
     * Random Number Generator
     *
     * @see pntr_app_random()
     * @see pntr_app_random_float()
     * @see pntr_app_random_seed()
     */
    prand_t prand;

    /**
     * The managed clipboard data.
     *
     * @see pntr_app_set_clipboard()
     * @see pntr_app_clipboard()
     */
    char* clipboard;

    /**
     * The audio system user data, if needed.
     */
    void* audioData;

    /**
     * A list of valid extensions that can be loaded with the application, seperated by a |.
     *
     * Example: txt|md
     *
     * Can be NULL.
     */
    const char* extensions;
};

typedef void pntr_sound;

/**
 * Load a sound from the given path. Supports .wav or .ogg files.
 *
 * @param fileName The filename of the sound file to load.
 *
 * @return The loaded sound, or NULL on failure.
 */
PNTR_APP_API pntr_sound* pntr_load_sound(const char* fileName);

/**
 * Load a sound from memory. Supports .wav or .ogg files.
 *
 * Will take ownership of the data and clear it when the sound is unloaded.
 *
 * @param type The type of sound that we'll be loading (PNTR_APP_SOUND_TYPE_WAV, PNTR_APP_SOUND_TYPE_WAV, etc).
 * @param data The file data.
 * @param dataSize The size of the data in memory.
 *
 * @return The loaded sound, or NULL on failure.
 * @see PNTR_APP_SOUND_TYPE_WAV
 * @see PNTR_APP_SOUND_TYPE_OGG
 */
PNTR_APP_API pntr_sound* pntr_load_sound_from_memory(pntr_app_sound_type type, unsigned char* data, unsigned int dataSize);

/**
 * Unload the given sound.
 *
 * @param sound The sound to unload.
 */
PNTR_APP_API void pntr_unload_sound(pntr_sound* sound);

/**
 * Play the given sound.
 *
 * TODO: Sounds: Add volume
 *
 * @param sound The sound to play.
 * @param loop Whether or not to loop back to the beginning when the sound finishes.
 */
PNTR_APP_API void pntr_play_sound(pntr_sound* sound, bool loop);

/**
 * Stop playing the given sound.
 *
 * @param sound The sound to stop playing.
 */
PNTR_APP_API void pntr_stop_sound(pntr_sound* sound);

/**
 * Sets the volume, or loudness, of the given sound.
 *
 * @param sound The sound to change the volume for.
 * @param volume The sound from 0.0f to 1.0f.
 */
PNTR_APP_API void pntr_set_volume(pntr_sound* sound, float volume);

/**
 * Get whether or not the given sound is actively playing.
 *
 * @param sound The sound to check if playing.
 * @return True if the sound is actively playing, false otherwise.
 */
PNTR_APP_API bool pntr_sound_playing(pntr_sound*sound);

/**
 * Get the sound type of the given file from its file path.
 */
PNTR_APP_API pntr_app_sound_type pntr_app_get_file_sound_type(const char* fileName);

/**
 * Get the user data associated with the application.
 *
 * @param app The application.
 *
 * @return A pointer to the user data associated with the application.
 */
PNTR_APP_API void* pntr_app_userdata(pntr_app* app);

/**
 * Sets the user data for the application.
 */
PNTR_APP_API void pntr_app_set_userdata(pntr_app* app, void* userData);

/**
 * Get the screen width of the application.
 */
PNTR_APP_API int pntr_app_width(pntr_app* app);

/**
 * Get the screen height of the application.
 */
PNTR_APP_API int pntr_app_height(pntr_app* app);

/**
 * Retrieves the change in time in seconds since the last update run.
 */
PNTR_APP_API float pntr_app_delta_time(pntr_app* app);

/**
 * Get the current actual FPS.
 */
PNTR_APP_API int pntr_app_fps(pntr_app* app);

/**
 * Get a random value between min and max.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 *
 * @return A random integer between the min and max.
 */
PNTR_APP_API int pntr_app_random(pntr_app* app, int min, int max);

/**
 * Get a random float value between min and max.
 *
 * @param min The minimum value.
 * @param max The maximum value.
 *
 * @return A random floatvalue between the min and max.
 */
PNTR_APP_API float pntr_app_random_float(pntr_app* app, float min, float max);

/**
 * Sets the random number generator seed.
 *
 * @note This is automatically called when the application is loading.
 *
 * @param seed The seed to use for the random number generator. If set to 0, will let the platform decide which seed to use.
 */
PNTR_APP_API void pntr_app_random_set_seed(pntr_app* app, uint64_t seed);

/**
 * Get the currently active random number generator seed.
 */
PNTR_APP_API uint64_t pntr_app_random_seed(pntr_app* app);

/**
 * Log a message.
 *
 * @param type The type of message to be logged.
 * @param message The message.
 *
 * @see pntr_app_log_type
 */
PNTR_APP_API void pntr_app_log(pntr_app_log_type type, const char* message);
PNTR_APP_API bool pntr_app_key_pressed(pntr_app* app, pntr_app_key key);
PNTR_APP_API bool pntr_app_key_down(pntr_app* app, pntr_app_key key);
PNTR_APP_API bool pntr_app_key_released(pntr_app* app, pntr_app_key key);
PNTR_APP_API bool pntr_app_key_up(pntr_app* app, pntr_app_key key);
PNTR_APP_API bool pntr_app_gamepad_button_pressed(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
PNTR_APP_API bool pntr_app_gamepad_button_down(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
PNTR_APP_API bool pntr_app_gamepad_button_released(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
PNTR_APP_API float pntr_app_mouse_x(pntr_app* app);
PNTR_APP_API float pntr_app_mouse_y(pntr_app* app);
PNTR_APP_API float pntr_app_mouse_delta_x(pntr_app* app);
PNTR_APP_API float pntr_app_mouse_delta_y(pntr_app* app);
PNTR_APP_API int pntr_app_mouse_wheel(pntr_app* app);
PNTR_APP_API bool pntr_app_mouse_button_pressed(pntr_app* app, pntr_app_mouse_button button);
PNTR_APP_API bool pntr_app_mouse_button_down(pntr_app* app, pntr_app_mouse_button button);
PNTR_APP_API bool pntr_app_mouse_button_released(pntr_app* app, pntr_app_mouse_button button);
PNTR_APP_API bool pntr_app_mouse_button_up(pntr_app* app, pntr_app_mouse_button button);
PNTR_APP_API bool pntr_app_show_mouse(pntr_app* app, bool toggle);

PNTR_APP_API void pntr_app_set_title(pntr_app* app, const char* title);
PNTR_APP_API const char* pntr_app_title(pntr_app* app);
PNTR_APP_API bool pntr_app_set_size(pntr_app* app, int width, int height);

/**
 * Sets the application's window icon.
 *
 * @param app The application to act on.
 * @param icon The icon for the image.
 */
PNTR_APP_API void pntr_app_set_icon(pntr_app* app, pntr_image* icon);

/**
 * When the application is passed a file to load through as a command line argument, this function will retrieve the associated file data.
 *
 * @note This function can only be called during or after `init()`.
 *
 * @param app The application to act on.
 * @param size A pointer to an unsigned int that will represent the size in bytes of the memory buffer.
 *
 * @return A memory buffer for the file data that was passed in. The returned memory buffer must be manually cleared with pntr_unload_file() after use.
 */
PNTR_APP_API void* pntr_app_load_arg_file(pntr_app* app, unsigned int* size);

/**
 * Set the clipboard text.
 *
 * @param app The application to act on.
 * @param text The text to set to the clipboard.
 * @param len The length of the text. Provide 0 if you're using a null-terminated string.
 */
PNTR_APP_API void pntr_app_set_clipboard(pntr_app* app, const char* text, int len);

/**
 * Get the clipboard text.
 * @param app The application to act on.
 *
 * @return The clipboard text.
 */
PNTR_APP_API const char* pntr_app_clipboard(pntr_app* app);

/**
 * Platform callback to initialize the platform.
 *
 * @param app The application to initialize.
 * @param argc The number of command line arguments passed in.
 * @param argv The arguments passed in through the command line.
 *
 * @return True if initialization was successful, false otherwise.
 *
 * @internal
 */
PNTR_APP_API bool pntr_app_init(pntr_app* app, int argc, char* argv[]);

/**
 * Initialize the platform.
 *
 * @internal
 */
PNTR_APP_API bool pntr_app_platform_init(pntr_app* app);

/**
 * Platform callback to invoke all events for the platform.
 *
 * @return True if the application should continue to run, false if the platform is requested to close.
 *
 * @internal
 */
PNTR_APP_API bool pntr_app_platform_events(pntr_app* app);

/**
 * @internal
 */
PNTR_APP_API void pntr_app_pre_events(pntr_app* app);

/**
 * @internal
 */
PNTR_APP_API void pntr_app_process_event(pntr_app* app, pntr_app_event* event);

/**
 * Platform callback to render to the screen.
 *
 * @return True if rendering was successful, false otherwise.
 *
 * @internal
 */
PNTR_APP_API bool pntr_app_platform_render(pntr_app* app);

/**
 * Close the application.
 *
 * @internal
 */
PNTR_APP_API void pntr_app_close(pntr_app* app);

/**
 * Platform callback to close the application.
 *
 * @internal
 */
PNTR_APP_API void pntr_app_platform_close(pntr_app* app);

/**
 * Asks the platform to update the delta time, and indicates if it's time to run an update.
 *
 * @return True of false depending on if it's time to run an update frame.
 *
 * @internal
 */
PNTR_APP_API bool pntr_app_platform_update_delta_time(pntr_app* app);

/**
 * @internal
 */
PNTR_APP_API bool pntr_app_platform_set_size(pntr_app* app, int width, int height);

#ifdef PNTR_ENABLE_VARGS
PNTR_APP_API void pntr_app_log_ex(pntr_app_log_type type, const char* message, ...);
#endif

/**
 * Updates the internal FPS counter.
 *
 * @see pntr_app_fps()
 * @internal
 */
void pntr_app_update_fps(pntr_app* app);

/**
 * Manually save/load the data.
 *
 * @internal
 */
void pntr_app_manual_save_load_data(pntr_app* app, pntr_app_event* event, const char* fileName);

#define PNTR_APP_HEADER_ONLY
#include "pntr_app_cli.h"
#include "pntr_app_libretro.h"
#include "pntr_app_raylib.h"
#include "pntr_app_sdl.h"
#include "pntr_app_web.h"
#undef PNTR_APP_HEADER_ONLY

#ifdef __cplusplus
}
#endif

#endif  // PNTR_APP_H__

#ifdef PNTR_APP_IMPLEMENTATION
#ifndef PNTR_APP_IMPLEMENTATION_ONCE
#define PNTR_APP_IMPLEMENTATION_ONCE

#ifndef PNTR_APP_SAVE_SIZE
    #define PNTR_APP_SAVE_SIZE 4096
#endif

#ifndef PNTR_APP_SAVE_FILENAME
    #define PNTR_APP_SAVE_FILENAME "pntr_app.save"
#endif

// Sokol Args
#define SOKOL_ASSERT(c) (void)(c)
#ifndef PNTR_APP_NO_SOKOL_ARGS_IMPL
#define SOKOL_ARGS_IMPL
#endif  // PNTR_APP_NO_SOKOL_ARGS_IMPL
#ifndef PNTR_APP_SOKOL_ARGS_H
#define PNTR_APP_SOKOL_ARGS_H "external/sokol_args.h"
#endif  // PNTR_APP_SOKOL_ARGS_H
#include PNTR_APP_SOKOL_ARGS_H

#ifndef PNTR_APP_MAIN
/**
 * The name of the entry point in your application.
 *
 * Will default to "Main".
 *
 * @code
 * #define PNTR_APP_MAIN MyOwnMain
 * #define PNTR_APP_IMPLEMENTATION
 * #include "pntr_app.h"
 *
 * pntr_app MyOwnMain(int argc, char* argv[]) {
 *   // Stuff
 * }
 * @endcode
 **/
#define PNTR_APP_MAIN Main
#endif  // PNTR_APP_MAIN

#ifdef __cplusplus
extern "C" {
#endif

pntr_app PNTR_APP_MAIN(int argc, char* argv[]);

#include "pntr_app_cli.h"
#include "pntr_app_libretro.h"
#include "pntr_app_raylib.h"
#include "pntr_app_sdl.h"
#include "pntr_app_web.h"

#ifdef __cplusplus
}
#endif

#define PNTR_IMPLEMENTATION
#include PNTR_APP_PNTR_H

#ifndef PNTR_APP_LOG
    #include <stdio.h> // printf(), sprintf()
#endif

// prand: Pseudo Random Number Generator
#define PRAND_IMPLEMENTATION
#include "external/prand.h"

#define PICO_B64_IMPLEMENTATION
#define PICO_B64_ISALNUM(c) (((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
#define PICO_B64_FLOOR(x) PNTR_FLOORF((float)x)
#define PICO_B64_CEIL(x) PNTR_CEILF((float)x)
#include "external/pico_b64.h"

/**
 * Retrieve a bit flag for the given button.
 */
#define PNTR_APP_GAMEPAD_BUTTON_FLAG(button) (1 << (button))

#ifdef __cplusplus
extern "C" {
#endif

void pntr_app_update_fps(pntr_app* app) {
    if (app->deltaTime > 0.0f) {
        // TODO: Switch to a frame counter instead?
        app->actualFPS = (int)(1.0f / app->deltaTime);
    }
}

// Whether or not the application uses int main().
#ifndef PNTR_APP_NO_ENTRY

#ifdef EMSCRIPTEN
#ifndef PNTR_APP_EMSCRIPTEN_H
#define PNTR_APP_EMSCRIPTEN_H <emscripten/emscripten.h>
#endif  // PNTR_APP_EMSCRIPTEN_H
#include PNTR_APP_EMSCRIPTEN_H

/**
 * The update callback for web.
 */
void pntr_app_emscripten_update_loop(void* application) {
    if (application == NULL) {
        emscripten_cancel_main_loop();
        return;
    }

    pntr_app* app = (pntr_app*)application;

    // Poll Events
    pntr_app_pre_events(app);
    if (!pntr_app_platform_events(app)) {
        emscripten_cancel_main_loop();
        return;
    }

    // Run the update function.
    if (pntr_app_platform_update_delta_time(app) && app->update != NULL) {
        pntr_app_update_fps(app);
        if (!app->update(app, app->screen)) {
            emscripten_cancel_main_loop();
            return;
        }
    }

    // Render
    if (!pntr_app_platform_render(app)) {
        emscripten_cancel_main_loop();
    }
}
#endif

/**
 * The main entry point of the application.
 *
 * Will call the Main() function.
 *
 * @see PNTR_APP_MAIN
 */
int main(int argc, char* argv[]) {
    pntr_app app = PNTR_APP_MAIN(argc, argv);

    if (!pntr_app_init(&app, argc, argv)) {
        return 1;
    }

    #if defined(EMSCRIPTEN)
        // Set up the main loop.
        emscripten_set_main_loop_arg(pntr_app_emscripten_update_loop, &app, 0, 1);
    #else
        do {
            // Events
            pntr_app_pre_events(&app);
            if (!pntr_app_platform_events(&app)) {
                break;
            }

            // Update callback
            if (pntr_app_platform_update_delta_time(&app) && app.update != NULL) {
                pntr_app_update_fps(&app);
                if (!app.update(&app, app.screen)) {
                    break;
                }
            }

            // Render
            if (!pntr_app_platform_render(&app)) {
                break;
            }
        } while(true);
    #endif

    // Tell the platform to close.
    pntr_app_close(&app);

    return 0;
}
#endif  // PNTR_APP_NO_ENTRY

static void* pntr_app_sokol_args_alloc(size_t size, void* user_data) {
    (void)user_data;
    return pntr_load_memory(size);
}

static void pntr_app_sokol_args_free(void* ptr, void* user_data) {
    (void)user_data;
    pntr_unload_memory(ptr);
}

PNTR_APP_API bool pntr_app_init(pntr_app* app, int argc, char* argv[]) {
    if (app == NULL) {
        return false;
    }

    // Parse the command line arguments.
    sargs_desc desc;
    desc.argc = argc,
    desc.argv = argv,
    desc.max_args = 0;
    desc.buf_size = 0;
    desc.allocator.alloc_fn = pntr_app_sokol_args_alloc;
    desc.allocator.free_fn = pntr_app_sokol_args_free;
    sargs_setup(&desc);

    // Search for the file provided.
    if (sargs_isvalid()) {
        for (int i = 0; i < sargs_num_args(); i++) {
            // The provided file is found as having an empty value.
            const char* value = sargs_value_at(i);
            if (value[0] == '\0') {
                const char* key = sargs_key_at(i);
                // Make sure it's not a flag.
                if (key != NULL && key[0] != '\0' && key[0] != '-') {
                    app->argFile = key;
                    break;
                }
            }
        }
    }

    // Initialize defaults.
    if (app->width <= 0) {
        app->width = 640;
    }

    if (app->height <= 0) {
        app->height = 360;
    }

    // Create the screen.
    app->screen = pntr_gen_image_color(app->width, app->height, PNTR_BLACK);
    if (app->screen == NULL) {
        sargs_shutdown();
        return false;
    }

    // Initialize the random number generator.
    pntr_app_random_set_seed(app, 0);

    // Initialize the platform.
    if (!pntr_app_platform_init(app)) {
        pntr_unload_image(app->screen);
        sargs_shutdown();
        return false;
    }

    // Initialize the audio system.
    #ifdef PNTR_APP_INIT_AUDIO
        PNTR_APP_INIT_AUDIO(app);
    #endif

    // Call the init callback.
    if (app->init != NULL) {
        // Check if initialization worked.
        if (!app->init(app)) {
            pntr_unload_image(app->screen);
            sargs_shutdown();
            return false;
        }
    }

    return true;
}

PNTR_APP_API void pntr_app_close(pntr_app* app) {
    if (app == NULL) {
        return;
    }

    // Tell the application to close.
    if (app->close != NULL) {
        app->close(app);
    }

    #ifdef PNTR_APP_CLOSE_AUDIO
    PNTR_APP_CLOSE_AUDIO(app);
    #endif

    // Unload any other associated memory
    pntr_unload_image(app->screen);
    app->screen = NULL;

    // Unload any loaded file data.
    if (!app->argFileDataDoNotUnload) {
        pntr_unload_memory(app->argFileData);
        app->argFileDataSize = 0;
        app->argFileData = NULL;
    }

    // Clear the clipboard data.
    if (app->clipboard != NULL) {
        pntr_unload_memory(app->clipboard);
        app->clipboard = NULL;
    }

    pntr_app_platform_close(app);

    // Stop using Sokol args.
    sargs_shutdown();
}

PNTR_APP_API pntr_app_sound_type pntr_app_get_file_sound_type(const char* fileName) {
    if (strstr(fileName, ".wav") || strstr(fileName, ".WAV")) {
        return PNTR_APP_SOUND_TYPE_WAV;
    }

    if (strstr(fileName, ".ogg") || strstr(fileName, ".OGG")) {
        return PNTR_APP_SOUND_TYPE_OGG;
    }

    return PNTR_APP_SOUND_TYPE_UNKNOWN;
}

PNTR_APP_API pntr_sound* pntr_load_sound(const char* fileName) {
    pntr_app_sound_type type = pntr_app_get_file_sound_type(fileName);
    if (type == PNTR_APP_SOUND_TYPE_UNKNOWN) {
        return pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    }

    unsigned int bytesRead;
    unsigned char* data = pntr_load_file(fileName, &bytesRead);
    if (data == NULL) {
        return NULL;
    }

    return pntr_load_sound_from_memory(type, data, bytesRead);
}

PNTR_APP_API void* pntr_app_userdata(pntr_app* app) {
    return app->userData;
}

PNTR_APP_API int pntr_app_width(pntr_app* app) {
    if (app->screen == NULL) {
        return app->width;
    }

    return app->screen->width;
}

PNTR_APP_API int pntr_app_height(pntr_app* app) {
    if (app->screen == NULL) {
        return app->height;
    }

    return app->screen->height;
}

PNTR_APP_API float pntr_app_delta_time(pntr_app* app) {
    return app->deltaTime;
}

PNTR_APP_API int pntr_app_fps(pntr_app* app) {
    return app->actualFPS;
}

PNTR_APP_API void pntr_app_set_userdata(pntr_app* app, void* userData) {
    if (app == NULL) {
        return;
    }
    app->userData = userData;
}

PNTR_APP_API void pntr_app_process_event(pntr_app* app, pntr_app_event* event) {
    switch (event->type) {
        case PNTR_APP_EVENTTYPE_KEY_DOWN:
            app->keysDown[event->key] = true;
            app->keysChanged = true;
            break;
        case PNTR_APP_EVENTTYPE_KEY_UP:
            app->keysDown[event->key] = false;
            app->keysChanged = true;
            break;
        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN:
            app->gamepadButtonState[event->gamepad] |= PNTR_APP_GAMEPAD_BUTTON_FLAG(event->gamepadButton);
            break;
        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP:
            app->gamepadButtonState[event->gamepad] &= ~PNTR_APP_GAMEPAD_BUTTON_FLAG(event->gamepadButton);
            break;
        case PNTR_APP_EVENTTYPE_MOUSE_MOVE:
            // Passing in a delta change means we're acting on mouse move rather than position.
            if (event->mouseDeltaX != 0 || event->mouseDeltaY != 0) {
                app->mouseDeltaX = event->mouseDeltaX;
                app->mouseDeltaY = event->mouseDeltaY;
                app->mouseX += event->mouseDeltaX;
                app->mouseY += event->mouseDeltaY;
                app->mouseChanged = true;
            }
            else {
                event->mouseDeltaX = event->mouseX - app->mouseX;
                event->mouseDeltaY = event->mouseY - app->mouseY;
                if (event->mouseDeltaX == 0 && event->mouseDeltaY == 0) {
                    return;
                }
                app->mouseDeltaX = event->mouseDeltaX;
                app->mouseDeltaY = event->mouseDeltaY;
                app->mouseX = event->mouseX;
                app->mouseY = event->mouseY;
                app->mouseChanged = true;
            }

            // Clamp the mouse position.
            if (app->mouseX < 0) {
                app->mouseX = 0;
            }
            else if (app->mouseX > app->width) {
                app->mouseX = (float)app->width;
            }
            if (app->mouseY < 0) {
                app->mouseY = 0;
            }
            else if (app->mouseY > app->height) {
                app->mouseY = (float)app->height;
            }

            // Make sure the event gets the updated positions.
            // event->mouseX = app->mouseX;
            // event->mouseY = app->mouseY;
            break;
        case PNTR_APP_EVENTTYPE_MOUSE_WHEEL:
            app->mouseWheel = event->mouseWheel;
            app->mouseWheelChanged = true;
            event->mouseX = app->mouseX;
            event->mouseX = app->mouseX;
            break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN:
            app->mouseButtonsDown[event->mouseButton] = true;
            app->mouseButtonsChanged = true;
            event->mouseX = app->mouseX;
            event->mouseX = app->mouseX;
            break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP:
            app->mouseButtonsDown[event->mouseButton] = false;
            app->mouseButtonsChanged = true;
            event->mouseX = app->mouseX;
            event->mouseX = app->mouseX;
            break;
        default:
            // Not covered here.
            break;
    }

    if (app->event != NULL) {
        app->event(app, event);
    }
}

PNTR_APP_API void pntr_app_pre_events(pntr_app* app) {
    if (app->keysChanged) {
        // Move the active keys to the last keys.
        for (int i = PNTR_APP_KEY_FIRST; i < PNTR_APP_KEY_LAST; i++) {
            app->keysDownLast[i] = app->keysDown[i];
        }
        app->keysChanged = false;
    }

    for (int i = 0; i < PNTR_APP_MAX_GAMEPADS; i++) {
        app->gamepadButtonStatePrevious[i] = app->gamepadButtonState[i];
    }

    if (app->mouseWheelChanged) {
        app->mouseWheel = 0;
        app->mouseWheelChanged = false;
    }

    if (app->mouseButtonsChanged) {
        for (int i = PNTR_APP_MOUSE_BUTTON_FIRST; i < PNTR_APP_MOUSE_BUTTON_LAST; i++) {
            app->mouseButtonsDownLast[i] = app->mouseButtonsDown[i];
        }
        app->mouseButtonsChanged = false;
    }

    if (app->mouseChanged) {
        app->mouseDeltaX = 0;
        app->mouseDeltaY = 0;
        app->mouseChanged = false;
    }
}

PNTR_APP_API bool pntr_app_key_pressed(pntr_app* app, pntr_app_key key) {
    return app->keysDown[key] && !app->keysDownLast[key];
}

PNTR_APP_API bool pntr_app_key_down(pntr_app* app, pntr_app_key key) {
    return app->keysDown[key];
}

PNTR_APP_API bool pntr_app_key_released(pntr_app* app, pntr_app_key key) {
    return !app->keysDown[key] && app->keysDownLast[key];
}

PNTR_APP_API bool pntr_app_key_up(pntr_app* app, pntr_app_key key) {
    return !app->keysDown[key];
}

/**
 * Checks if a given gamepad button was pressed.
 *
 * @param app The active application.
 * @param gamepad The gamepad to check. If set to -1, will check all gamepads.
 * @param button The button to check.
 *
 * @return True or false, depending on whether or not the button was pressed.
 */
PNTR_APP_API bool pntr_app_gamepad_button_pressed(pntr_app* app, int gamepad, pntr_app_gamepad_button button) {
    if (app == NULL) {
        return false;
    }

    if (gamepad < 0) {
        for (int i = 0; i < PNTR_APP_MAX_GAMEPADS; i++) {
            if ((app->gamepadButtonStatePrevious[i] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) == 0 &&
			    (app->gamepadButtonState[i] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0) {
                return true;
            }
        }

        return false;
    }

    if (gamepad >= PNTR_APP_MAX_GAMEPADS) {
        return false;
    }

    return ((app->gamepadButtonStatePrevious[gamepad] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) == 0 &&
			(app->gamepadButtonState[gamepad] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0);
}

/**
 * Checks if a given gamepad button is down.
 *
 * @param app The active application.
 * @param gamepad The gamepad to check. If set to -1, will check all gamepads.
 * @param button The button to check.
 *
 * @return True or false, depending on whether or not the button is currently down.
 */
PNTR_APP_API bool pntr_app_gamepad_button_down(pntr_app* app, int gamepad, pntr_app_gamepad_button button) {
    if (app == NULL) {
        return false;
    }

    if (gamepad < 0) {
        for (int i = 0; i < PNTR_APP_MAX_GAMEPADS; i++) {
            if ((app->gamepadButtonState[i] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0) {
                return true;
            }
        }

        return false;
    }

    if (gamepad >= PNTR_APP_MAX_GAMEPADS) {
        return false;
    }

    return (app->gamepadButtonState[gamepad] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0;
}

/**
 * Checks if a given gamepad button was released.
 *
 * @param app The active application.
 * @param gamepad The gamepad to check. If set to -1, will check all gamepads.
 * @param button The button to check.
 *
 * @return True or false, depending on whether or not the button was released.
 */
PNTR_APP_API bool pntr_app_gamepad_button_released(pntr_app* app, int gamepad, pntr_app_gamepad_button button) {
    if (app == NULL) {
        return false;
    }

    if (gamepad < 0) {
        for (int i = 0; i < PNTR_APP_MAX_GAMEPADS; i++) {
            if ((app->gamepadButtonState[i] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) == 0 &&
			    (app->gamepadButtonStatePrevious[i] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0) {
                return true;
            }
        }

        return false;
    }

    if (gamepad >= PNTR_APP_MAX_GAMEPADS) {
        return false;
    }

    return ((app->gamepadButtonState[gamepad] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) == 0 &&
			(app->gamepadButtonStatePrevious[gamepad] & PNTR_APP_GAMEPAD_BUTTON_FLAG(button)) != 0);
}

PNTR_APP_API float pntr_app_mouse_x(pntr_app* app) {
    return app->mouseX;
}

PNTR_APP_API float pntr_app_mouse_y(pntr_app* app) {
    return app->mouseY;
}

PNTR_APP_API float pntr_app_mouse_delta_x(pntr_app* app) {
    return app->mouseDeltaX;
}

PNTR_APP_API float pntr_app_mouse_delta_y(pntr_app* app) {
    return app->mouseDeltaY;
}

PNTR_APP_API int pntr_app_mouse_wheel(pntr_app* app) {
    return app->mouseWheel;
}

PNTR_APP_API bool pntr_app_mouse_button_pressed(pntr_app* app, pntr_app_mouse_button button) {
    return app->mouseButtonsDown[button] && !app->mouseButtonsDownLast[button];
}

PNTR_APP_API bool pntr_app_mouse_button_down(pntr_app* app, pntr_app_mouse_button button) {
    return app->mouseButtonsDown[button];
}

PNTR_APP_API bool pntr_app_mouse_button_released(pntr_app* app, pntr_app_mouse_button button) {
    return !app->mouseButtonsDown[button] && app->mouseButtonsDownLast[button];
}
PNTR_APP_API bool pntr_app_mouse_button_up(pntr_app* app, pntr_app_mouse_button button) {
    return !pntr_app_mouse_button_down(app, button);
}

PNTR_APP_API bool pntr_app_show_mouse(pntr_app* app, bool show) {
    if (app == NULL) {
        return false;
    }

    #ifdef PNTR_APP_SHOW_MOUSE
        return PNTR_APP_SHOW_MOUSE(app, show);
    #else
        (void)show;
        return false;
    #endif
}

/**
 * Change the size of the screen.
 *
 * @param app The application to act on.
 * @param width The desired width of the screen.
 * @param height The desired height of the screen.
 *
 * @return True or false depending on if the screen size is now matching the desired width and height.
 */
PNTR_APP_API bool pntr_app_set_size(pntr_app* app, int width, int height) {
    if (app == NULL || width <= 0 || height <= 0) {
        return false;
    }

    // Make sure we're not resizing twice.
    if (pntr_app_width(app) == width && pntr_app_height(app) == height) {
        return true;
    }

    // Create a new backbuffer.
    pntr_image* new_screen = pntr_image_resize(app->screen, width, height, PNTR_FILTER_NEARESTNEIGHBOR);
    if (new_screen == NULL) {
        return false;
    }

    // Request that the platform resizes the window.
    if (!pntr_app_platform_set_size(app, width, height)) {
        pntr_unload_image(new_screen);
        return false;
    }

    // Swap the buffers
    pntr_image* oldScreen = app->screen;
    app->screen = new_screen;
    pntr_unload_image(oldScreen);
    app->width = app->screen->width;
    app->height = app->screen->height;

    return true;
}

void* pntr_app_load_arg_file(pntr_app* app, unsigned int* size) {
    if (app == NULL) {
        return NULL;
    }

    // See if the data is already available.
    if (app->argFileData != NULL && app->argFileDataSize > 0) {
        // Copy the memory as an output, as the application is now responsible to unload it.
        void* output = pntr_load_memory(app->argFileDataSize);
        pntr_memory_copy(output, app->argFileData, app->argFileDataSize);
        if (size != NULL) {
            *size = app->argFileDataSize;
        }
        return output;
    }

    // Load the file directly.
    if (app->argFile != NULL && app->argFile[0] != '\0') {
        unsigned int loadedSize =  0;
        void* output = pntr_load_file(app->argFile, &loadedSize);
        if (size != NULL) {
            *size = loadedSize;
        }
        return output;
    }

    return NULL;
}

PNTR_APP_API void pntr_app_log(pntr_app_log_type type, const char* message) {
#ifdef PNTR_APP_LOG
    PNTR_APP_LOG(type, message);
#else
    switch (type) {
        case PNTR_APP_LOG_ERROR:
            fprintf(stderr, "%s\n", message);
        break;
        case PNTR_APP_LOG_DEBUG:
            // Skip debug messages if NDEBUG is defined.
            #ifndef NDEBUG
                printf("%s\n", message);
            #endif
        break;
        default:
            printf("%s\n", message);
        break;
    }
#endif
}

#ifdef PNTR_ENABLE_VARGS
PNTR_APP_API void pntr_app_log_ex(pntr_app_log_type type, const char* message, ...) {
    #ifndef PNTR_APP_LOG_EX_STRING_LENGTH
    #define PNTR_APP_LOG_EX_STRING_LENGTH 256
    #endif
    char output[PNTR_APP_LOG_EX_STRING_LENGTH];

    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(output, PNTR_APP_LOG_EX_STRING_LENGTH, message, arg_ptr);
    va_end(arg_ptr);

    pntr_app_log(type, output);
}
#endif

PNTR_APP_API const char* pntr_app_title(pntr_app* app) {
    if (app == NULL) {
        return NULL;
    }

    return app->title;
}

PNTR_APP_API float pntr_app_random_float(pntr_app* app, float min, float max) {
    if (app == NULL) {
        return 0.0f;
    }
    return prand_float(&app->prand, min, max);
}

PNTR_APP_API int pntr_app_random(pntr_app* app, int min, int max) {
    if (app == NULL) {
        return 0;
    }
    return prand_int(&app->prand, min, max);
}

PNTR_APP_API uint64_t pntr_app_random_seed(pntr_app* app) {
    if (app == NULL) {
        return 0;
    }
    return app->prand.seed;
}

PNTR_APP_API void pntr_app_random_set_seed(pntr_app* app, uint64_t seed) {
    if (app == NULL) {
        return;
    }
    prand_init(&app->prand, seed);
}

/**
 * Set the clipboard text.
 *
 * On the platform front, the `PNTR_APP_SET_CLIPBOARD` macro can be defined to handle setting the clipboard.
 *
 * @param app The application to act on.
 * @param text The text to set the clipboard to.
 * @param text_size The length of the text to set. Use 0 to determine the length automatically.
 */
PNTR_APP_API void pntr_app_set_clipboard(pntr_app* app, const char* text, int text_size) {
    if (app == NULL || text == NULL) {
        return;
    }

    if (app->clipboard != NULL) {
        pntr_unload_memory(app->clipboard);
    }

    // Copy the clipboard text.
    size_t length = text_size <= 0 ? PNTR_STRSIZE(text) : (size_t)(text_size + 1);
    app->clipboard = (char*)pntr_load_memory(length);
    if (app->clipboard == NULL) {
        return;
    }

    // Copy the memory.
    size_t i;
    for (i = 0; i < length - (size_t)1; i++) {
        app->clipboard[i] = text[i];
    }
    app->clipboard[i] = '\0';

    #ifdef PNTR_APP_SET_CLIPBOARD
        PNTR_APP_SET_CLIPBOARD(app, app->clipboard);
    #endif
}

/**
 * Get the clipboard text.
 *
 * On the platform front, the `PNTR_APP_CLIPBOARD` macro can be defined to handle getting the clipboard. It will create new memory with the text, only if it has changed.
 *
 * @param app The application to act on.
 *
 * @return The clipboard text, or NULL if there hasn't been any clipboard text set.
 */
PNTR_APP_API const char* pntr_app_clipboard(pntr_app* app) {
    #ifdef PNTR_APP_CLIPBOARD
        const char* clipboard = PNTR_APP_CLIPBOARD(app);
        if (clipboard != NULL) {
            if (app->clipboard != NULL) {
                pntr_unload_memory((void*)app->clipboard);
            }
            app->clipboard = (char*)clipboard;
        }
    #endif
    return app->clipboard;
}

PNTR_APP_API pntr_sound* pntr_load_sound_from_memory(pntr_app_sound_type type, unsigned char* data, unsigned int dataSize) {
    if (data == NULL || dataSize <= 0) {
        return NULL;
    }

    #ifdef PNTR_APP_LOAD_SOUND_FROM_MEMORY
        return PNTR_APP_LOAD_SOUND_FROM_MEMORY(type, data, dataSize);
    #else
        (void)type;
        return NULL;
    #endif
}

PNTR_APP_API void pntr_unload_sound(pntr_sound* sound) {
    if (sound == NULL) {
        return;
    }

    #ifdef PNTR_APP_UNLOAD_SOUND
        PNTR_APP_UNLOAD_SOUND(sound);
    #endif
}

PNTR_APP_API void pntr_play_sound(pntr_sound* sound, bool loop) {
    if (sound == NULL) {
        return;
    }

    #ifdef PNTR_APP_PLAY_SOUND
        PNTR_APP_PLAY_SOUND(sound, loop);
    #else
        (void)loop;
    #endif
}

PNTR_APP_API void pntr_stop_sound(pntr_sound* sound) {
    if (sound == NULL) {
        return;
    }

    #ifdef PNTR_APP_STOP_SOUND
        PNTR_APP_STOP_SOUND(sound);
    #endif
}

PNTR_APP_API void pntr_set_volume(pntr_sound* sound, float volume) {
    if (sound == NULL) {
        return;
    }

    if (volume < 0.0f) {
        volume = 0.0f;
    }
    else if (volume > 1.0f) {
        volume = 1.0f;
    }

    #ifdef PNTR_APP_SET_VOLUME
        PNTR_APP_SET_VOLUME(sound, volume);
    #endif
}

PNTR_APP_API bool pntr_sound_playing(pntr_sound*sound) {
    if (sound == NULL) {
        return false;
    }

    #ifdef PNTR_APP_SOUND_PLAYING
        return PNTR_APP_SOUND_PLAYING(sound);
    #else
        return false;
    #endif
}

void pntr_app_manual_save_load_data(pntr_app* app, pntr_app_event* event, const char* fileName) {
    if (event->type == PNTR_APP_EVENTTYPE_LOAD) {
        unsigned int size;

        void* data = pntr_load_file(fileName, &size);
        if (data == NULL) {
            return;
        }
        size_t decoded_size = b64_decoded_size((const char*)data, (size_t)size);
        unsigned char* saveData = (unsigned char*)pntr_load_memory(decoded_size + (size_t)1);

        // Clear out the data.
        for (size_t i = 0; i < decoded_size; i++) {
            saveData[i] = '\0';
        }


        // Decode the loaded data
        event->save = (void*)saveData;
        event->save_size = b64_decode((unsigned char*)event->save, (const char*)data, (size_t)size);

        // Callback
        pntr_app_process_event(app, event);

        // Clean up
        pntr_unload_memory(event->save);
        event->save = NULL;
        event->save_size = 0;
        pntr_unload_file((unsigned char*)data);
    }
    else if (event->type == PNTR_APP_EVENTTYPE_SAVE) {
        // Load the memory
        event->save_size = PNTR_APP_SAVE_SIZE;
        event->save = pntr_load_memory(event->save_size);
        pntr_app_process_event(app, event);

        // Encode it
        size_t encoded_size = b64_encoded_size(event->save_size);
        char* encoded = (char*)pntr_load_memory(encoded_size);
        size_t result_size = b64_encode(encoded, (const unsigned char*)event->save, encoded_size);

        // Save
        pntr_save_file(fileName, encoded, (unsigned int)result_size);

        // Clean up
        pntr_unload_memory(event->save);
        pntr_unload_memory((void*)encoded);
    }
}

#ifdef __cplusplus
}
#endif

#endif  // PNTR_APP_IMPLEMENTATION_ONCE
#endif  // PNTR_APP_IMPLEMENTATION
