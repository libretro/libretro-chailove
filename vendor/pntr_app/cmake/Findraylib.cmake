# raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
)
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    # Don't build raylib's examples and games
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
endif()
