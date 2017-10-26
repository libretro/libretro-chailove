# ChaiGame [![Build Status](https://travis-ci.org/RobLoach/ChaiGame.svg?branch=master)](https://travis-ci.org/RobLoach/ChaiGame) [![Build Status](https://img.shields.io/badge/platform-libretro-green.png)](http://buildbot.fiveforty.net/admin/buildbot/build/?name=chaigame)

Framework to make 2D games with [ChaiScript](http://chaiscript.com/) and [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com).

![ChaiGame Benchmark Screenshot](examples/benchmark/screenshot.png)

## Sample Games

- [Floppy Bird](https://github.com/RobLoach/ChaiGame-FloppyBird)

## Usage

ChaiGame is a [libretro](https://www.libretro.com/) core, which can be run through [RetroArch](http://retroarch.com/). To play [Floppy Bird](https://github.com/RobLoach/ChaiGame-FloppyBird), run RetroArch and...

1. Run [RetroArch](http://retroarch.com/)
2. Download the ChaiGame core through RetroArch at *Online Updater* → *Core Updator* → *ChaiGame*
3. Download *Floppy Bird* through RetroArch at *Online Updater* → *Content Downloader* → *ChaiGame* → *Floppy Bird*
4. Launch the game over through *Load Content* → *Downloads* → *Floppy Bird.chaigame*

## API

ChaiGame is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a Hello World sample application:

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
retroarch -L chaigame_libretro.so main.chai
```

## Development

Building ChaiGame takes some time, so have patience. Use the following command to compile the core:

```
make
```

### Testing

To compile and run the testing framework, use:

```
make examples
```

### Flags

There are a few flags you can enable to change how Chai is compiled and used.

- `HAVE_CHAISCRIPT=0` Remove the scripting environment for fast compilation
- `HAVE_TESTS=1` Enables [`test/Test.cpp`](Test.cpp) for testing

```
make HAVE_CHAISCRIPT=0 HAVE_TESTS=1
```
