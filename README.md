# ChaiGame [![Build Status](https://travis-ci.org/RobLoach/ChaiGame.svg?branch=master)](https://travis-ci.org/RobLoach/ChaiGame)

Framework to make 2D games with [ChaiScript](http://chaiscript.com/) and [libretro](https://www.libretro.com)/[RetroArch](http://retroarch.com).

![ChaiGame Benchmark Screenshot](examples/benchmark/screenshot.png)

## Games

- [FlappyBird](https://github.com/RobLoach/chaigame-flappybird)

## Usage

ChaiGame is roughly inspired by the [LÖVE API](https://love2d.org/wiki/Main_Page). The following `main.chai` is a Hello World sample application:

``` lua
def load() {
	// Load assets.
}

def draw() {
    graphics.print("Hello World!", 400, 300)
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
