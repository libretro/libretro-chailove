# ChaiLove
[![Build Status](https://travis-ci.org/RobLoach/ChaiLove.svg?branch=master)](https://travis-ci.org/RobLoach/ChaiLove) [![platform libretro](https://img.shields.io/badge/platform-libretro-brightgreen.svg)](http://buildbot.fiveforty.net/admin/buildbot/build/?name=chailove)

Framework to make 2D games with [ChaiScript](http://chaiscript.com/) and [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com).

![ChaiLove Benchmark Screenshot](examples/benchmark/screenshot.png)

## Games

- [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)

## Usage

ChaiLove is a [libretro](https://www.libretro.com/) core, which can be run through [RetroArch](http://retroarch.com/). To play the sample game [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)...

1. Run [RetroArch](http://retroarch.com/)
2. *Online Updater* → *Core Updator* → *ChaiLove*
3. *Online Updater* → *Content Downloader* → *ChaiLove* → *Floppy Bird*
4. *Load Content* → *Downloads* → *Floppy Bird.chailove*

You can also run ChaiLove through the command line by using:

```
retroarch -L chailove_libretro.so path/to/FloppyBird.chailove
```

## API

The [ChaiLove API](https://robloach.github.io/ChaiLove/) is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a [simple Hello World example](examples/simple/main.chai):

``` lua
global logo

def load() {
	logo = graphics.newImage("logo.png")
}

def draw() {
    graphics.print("Hello World!", 400, 300)
    graphics.draw(logo, 100, 100)
}

def update(delta) {
	// Change something on the screen.
}
```

To run it, execute the following:

```
retroarch -L chailove_libretro.so main.chai
```

## Development

Building ChaiLove takes some time, so have patience. Use the following command to compile the core:

```
make
```

### Testing

To compile and run the testing framework, use:

```
retroarch -L chailove_libretro.so test/main.chai
```

You can run the unit tests, by executing:

```
make unit
```

### Documentation

Visit the [ChaiLove API documentation](https://robloach.github.io/ChaiLove/). Build it by using:

```
make docs
```

### Flags

There are a few flags you can enable to change how Chai is compiled and used.

- `HAVE_CHAISCRIPT=0` Remove the scripting environment for fast compilation
- `HAVE_TESTS=1` Enables [`test/Test.cpp`](Test.cpp) for native testing

```
make HAVE_CHAISCRIPT=0 HAVE_TESTS=1
```
