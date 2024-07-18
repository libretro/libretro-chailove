SDL_tty
=======

SDL_tty is a simple library that tries to simulate a primitive
terminal that allows you to print to the screen in much the same way
that you would print to stdout. The usage is like this:

    // Create the fixed width font
    SDL_Surface* temp = IMG_Load("fontfile.png");
    TTY_Font* font = TTY_CreateFont(temp, 16, 16,
                                    "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    // Create the terminal
    TTY* tty = TTY_Create(40, 30, font);

    // Your mainloop
    while(1)
    {
       // print text via
       TTY_printf(tty, "Hello World\n");

       // renderer the terminal to the screen
       TTY_Blit(tty, screen, 80, 60);

       SDL_Flip(screen);
    }

    TTY_Free(tty);
    TTY_FreeFont(font);

`fontdump`
----------

The `fontdump` utility can be used to generate header files that can
be included straight into the source code so that there are no
external dependencies:

	Usage: fontdump FONTNAME IMAGEFILE GLYPHWIDTH GLYPHHEIGHT GLYPHS

Example:

    fontdump font8x8 font8x8.png 8 8 \
      "\x7f !\\"#$$%&\'()*+,-./0123456789:;<=>?@\
      ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_\`abcdefghijklmnopqrstuvwxyz{|}~" \
      > font8x8.h


`c64lookalike`
--------------

The `c64lookalike` programm demonstrates some more advanced usage of
the library.

![Screenshot of c64lookalike](https://raw.githubusercontent.com/Grumbel/SDL_tty/master/c64_screenshot.png)


Features
--------

* can create a primitive terminal for text output
* some primitve support for scrolling
* support for fixed-width fonts
* support for loading fonts from file as well as directly from code, a
  image to .h converter is provided
* small and meant to be included in your source, not meant to be compiled as
  a real .so/dll library


Webpage/Contact
---------------

The latest version is currently available at:

* https://github.com/Grumbel/SDL_tty

Question and suggestion should go to:

  Ingo Ruhnke <grumbel@gmail.com>

