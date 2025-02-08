# pntr_app

Build [pntr](https://github.com/robloach/pntr) applications with the same code for a number of different targets, including SDL, raylib, libretro, the web, and more.

## Features

- Compile for a number of platforms...
    - [raylib](https://www.raylib.com/)
    - [SDL](https://www.libsdl.org/)
    - Web with [Emscripten](https://emscripten.org/)
    - [libretro](https://www.libretro.com/) and RetroArch
    - Command Line Interfaces with [termbox2](https://github.com/termbox/termbox2)
- Software rendering with [pntr](https://github.com/robloach/pntr)
- Audio (*.wav* or *.ogg*)
- Input with Mouse, Keyboard, or Gamepads

## Example

``` c
#define PNTR_APP_IMPLEMENTATION
#include "pntr_app.h"

bool Init(pntr_app* app) {
    // Initialize the application, return false on failure.
    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    // Clear the screen.
    pntr_clear_background(screen, PNTR_WHITE);

    // Draw a circle.
    pntr_draw_circle_fill(screen, screen->width / 2, screen->height / 2, 100, PNTR_BLUE);

    // Continue running the application.
    return true;
}

void Close(pntr_app* app) {
    // Uninitialize the application.
}

pntr_app Main(int argc, char* argv[]) {
    return (pntr_app) {
        .width = 800,
        .height = 450,
        .title = "pntr_app",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 60
    };
}
```

## Configuration

When compiling, define one of the following to determine which platform you are targeting...
```
PNTR_APP_SDL
PNTR_APP_RAYLIB
PNTR_APP_LIBRETRO
PNTR_APP_CLI
PNTR_APP_WEB
```

## API

For rendering, see the [pntr API](https://github.com/RobLoach/pntr).

``` c
// Application
pntr_app Main(int argc, char* argv[]);
int pntr_app_width(pntr_app* app);
int pntr_app_height(pntr_app* app);
void pntr_app_set_title(pntr_app* app, const char* title);
const char* pntr_app_title(pntr_app* app);
void* pntr_app_userdata(pntr_app* app);
void pntr_app_set_userdata(pntr_app* app, void* userData);
bool pntr_app_set_size(pntr_app* app, int width, int height);
void pntr_app_set_icon(pntr_app* app, pntr_image* icon);
float pntr_app_delta_time(pntr_app* app);

// Input
bool pntr_app_key_pressed(pntr_app* app, pntr_app_key key);
bool pntr_app_key_down(pntr_app* app, pntr_app_key key);
bool pntr_app_key_released(pntr_app* app, pntr_app_key key);
bool pntr_app_key_up(pntr_app* app, pntr_app_key key);
bool pntr_app_gamepad_button_pressed(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
bool pntr_app_gamepad_button_down(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
bool pntr_app_gamepad_button_released(pntr_app* app, int gamepad, pntr_app_gamepad_button key);
float pntr_app_mouse_x(pntr_app* app);
float pntr_app_mouse_y(pntr_app* app);
float pntr_app_mouse_delta_x(pntr_app* app);
float pntr_app_mouse_delta_y(pntr_app* app);
bool pntr_app_mouse_button_pressed(pntr_app* app, pntr_app_mouse_button button);
bool pntr_app_mouse_button_down(pntr_app* app, pntr_app_mouse_button button);
bool pntr_app_mouse_button_released(pntr_app* app, pntr_app_mouse_button button);
bool pntr_app_mouse_button_up(pntr_app* app, pntr_app_mouse_button button);

// Utility
int pntr_app_random(pntr_app* app, int min, int max);
float pntr_app_random_float(pntr_app* app, float min, float max);
uint64_t pntr_app_random_seed(pntr_app* app);
void pntr_app_random_set_seed(pntr_app* app, uint64_t seed);
void pntr_app_log(pntr_app_log_type type, const char* message);
void* pntr_app_load_arg_file(pntr_app* app, unsigned int* size);

// Sounds
pntr_sound* pntr_load_sound(const char* fileName);
pntr_sound* pntr_load_sound_from_memory(pntr_app_sound_type type, unsigned char* data, unsigned int dataSize);
void pntr_unload_sound(pntr_sound* sound);
void pntr_play_sound(pntr_sound* sound, bool loop);
void pntr_stop_sound(pntr_sound* sound);
void pntr_set_volume(pntr_sound* sound, float volume);
bool pntr_sound_playing(pntr_sound* sound);
```

## Build

There are a few platforms supported by pntr_app, which have their own build methods...

### Desktop

To build the raylib and SDL applications, use [CMake](https://cmake.org/). Depends on either [raylib](https://www.raylib.com/), or [SDL](https://www.libsdl.org/) along with [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)...

``` bash
cmake -B build
cmake --build build
```

You can disable building some examples by using...

``` bash
cmake -B build -DPNTR_APP_BUILD_EXAMPLE_SDL=false -DPNTR_APP_BUILD_EXAMPLE_RAYLIB=false
cmake --build build
```

### libretro

To build the libretro core, use `make`. Depends on [libretro-common](https://github.com/libretro/libretro-common).

``` bash
git submodule update --init
cd example
make
```

#### libretro WASM

``` bash
cd example
emmake make platform=emscripten
```

### Web

Build for the web with [Emscripten](https://emscripten.org/) and raylib. Depends on [emsdk](https://emscripten.org/docs/tools_reference/emsdk.html).

``` bash
emcmake cmake -B build -DPNTR_APP_BUILD_EXAMPLE_RAYLIB=false -DPNTR_APP_BUILD_EXAMPLE_WEB=true
emmake make -C build
emrun build/example/index.html
```

## License

Unless stated otherwise, all works are:

- Copyright (c) 2023 [Rob Loach](https://robloach.net)

... and licensed under:

- [zlib License](LICENSE)
