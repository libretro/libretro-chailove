/**
 * @page gettingstarted Getting Started
 *
 * This provides a quick introduction on how to get started with [ChaiLove](http://github.com/libretro/libretro-chailove).
 *
 * ## 1. Install ChaiLove
 *
 * ChaiLove is a [libretro](https://www.libretro.com/) core, which can be run through [RetroArch](http://retroarch.com/). It can be installed through the user interface...
 * 1. Run [RetroArch](http://retroarch.com/)
 * 2. *Online Updater* → *Core Updator* → *ChaiLove*
 *
 * ## 2. Running Games
 *
 * ChaiLove can load a game in two ways:
 *
 * 1. Run the `main.chai` file
 * 2. Run the compressed `game.chailove` file
 *
 * To download and play the sample game, [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)...
 *
 * 1. Run RetroArch
 * 2. Visit *Online Updater* → *Content Downloader* → *ChaiLove* → *Floppy Bird*
 * 3. *Load Content* → *Downloads* → *Floppy Bird.chailove*
 *
 * To run games through the command line...
 *
 * @code
 * retroarch -L chailove_libretro.so FloppyBird.chailove
 * @endcode
 *
 * ## Next Steps
 *
 * - \link love::script Callbacks \endlink will teach you about the basic structure of a ChaiLove game.
 * - \link ::love love \endlink module will show you the API available.
 * - [Examples](https://git.io/vxPmn) are some useful learning resources.
 * - \link games Games \endlink provides some example games using ChaiLove.
 */
