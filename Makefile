DEBUG = 0

ifeq ($(platform),)
	platform = unix
ifeq ($(shell uname -a),)
	platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
	platform = osx
else ifneq ($(findstring MINGW,$(shell uname -a)),)
	platform = win
endif
endif

TARGET_NAME := chaigame

ifeq ($(platform), unix)
	TARGET := $(TARGET_NAME)_libretro.so
	fpic += -fPIC
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS += -D__LINUX__ -D__linux
	SDL_PREFIX := unix
	GL_LIB := -lGL
# android arm
else ifneq (,$(findstring android,$(platform)))
	TARGET := $(TARGET_NAME)_libretro_android.so
	fpic += -fPIC
	SHARED := -lstdc++ -lstd++fs -llog -lz -shared -Wl,--version-script=link.T -Wl,--no-undefined
	CFLAGS +=  -g -O2
	FLAGS += -DANDROID
	GL_LIB := -lGL
# cross Windows
else ifeq ($(platform), wincross64)
	TARGET := $(TARGET_NAME)_libretro.dll
	AR = x86_64-w64-mingw32-ar
 	CC = x86_64-w64-mingw32-gcc
 	CXX = x86_64-w64-mingw32-g++
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	LDFLAGS += -static-libgcc -static-libstdc++ -lstd++fs
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS += -D_WIN64
	EXTRA_LDF := -lwinmm -Wl,--export-all-symbols
	SDL_PREFIX := win
	GL_LIB := -lopengl32
else
	TARGET :=  $(TARGET_NAME)_retro.dll
	CC = gcc
 	CXX = g++
	SHARED := -shared -Wl,--no-undefined -Wl,--version-script=link.T
	LDFLAGS += -static-libgcc -static-libstdc++  -lstd++fs
	ENDIANNESS_DEFINES := -DLSB_FIRST
	FLAGS += -D_WIN32
	EXTRA_LDF += -lwinmm -Wl,--export-all-symbols
	SDL_PREFIX := win
	GL_LIB := -lopengl32
endif

# MacOSX
ifeq ($(platform), osx)
	FLAGS += -D__APPLE__
endif

OBJECTS += src/glsym/rglgen.o
ifeq ($(GLES), 1)
   CFLAGS += -DHAVE_OPENGLES -DHAVE_OPENGLES2
   ifeq ($(GLES31), 1)
      CFLAGS += -DHAVE_OPENGLES3 -DHAVE_OPENGLES_3_1
   else ifeq ($(GLES3), 1)
      CFLAGS += -DHAVE_OPENGLES3
   endif
   # Still link against GLESv2 when using GLES3 API, at least on desktop Linux.
   LIBS += -lGLESv2
   OBJECTS += src/glsym/glsym_es2.o
else
   OBJECTS += src/glsym/glsym_gl.o
   LIBS += $(GL_LIB)
endif

OBJECTS += src/libretro.o \
	src/Game.o \
	src/chaigame/audio.o \
	src/chaigame/log.o \
	src/chaigame/graphics.o \
	src/chaigame/keyboard.o \
	src/chaigame/script.o \
	src/chaigame/filesystem.o \
	src/chaigame/image.o \
	src/chaigame/sound.o \
	src/chaigame/math.o \
	src/chaigame/font.o \
	src/chaigame/timer.o \
	src/chaigame/event.o \
	src/chaigame/window.o \
	src/chaigame/mouse.o \
	src/chaigame/system.o \
	src/chaigame/joystick.o \
	src/chaigame/graphics/ImageData.o \
	src/chaigame/graphics/Quad.o \
	src/chaigame/graphics/Image.o \
	src/chaigame/graphics/Color.o \
	src/chaigame/graphics/Font.o \
	src/chaigame/graphics/Point.o \
	src/chaigame/input/Joystick.o \
	src/chaigame/audio/SoundData.o \
	src/chaigame/system/Config.o \
	test/Test.o \
	vendor/physfs/extras/physfsrwops.o \
	vendor/SDL_tty/src/SDL_tty.o \
	vendor/SDL_tty/src/SDL_fnt.o \
	vendor/physfs/src/archiver_dir.o \
	vendor/physfs/src/archiver_grp.o \
	vendor/physfs/src/archiver_hog.o \
	vendor/physfs/src/archiver_iso9660.o \
	vendor/physfs/src/archiver_lzma.o \
	vendor/physfs/src/archiver_mvl.o \
	vendor/physfs/src/archiver_qpak.o \
	vendor/physfs/src/archiver_slb.o \
	vendor/physfs/src/archiver_unpacked.o \
	vendor/physfs/src/archiver_wad.o \
	vendor/physfs/src/archiver_zip.o \
	vendor/physfs/src/physfs_byteorder.o \
	vendor/physfs/src/physfs.o \
	vendor/physfs/src/physfs_unicode.o \
	vendor/physfs/src/platform_macosx.o \
	vendor/physfs/src/platform_posix.o \
	vendor/physfs/src/platform_unix.o \
	vendor/physfs/src/platform_windows.o \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/SDL_framerate.o \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/SDL_gfxBlitFunc.o \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/SDL_gfxPrimitives.o \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/SDL_imageFilter.o \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/SDL_rotozoom.o

