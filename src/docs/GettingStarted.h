/**
 * @page gettingstarted Getting Started
 *
 * This provides a quick introduction on how to get started with [ChaiLove](http://github.com/libretro/libretro-chailove).
 *
 * ## Get ChaiLove
 *
 * ChaiLove is a [libretro](https://www.libretro.com/) core, which can be run through [RetroArch](http://retroarch.com/). To play the sample game [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird)...
 * 1. Run [RetroArch](http://retroarch.com/)
 * 2. *Online Updater* → *Core Updator* → *ChaiLove*
 *
 * ## Running Games
 *
 * ChaiLove can load a game in two ways:
 *
 * 1. Run on a `main.chai` file
 * 2. Run on a compressed `game.chailove` file
 *
 * To [download and play](https://github.com/RobLoach/ChaiLove-FloppyBird/releases) the sample [Floppy Bird](https://github.com/RobLoach/ChaiLove-FloppyBird) game...
 * 1. Run RetroArch
 * 2. Visit *Online Updater* → *Content Downloader* → *ChaiLove* → *Floppy Bird*
 * 3. *Load Content* → *Downloads* → *Floppy Bird.chailove*
 *
 * To run games through ChaiLove manually through the command line interface...
 *
 * @code
 * retroarch -L chailove_libretro.so path/to/FloppyBird.chailove
 * @endcode
 *
 * ## Next Steps
 *
 * - \link love::script Callbacks \endlink will teach you about the basic structure of a ChaiLove game.
 * - \link ::love love \endlink module will show you the API available.
 * - [Examples](https://git.io/vxPmn) are some useful learning resources.
 * - \link games Games \endlink provides some example games using ChaiLove.
 */
