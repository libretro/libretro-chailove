# SDL2_mixer
include(FetchContent)
FetchContent_Declare(
    SDL2MixerSource
    URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-2.8.0.zip
)
FetchContent_MakeAvailable(SDL2MixerSource)
#include_directories(${sdl2mixersource_SOURCE_DIR}/include)
