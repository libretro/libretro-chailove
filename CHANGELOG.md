# Changelog
All notable changes to [ChaiLove](https://github.com/RobLoach/ChaiLove) will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## 0.12.0 - 2017-12-13
### Added
- `SoundData.getVolume()`
- `SoundData.setVolume()`

### Changed
- Updated C++ namespace from `Modules` to `love`
- [Method chaining](https://en.wikipedia.org/wiki/Method_chaining) for most functions
    ```
    graphics.love.point(100,100).point(50, 200)
    ```
- Moved `Types` namespace to `love::Types`

## 0.11.1 - 2017-12-10
### Fixed
- Version number

## 0.11.0 - 2017-12-09
### Added
- `love` namespace
  - Example: `love.graphics.draw()`
- `love.graphics.draw()` rotation and scaling
- `love.graphics.setDefaultFilter()`
- `love.graphics.getDefaultFilter()`

### Changed
- [ChaiScript_Extras](https://github.com/ChaiScript/ChaiScript_Extras) now using original source as upstream issue is fixed
- Updated [libretro-common](http://github.com/libretro/libretro-common)
- Updated [random](https://github.com/libretro/sdl-libretro)
- Updated [sdl-libretro](https://github.com/libretro/sdl-libretro)

### Fixed
- `keyreleased()` callback parameter types

## 0.10.0 - 2017-11-30
### Added
- Mac support
- Unit testing

### Changed
- Coding standards

## 0.9.0 - 2017-11-25
### Added
- Namespace update
- Documentation
