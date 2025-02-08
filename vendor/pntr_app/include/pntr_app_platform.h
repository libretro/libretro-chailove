#ifndef PNTR_APP_PLATFORM_H__
#define PNTR_APP_PLATFORM_H__

// Platform detection.
#if !defined(PNTR_APP_CLI) && !defined(PNTR_APP_WEB) && !defined(PNTR_APP_LIBRETRO) && !defined(PNTR_APP_RAYLIB) && !defined(PNTR_APP_SDL)
    // libretro
    #if defined(__LIBRETRO__)
        #define PNTR_APP_LIBRETRO

    // Emscripten
    #elif defined(__EMSCRIPTEN__)
        #define PNTR_APP_EMSCRIPTEN

    // SDL
    #elif defined(SDL_VERSION)
        #define PNTR_APP_SDL

    // Raylib
    #elif defined(RAYLIB_VERSION)
        #define PNTR_APP_RAYLIB

    #else
        // Fall back to the CLI
        #define PNTR_APP_CLI
        #define PNTR_APP_DISABLE_TERMBOX
    #endif
#endif

// Pixel Format
#if defined(PNTR_APP_SDL) || defined(PNTR_APP_LIBRETRO)
    #ifndef PNTR_PIXELFORMAT_ARGB
        #define PNTR_PIXELFORMAT_ARGB
    #endif
    #ifdef PNTR_PIXELFORMAT_RGBA
        #undef PNTR_PIXELFORMAT_RGBA
    #endif
#else
    #ifndef PNTR_PIXELFORMAT_RGBA
        #define PNTR_PIXELFORMAT_RGBA
    #endif
    #ifdef PNTR_PIXELFORMAT_ARGB
        #undef PNTR_PIXELFORMAT_ARGB
    #endif
#endif

#endif  // PNTR_APP_PLATFORM_H__
