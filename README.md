# ChaiLove
[![Build Status](https://travis-ci.org/libretro/libretro-chailove.svg?branch=master)](https://travis-ci.org/libretro/libretro-chailove)
[![platform libretro](https://img.shields.io/badge/platform-libretro-brightgreen.svg)](http://buildbot.fiveforty.net/admin/buildbot/build/?name=chailove)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://rawgit.com/libretro/libretro-chailove/docs/)

Framework to make 2D games with [ChaiScript](http://chaiscript.com/) and [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com). It's free, open-source, and works on Windows, Mac OS X, Linux, and ARM.

[![Floppy Bird Gameplay](docs/screenshot.png)](https://www.youtube.com/watch?v=RLVwTh6qDFI&hd=1)

## Games

- [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)
- [Nyan Cat](https://github.com/RobLoach/ChaiLove-NyanCat)
- [Snake](examples/snake/Snake.chai)
- [Game of Life](https://github.com/RobLoach/ChaiLove-GameOfLife)
- [... and more](https://github.com/topics/chailove)

## Usage

ChaiLove is a [libretro](https://www.libretro.com/) core, which can be run through [RetroArch](http://retroarch.com/). [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird) is a [free game you can download and play](https://www.youtube.com/watch?v=RLVwTh6qDFI)...

1. Run [RetroArch](http://retroarch.com/)
2. *Online Updater* → *Core Updator* → *ChaiLove*
3. *Online Updater* → *Content Downloader* → *ChaiLove* → *Floppy Bird*
4. *Load Content* → *Downloads* → *Floppy Bird.chailove*

Alternatively, you can run the ChaiLove core through RetroArch via the command line:

```
wget https://buildbot.libretro.com/assets/cores/ChaiLove/Floppy%20Bird.chailove
retroarch -L chailove_libretro.so Floppy\ Bird.chailove
```

## API

The [ChaiLove API](https://rawgit.com/libretro/libretro-chailove/docs/) is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a [simple Hello World example](examples/simple/main.chai):

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

### Compiling

Use the following command to compile the core:

```
make
```

### Testing

Run the automated tests by executing:

```
make test
```

Run the usability tests with:

```
retroarch -L chailove_libretro.so test/main.chai
```

### Documentation

Visit the [ChaiLove API documentation](https://rawgit.com/libretro/libretro-chailove/docs/). Build it through [Doxygen](http://www.stack.nl/~dimitri/doxygen/) by using:

```
make docs
```

## Authors

The following individuals contributed to ChaiLove:

- [@RobLoach](http://github.com/robloach)
- [sdl-libretro](https://github.com/r-type/sdl-libretro) by [@r-type](https://github.com/r-type)
- [Logo](docs/chailove.png) by [@baxysquare](https://github.com/baxysquare)
