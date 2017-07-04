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

- `HAVE_CHAISCRIPT` Remove the scripting environment.

```
make HAVE_CHAISCRIPT=0
```
