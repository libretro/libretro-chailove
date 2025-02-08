# CMAKE Modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# Resources
file(GLOB resources resources/*)
set(examples_resources)
list(APPEND examples_resources ${resources})
file(COPY ${examples_resources} DESTINATION "resources/")

find_package(pntr)

set(BUILD_SHARED_LIBS FALSE)

# SDL
if (PNTR_APP_BUILD_EXAMPLE_SDL AND NOT EMSCRIPTEN)
    add_executable(pntr_app_example_sdl
        pntr_app_example.c
    )

    target_compile_definitions(pntr_app_example_sdl PUBLIC PNTR_APP_SDL)

    # SDL
    set(SDL_SHARED FALSE)
    set(SDL2_SHARED FALSE)
    set(SDL_STATIC TRUE)
    set(SDL_TEST FALSE)
    set(SDL_TESTS FALSE)
    set(INTERFACE_SDL2_SHARED false)
    set(SDL2_DISABLE_UNINSTALL TRUE)
    set(SDL2_DISABLE_INSTALL TRUE)
    set(SDL_INSTALL_TESTS FALSE)
    find_package(SDL2 REQUIRED)
    set(SDL2_LIBRARIES SDL2-static)
    #set(SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)

    # SDL_mixer
    set(SDL2MIXER_VORBIS STB)
    set(SDL2MIXER_INSTALL OFF)
    set(SDL2MIXER_DEPS_SHARED OFF)
    set(SDL2MIXER_VENDORED OFF)
    set(SDL2MIXER_SAMPLES OFF)
    set(SDL2MIXER_CMD OFF)
    set(SDL2MIXER_FLAC OFF)
    set(SDL2MIXER_MOD OFF)
    set(SDL2MIXER_MP3 OFF)
    set(SDL2MIXER_MIDI_NATIVE OFF)
    set(SDL2MIXER_OPUS OFF)
    set(SDL2MIXER_OPUS_SHARED OFF)
    set(SDL2MIXER_MIDI_FLUIDSYNTH OFF)
    set(SDL2MIXER_MP3_MPG123 OFF)
    set(SDL2MIXER_MP3_DRMP3 OFF)
    set(SDL2MIXER_MOD_XMP OFF)
    set(SDL2MIXER_MOD_MODPLUG OFF)
    set(SDL2MIXER_FLAC_DRFLAC OFF)
    set(SDL2MIXER_FLAC_LIBFLAC OFF)
    set(SDL2MIXER_VORBIS_VORBISFILE OFF)
    set(SDL2MIXER_WAVPACK OFF)
    set(SDL2MIXER_SAMPLES_INSTALL OFF)
    set(SDL2MIXER_BUILD_SHARED_LIBS OFF)
    find_package(SDL2_mixer REQUIRED)
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2_mixer::SDL2_mixer-static)
    #set(SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2_mixer)

    target_compile_definitions(pntr_app_example_sdl PUBLIC
        PNTR_APP_SDL_MIXER
    )

    target_link_libraries(pntr_app_example_sdl PUBLIC
        pntr
        pntr_app
        ${SDL2_LIBRARIES}
    )
    set_property(TARGET pntr_app_example_sdl PROPERTY C_STANDARD 11)
    # Strict Warnings and Errors
    if(MSVC)
        target_compile_options(pntr_app_example_sdl PRIVATE /W4 /WX)
    else()
        target_compile_options(pntr_app_example_sdl PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

endif()

# raylib or Emscripten
if (PNTR_APP_BUILD_EXAMPLE_RAYLIB)
    find_package(raylib QUIET)
    add_executable(pntr_app_example_raylib
        pntr_app_example.c
    )
    target_compile_definitions(pntr_app_example_raylib PUBLIC PNTR_APP_RAYLIB)

    # Platform Updates
    if (EMSCRIPTEN)
        set_target_properties(pntr_app_example_raylib PROPERTIES OUTPUT_NAME "index")
        set_target_properties(pntr_app_example_raylib PROPERTIES SUFFIX ".html")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY --preload-file resources@/resources --shell-file ${CMAKE_SOURCE_DIR}/example/pntr_app_example.html")
    else()
        set_property(TARGET pntr_app_example_raylib PROPERTY C_STANDARD 11)
    endif()

    if (APPLE AND NOT EMSCRIPTEN)
        target_link_libraries(pntr_app_example_raylib PUBLIC "-framework IOKit")
        target_link_libraries(pntr_app_example_raylib PUBLIC "-framework Cocoa")
        target_link_libraries(pntr_app_example_raylib PUBLIC "-framework OpenGL")
    endif()

    target_link_libraries(pntr_app_example_raylib PUBLIC
        pntr
        pntr_app
        raylib_static
    )
    # Strict Warnings and Errors
    if(MSVC)
        target_compile_options(pntr_app_example_raylib PRIVATE /W4 /WX)
    else()
        target_compile_options(pntr_app_example_raylib PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

endif()

# CLI
if (PNTR_APP_BUILD_EXAMPLE_CLI AND NOT EMSCRIPTEN)
    add_executable(pntr_app_example_cli pntr_app_example.c)
    target_link_libraries(pntr_app_example_cli PUBLIC pntr pntr_app)
    target_compile_definitions(pntr_app_example_cli PUBLIC PNTR_APP_CLI)
    set_property(TARGET pntr_app_example_cli PROPERTY C_STANDARD 11)
    # Strict Warnings and Errors
    if(MSVC)
        target_compile_options(pntr_app_example_cli PRIVATE /W4 /WX)
    else()
        target_compile_options(pntr_app_example_cli PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

endif()


# Libretro core
if (PNTR_APP_BUILD_EXAMPLE_RETRO AND NOT EMSCRIPTEN)
    find_package(libretro_common REQUIRED)
    find_package(libretro_deps REQUIRED)

    add_library(pntr_app_example_libretro SHARED
        pntr_app_example.c
	    "${libretro_common_SOURCE_DIR}/audio/audio_mix.c"
	    "${libretro_common_SOURCE_DIR}/audio/audio_mixer.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/float_to_s16_neon.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/float_to_s16.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/mono_to_stereo_float.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/s16_to_float_neon.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/s16_to_float.c"
	    "${libretro_common_SOURCE_DIR}/audio/conversion/stereo_to_mono_float.c"
	    "${libretro_common_SOURCE_DIR}/audio/resampler/audio_resampler.c"
	    "${libretro_common_SOURCE_DIR}/audio/resampler/drivers/nearest_resampler.c"
	    "${libretro_common_SOURCE_DIR}/audio/resampler/drivers/sinc_resampler.c"
	    "${libretro_common_SOURCE_DIR}/compat/compat_posix_string.c"
	    "${libretro_common_SOURCE_DIR}/compat/compat_snprintf.c"
	    "${libretro_common_SOURCE_DIR}/compat/compat_strcasestr.c"
	    "${libretro_common_SOURCE_DIR}/compat/compat_strl.c"
	    "${libretro_common_SOURCE_DIR}/compat/fopen_utf8.c"
	    "${libretro_common_SOURCE_DIR}/formats/wav/rwav.c"
	    "${libretro_common_SOURCE_DIR}/features/features_cpu.c"
	    "${libretro_common_SOURCE_DIR}/encodings/encoding_utf.c"
	    "${libretro_common_SOURCE_DIR}/file/config_file_userdata.c"
	    "${libretro_common_SOURCE_DIR}/file/config_file.c"
	    "${libretro_common_SOURCE_DIR}/file/file_path.c"
	    "${libretro_common_SOURCE_DIR}/file/file_path_io.c"
	    "${libretro_common_SOURCE_DIR}/memmap/memalign.c"
	    "${libretro_common_SOURCE_DIR}/lists/string_list.c"
	    "${libretro_common_SOURCE_DIR}/streams/file_stream.c"
	    "${libretro_common_SOURCE_DIR}/streams/file_stream_transforms.c"
	    "${libretro_common_SOURCE_DIR}/streams/memory_stream.c"
	    "${libretro_common_SOURCE_DIR}/string/stdstring.c"
	    #"${libretro_common_SOURCE_DIR}/time/rtime.c"
	    "${libretro_common_SOURCE_DIR}/vfs/vfs_implementation.c"
    )
    target_link_libraries(pntr_app_example_libretro PUBLIC pntr pntr_app)

    target_include_directories(pntr_app_example_libretro PUBLIC
        "${libretro_common_SOURCE_DIR}/include"
        "${libretro_deps_SOURCE_DIR}"
    )

    target_compile_definitions(pntr_app_example_libretro PUBLIC
        PNTR_APP_LIBRETRO
        HAVE_RWAV=1
        PATH_MAX=1024
        __LIBRETRO__
        HAVE_STB_VORBIS
    )

    set_target_properties(pntr_app_example_libretro PROPERTIES PREFIX "" POSITION_INDEPENDENT_CODE ON)
endif()

# Emscripten
if (PNTR_APP_BUILD_EXAMPLE_WEB AND EMSCRIPTEN)
    add_executable(pntr_app_example_web pntr_app_example.c)
    target_link_libraries(pntr_app_example_web PUBLIC pntr pntr_app)
    target_compile_definitions(pntr_app_example_web PUBLIC PNTR_APP_WEB)
    set_property(TARGET pntr_app_example_web PROPERTY C_STANDARD 11)
    set_target_properties(pntr_app_example_web PROPERTIES SUFFIX ".html")
    set_target_properties(pntr_app_example_web PROPERTIES OUTPUT_NAME "index")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ASSERTIONS=1 -s WASM=1 --preload-file resources@/resources --shell-file ${CMAKE_SOURCE_DIR}/example/pntr_app_example.html")
    # Strict Warnings and Errors
    if(MSVC)
        target_compile_options(pntr_app_example_web PRIVATE /W4 /WX)
    else()
        target_compile_options(pntr_app_example_web PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
