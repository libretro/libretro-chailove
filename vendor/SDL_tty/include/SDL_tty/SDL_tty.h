/**
 ** Copyright (c) 2006 Ingo Ruhnke <grumbel@gmail.com>
 **
 ** This software is provided 'as-is', without any express or implied
 ** warranty. In no event will the authors be held liable for any
 ** damages arising from the use of this software.
 **
 ** Permission is granted to anyone to use this software for any
 ** purpose, including commercial applications, and to alter it and
 ** redistribute it freely, subject to the following restrictions:
 **
 **   1. The origin of this software must not be misrepresented; you
 **      must not claim that you wrote the original software. If you
 **      use this software in a product, an acknowledgment in the
 **      product documentation would be appreciated but is not
 **      required.
 **
 **   2. Altered source versions must be plainly marked as such, and
 **      must not be misrepresented as being the original software.
 **
 **   3. This notice may not be removed or altered from any source
 **      distribution.
 **
 */

#ifndef _SDL_TTY_H
#define _SDL_TTY_H

#include <SDL.h>
#include "SDL_fnt.h"

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

#define TTY_MAJOR_VERSION  0;
#define TTY_MINOR_VERSION  0;
#define TTY_PATCH_VERSION  2;

/** Reuse SDL functions for error reporting */
#define TTY_SetError	SDL_SetError
#define TTY_GetError	SDL_GetError

typedef struct TTY
{
  /**
   *  The buffer containing all characters for display, access via
   *  framebuffer[y][x]
   */
  char** framebuffer;

  /**
   *  The font that is used at default for rendering the framebuffer
   */
  TTY_Font* font;

  /**
   *  The width of the framebuffer
   */
  int width;

  /**
   *  The height of the framebuffer
   */
  int height;

  /**
   *  The cursors x position in the framebuffer in screen coordinates,
   *  use TTY_SetCursor() to avoid trouble when scrolling
   */
  int cursor_x;

  /**
   *  The cursors y position in the framebuffer in screen coordinates,
   *  use TTY_SetCursor() to avoid trouble when scrolling
   */
  int cursor_y;

  /**
   *  The character that should be used to display the cursor
   */
  int cursor_character;

  /**
   *  If set the cursor is displayed
   */
  int print_cursor;

  /**
   *  The scroll offset in x direction
   */
  int scroll_x;

  /**
   *  The scroll offset in x direction
   */
  int scroll_y;

}  TTY;

/**
 *  Allocate a new TTY with the given dimensions and font.
 *
 *  @param width  The width of the terminal in characters
 *  @param height The height of the terminal in characters
 *  @param font   The font used for displaying the terminal, the font
 *                will not be freed upon TTY_Free()

 */
TTY* TTY_Create(int width, int height, TTY_Font* font);

/**
 *  Deallocate a given TTY
 */
void TTY_Free(TTY* tty);

/**
 *  Set the current cursor position to \a x, \a y, if x or y are
 *  outside the range of the TTY, they automatically wrap around
 */
void TTY_SetCursor(TTY* tty, int x, int y);

/**
 *  Write the current cursor position to \a x and \a y
 */
void TTY_GetCursor(TTY* tty, int* x, int* y);

void TTY_SetScrollOffset(TTY* tty, int  scroll_x, int  scroll_y);
void TTY_GetScrollOffset(TTY* tty, int* scroll_x, int* scroll_y);

/**
 *  Use character chr as the cursor
 */
void TTY_SetCursorCharacter(TTY* tty, int chr);

/**
 *  If \a i is set, display a cursor, if \a i is 0, don't display it
 */
void TTY_EnableVisibleCursor(TTY* tty, int i);

/**
 *  Clear the tty's framebuffer
 */
void TTY_Clear(TTY* tty);

/**
 *  Append the content of \a buffer to the given \a tty, \a len gives
 *  the length of the buffer.
 */
void TTY_write(TTY* tty, const char* buffer, int len);

/**
 *  Append the content of \a buffer to the given \a tty, \a buffer
 *  must be '\0' terminated.
 */
void TTY_print(TTY* tty, const char* buffer);

/**
 *  Get the character at position \a x, \a y
 */
char TTY_GetChar(TTY* tty, int x, int y);

/**
 *  Append chr to \a tty
 */
void TTY_putchar(TTY* tty, char chr);

/**
 *  Put\a chr at the current cursor position without advancing the cursor
 */
void TTY_putchar_nomove(TTY* tty, char chr);

/**
 *  printf like way to append content to \a tty
 */
void TTY_printf(TTY* tty, const char *fmt, ...)  __attribute__ ((format (printf, 2, 3)));

/**
 *  Blit \a tty given to the surface \a screen at the given coordinates \a x and \a y
 */
void TTY_Blit(TTY* tty, SDL_Surface* screen, int x, int y);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif

/* EOF */
