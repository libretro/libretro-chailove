# ChaiLove
[![Build Status](https://travis-ci.org/libretro/libretro-chailove.svg?branch=master)](https://travis-ci.org/libretro/libretro-chailove)
[![platform libretro](https://img.shields.io/badge/platform-libretro-brightgreen.svg)](http://buildbot.fiveforty.net/admin/buildbot/build/?name=chailove)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://robloach.github.io/ChaiLove)

Framework to make 2D games with [ChaiScript](http://chaiscript.com/) and [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com). It's free, open-source, and works on Windows, Mac OS X, Linux, and ARM.

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

The [ChaiLove API](https://libretro.github.io/libretro-chailove/) is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a [simple Hello World example](examples/simple/main.chai):

``` lua
global logo

def load() {
	logo = love.graphics.newImage("logo.png")
}

def draw() {
	love.graphics.print("Hello World!", 400, 300)
	love.graphics.draw(logo, 100, 100)
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

Behind ChaiLove, there's the documentation, compiling it, along with testing.

### Documentation

Visit the [ChaiLove API documentation](https://libretro.github.io/libretro-chailove/). Build it through [Doxygen](http://www.stack.nl/~dimitri/doxygen/) by using:

```
make docs
```

### Compiling

Use the following command to compile the core:

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
make unittest
```

## Authors

The following individuals contributed to ChaiLove:

- [@RobLoach](http://github.com/robloach)
- [sdl-libretro](https://github.com/r-type/sdl-libretro) by [@r-type](https://github.com/r-type)
- [Logo](docs/chailove.png) by [@baxysquare](https://github.com/baxysquare)
