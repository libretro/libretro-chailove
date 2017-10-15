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
# android arm
else ifneq (,$(findstring android,$(platform)))
	TARGET := $(TARGET_NAME)_libretro_android.so
	fpic += -fPIC
	SHARED := -lstdc++ -lstd++fs -llog -lz -shared -Wl,--version-script=link.T -Wl,--no-undefined
	CFLAGS +=  -g -O2
	FLAGS += -DANDROID
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
endif

# MacOSX
ifeq ($(platform), osx)
	FLAGS += -D__APPLE__
endif

# ChaiGame
SOURCES_CXX += $(wildcard \
	src/*.cpp \
	src/chaigame/*.cpp \
	test/*.cpp \
	src/chaigame/graphics/*.cpp \
	src/chaigame/input/*.cpp \
	src/chaigame/audio/*.cpp \
	src/chaigame/system/*.cpp \
)

# PhysFS
SOURCES_C += $(wildcard \
	vendor/physfs/extras/physfsrwops.c \
	vendor/physfs/src/*.c \
)

# SDL_tty
SOURCES_C += $(wildcard \
	vendor/SDL_tty/src/SDL_tty.c \
	vendor/SDL_tty/src/SDL_fnt.c \
)

# SDL_gfx
SOURCES_C += $(wildcard \
	vendor/sdl-libretro/tests/SDL_gfx-2.0.26/*.c \
)

# SDL_ttf
SOURCES_C += $(wildcard \
	vendor/sdl-libretro/tests/SDL_ttf-2.0.11/SDL_*.c \
)
# TODO: Add freetype lib sources.

# SDL
ifeq ($(platform), win)
	SDL_SOURCES_C += $(wildcard ./vendor/sdl-libretro/src/*.c  ./vendor/sdl-libretro/src/audio/*.c  ./vendor/sdl-libretro/src/cdrom/win32/*.c  ./vendor/sdl-libretro/src/cdrom/*.c  ./vendor/sdl-libretro/src/cpuinfo/*.c  ./vendor/sdl-libretro/src/events/*.c  ./vendor/sdl-libretro/src/file/*.c  ./vendor/sdl-libretro/src/stdlib/*.c  ./vendor/sdl-libretro/src/thread/*.c  ./vendor/sdl-libretro/src/timer/*.c  ./vendor/sdl-libretro/src/video/*.c  ./vendor/sdl-libretro/src/joystick/*.c  ./vendor/sdl-libretro/src/video/libretro/*.c  ./vendor/sdl-libretro/src/joystick/libretro/*.c  ./vendor/sdl-libretro/src/timer/libretro/*.c  ./vendor/sdl-libretro/src/audio/libretro/*.c  ./vendor/sdl-libretro/src/thread/win32/SDL_sysmutex.c ./vendor/sdl-libretro/src/thread/win32/SDL_syssem.c ./vendor/sdl-libretro/src/thread/win32/SDL_systhread.c ./vendor/sdl-libretro/src/thread/generic/SDL_syscond.c ./vendor/sdl-libretro/src/loadso/dummy/*.c)
else
	SDL_SOURCES_C += $(wildcard ./vendor/sdl-libretro/src/*.c ./vendor/sdl-libretro/src/audio/*.c  ./vendor/sdl-libretro/src/cdrom/linux/*.c  ./vendor/sdl-libretro/src/cdrom/*.c  ./vendor/sdl-libretro/src/cpuinfo/*.c  ./vendor/sdl-libretro/src/events/*.c  ./vendor/sdl-libretro/src/file/*.c  ./vendor/sdl-libretro/src/stdlib/*.c  ./vendor/sdl-libretro/src/thread/*.c  ./vendor/sdl-libretro/src/timer/*.c  ./vendor/sdl-libretro/src/video/*.c  ./vendor/sdl-libretro/src/joystick/*.c  ./vendor/sdl-libretro/src/video/libretro/*.c  ./vendor/sdl-libretro/src/thread/pthread/*.c ./vendor/sdl-libretro/src/joystick/libretro/*.c  ./vendor/sdl-libretro/src/timer/libretro/*.c  ./vendor/sdl-libretro/src/audio/libretro/*.c  ./vendor/sdl-libretro/src/loadso/dummy/*.c)
endif

OBJECTS += $(SDL_SOURCES_C:.c=.o) $(SOURCES_CXX:.cpp=.o) $(SOURCES_C:.c=.o)

# Build all the dependencies, and the core.
all: | dependencies	$(TARGET)

ifeq ($(DEBUG), 0)
   FLAGS += -O3 -ffast-math -fomit-frame-pointer
else
   FLAGS += -O0 -g
endif

LDFLAGS +=  $(fpic) $(SHARED) \
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
	-Ivendor/stb

WARNINGS :=

ifeq ($(HAVE_CHAISCRIPT),)
	FLAGS += -D__HAVE_CHAISCRIPT__ -DCHAISCRIPT_NO_THREADS -DCHAISCRIPT_NO_THREADS_WARNING
endif
ifneq ($(HAVE_TESTS),)
	FLAGS += -D__HAVE_TESTS__
endif

FLAGS += -D__LIBRETRO__ $(ENDIANNESS_DEFINES) $(WARNINGS) $(fpic)

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
