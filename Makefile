TARGET_NAME := chailove

include Makefile.libretro
include Makefile.common

ifeq ($(STATIC_LINKING),1)
	FLAGS += -DSTATIC_LINKING
endif

FLAGS += -D__LIBRETRO__ $(COREDEFINES) $(ENDIANNESS_DEFINES) $(PLATFORM_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -fpermissive -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

ifeq ($(platform), osx)
	CXXFLAGS += -stdlib=libc++ -mmacosx-version-min=10.9
endif

$(TARGET): $(OBJECTS) | dependencies
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp | dependencies
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c | dependencies
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
