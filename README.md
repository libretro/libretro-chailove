# ChaiGame

Experimental framework to make 2D games with [libretro](https://www.libretro.com).

## Features

- [libretro](https://www.libretro.com)
- [SDL](https://www.libsdl.org)
- [ChaiScript](http://chaiscript.com)

## Usage

TODO: Add usage documentation.

## Development

```
make
retroarch -L chaigame_*
```

### Flags

There are a few flags you can enable to change how Chai is compiled and used.

- `DISABLE_CHAISCRIPT` Remove the scripting environment.

```
make DISABLE_CHAISCRIPT=true
```