ifeq ($(platform), win)
	SDL_SOURCES_C := $(wildcard ./vendor/sdl-libretro/src/*.c  ./vendor/sdl-libretro/src/audio/*.c  ./vendor/sdl-libretro/src/cdrom/win32/*.c  ./vendor/sdl-libretro/src/cdrom/*.c  ./vendor/sdl-libretro/src/cpuinfo/*.c  ./vendor/sdl-libretro/src/events/*.c  ./vendor/sdl-libretro/src/file/*.c  ./vendor/sdl-libretro/src/stdlib/*.c  ./vendor/sdl-libretro/src/thread/*.c  ./vendor/sdl-libretro/src/timer/*.c  ./vendor/sdl-libretro/src/video/*.c  ./vendor/sdl-libretro/src/joystick/*.c  ./vendor/sdl-libretro/src/video/libretro/*.c  ./vendor/sdl-libretro/src/joystick/libretro/*.c  ./vendor/sdl-libretro/src/timer/libretro/*.c  ./vendor/sdl-libretro/src/audio/libretro/*.c  ./vendor/sdl-libretro/src/thread/win32/SDL_sysmutex.c ./vendor/sdl-libretro/src/thread/win32/SDL_syssem.c ./vendor/sdl-libretro/src/thread/win32/SDL_systhread.c ./vendor/sdl-libretro/src/thread/generic/SDL_syscond.c ./vendor/sdl-libretro/src/loadso/dummy/*.c)
else
	SDL_SOURCES_C := $(wildcard ./vendor/sdl-libretro/src/*.c ./vendor/sdl-libretro/src/audio/*.c  ./vendor/sdl-libretro/src/cdrom/linux/*.c  ./vendor/sdl-libretro/src/cdrom/*.c  ./vendor/sdl-libretro/src/cpuinfo/*.c  ./vendor/sdl-libretro/src/events/*.c  ./vendor/sdl-libretro/src/file/*.c  ./vendor/sdl-libretro/src/stdlib/*.c  ./vendor/sdl-libretro/src/thread/*.c  ./vendor/sdl-libretro/src/timer/*.c  ./vendor/sdl-libretro/src/video/*.c  ./vendor/sdl-libretro/src/joystick/*.c  ./vendor/sdl-libretro/src/video/libretro/*.c  ./vendor/sdl-libretro/src/thread/pthread/*.c ./vendor/sdl-libretro/src/joystick/libretro/*.c  ./vendor/sdl-libretro/src/timer/libretro/*.c  ./vendor/sdl-libretro/src/audio/libretro/*.c  ./vendor/sdl-libretro/src/loadso/dummy/*.c)
endif
OBJECTS += $(SDL_SOURCES_C:.c=.o)

SDL_GPU_SOURCES_C := $(wildcard ./vendor/sdl-gpu/src/*.c ./vendoro/sdl-gpu/src/externals/gl3stub/*.c ./vendor/sdl-gpu/src/externals/glew/*.c ./vendor/sdl-gpu/src/externals/stb_image/*.c ./vendor/sdl-gpu/src/externals/stb_image_write/*.c )
OBJECTS += $(SDL_GPU_SOURCES_C:.c=.o)

# Build all the dependencies, and the core.
all: | dependencies	$(TARGET)

ifeq ($(DEBUG), 0)
   FLAGS += -O3 -ffast-math -fomit-frame-pointer
else
   FLAGS += -O0 -g
endif

LDFLAGS +=  $(fpic) $(SHARED) \
	-$(LIBS) \
	-ldl \
	-lpthread \
	$(EXTRA_LDF)
FLAGS += -I. \
	-Ivendor/sdl-libretro/include \
	-Ivendor/libretro-common/include \
	-Ivendor/chaiscript/include \
	-Ivendor/SDL_tty/include \
	-Ivendor/spdlog/include \
	-Ivendor/sdl-libretro/tests/SDL_gfx-2.0.26 \
	-Ivendor/sdl-libretro/tests/SDL_ttf-2.0.11/VisualC/external/include \
	-Ivendor/ChaiScript_Extras/include \
	-Ivendor/physfs/src \
	-Ivendor/Snippets \
	-Ivendor/sdl-gpu/include \
	-Ivendor/sdl-gpu/src/externals/gl3stub \
	-Ivendor/sdl-gpu/src/externals/glew \
	-Ivendor/sdl-gpu/src/externals/glew/GL \
	-Ivendor/sdl-gpu/src/externals/stb_image \
	-Ivendor/sdl-gpu/src/externals/stb_image_write \
	-Isrc/glsym

WARNINGS :=

ifeq ($(HAVE_CHAISCRIPT),)
	FLAGS += -D__HAVE_CHAISCRIPT__ -DCHAISCRIPT_NO_THREADS -DCHAISCRIPT_NO_THREADS_WARNING
endif
ifneq ($(HAVE_TESTS),)
	FLAGS += -D__HAVE_TESTS__
endif

FLAGS += -D__LIBRETRO__ -DSDL_GPU_DISABLE_GLES $(ENDIANNESS_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -fpermissive -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)

dependencies:
	git submodule update --init --recursive

test: all
	@echo "Execute the following to run tests:\n\n    retroarch -L $(TARGET) test/main.chai\n"

examples: all
	retroarch -L $(TARGET) test/examples/main.chai

test-script: all
	retroarch -L $(TARGET) test/main.chai

noscript: dependencies
	$(MAKE) HAVE_CHAISCRIPT=0 HAVE_TESTS=1

test-noscript: noscript
	retroarch -L $(TARGET) test/main.chai

PREFIX := /usr
INSTALLDIR := $(PREFIX)/lib/libretro
install: all
	mkdir -p $(DESTDIR)$(INSTALLDIR)
	cp $(TARGET) $(DESTDIR)$(INSTALLDIR)
