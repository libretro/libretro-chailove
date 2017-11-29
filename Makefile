TARGET_NAME := chailove

include Makefile.libretro

ifeq ($(STATIC_LINKING),1)
	FLAGS += -DSTATIC_LINKING
endif

FLAGS += -D__LIBRETRO__ $(COREDEFINES) $(ENDIANNESS_DEFINES) $(PLATFORM_DEFINES) $(WARNINGS) $(fpic)

CXXFLAGS += $(FLAGS) -fpermissive -std=c++14
CFLAGS += $(FLAGS) -std=gnu99

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
	@echo "Execute the following to run tests:\n\n    retroarch -L $(TARGET) test/main.chai\n    make unit\n\n"

vendor/noarch/noarch: dependencies
	cd vendor/noarch && make

unit: vendor/noarch/noarch
	vendor/noarch/noarch $(CORE_DIR)/chailove_libretro.so test/unittests/main.chai

examples: all
	retroarch -L $(TARGET) examples/benchmark/main.chai

test-script: all
	retroarch -L $(TARGET) test/main.chai

docs: dependencies
	doxygen docs/Doxyfile

docs-deploy: docs
	npm install push-dir && node_modules/.bin/push-dir --dir=docs/html --branch=gh-pages

noscript: dependencies
	$(MAKE) HAVE_CHAISCRIPT=0 HAVE_TESTS=1

test-noscript: noscript
	retroarch -L $(TARGET) test/main.chai

PREFIX := /usr
INSTALLDIR := $(PREFIX)/lib/libretro
install: all
	mkdir -p $(DESTDIR)$(INSTALLDIR)
	cp $(TARGET) $(DESTDIR)$(INSTALLDIR)
