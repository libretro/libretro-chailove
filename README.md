# ChaiGame

Experimental framework to make 2D games with [libretro](https://www.libretro.com), inspired by [LÖVE](https://love2d.org).

## Features

- [libretro](https://www.libretro.com)
- [SDL](https://www.libsdl.org)
- [ChaiScript](http://chaiscript.com)
- [PhysFS](https://www.icculus.org/physfs/)

## Usage

TODO: Add usage documentation.

## Development

Building takes some time, so be patient.

```
make
retroarch -L chaigame_libretro.so main.chai
```

### Flags

There are a few flags you can enable to change how Chai is compiled and used.

- `HAVE_CHAISCRIPT=0` Remove the scripting environment for fast compilation
- `HAVE_TESTS=1` Enables [`test/Test.cpp`](Test.cpp) for testing

```
make HAVE_CHAISCRIPT=0 HAVE_TESTS=1
```

### Testing

To compile and run the testing framework, use:

```
make test
```
