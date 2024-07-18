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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_tty.h"
#include <string.h>

static int modulo(int x, int y)
{
  int xmody = x - (x / y) * y;
  if (xmody && ((y ^ xmody) < 0)) {
    xmody += y;
  }
  return xmody;
}

TTY*
TTY_Create(int width, int height, TTY_Font* font)
{
  int i;
  TTY* tty = (TTY*)malloc(sizeof(TTY));

  // SDL_Surface* temp = TTY_CreateRGBSurface(font8x12);
  // SDL_Surface* temp = IMG_Load("c64_16x16.png");

  //tty->font = TTY_CreateFont(temp, 16, 16,
  //                         "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  //                         "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  tty->font = font;

  //SDL_FreeSurface(temp);

  /* Create Framebuffer */
  tty->framebuffer = (char**)malloc(sizeof(char*) * height);
  for(i = 0; i < height; ++i)
    tty->framebuffer[i] = (char*)malloc(sizeof(char) * width);

  tty->width  = width;
  tty->height = height;

  tty->cursor_character = 0;
  tty->print_cursor     = 0;

  tty->scroll_x = 0;
  tty->scroll_y = 0;

  tty->cursor_x = 0;
  tty->cursor_y = 0;

  TTY_Clear(tty);

  return tty;
}

void
TTY_Free(TTY* tty)
{
  int i;

  // TTY_FreeFont(tty->font);

  for(i = 0; i < tty->height; ++i)
    free(tty->framebuffer[i]);
  free(tty->framebuffer);

  free(tty);
}

void TTY_SetScrollOffset(TTY* tty, int scroll_x, int scroll_y)
{
  tty->scroll_x = scroll_x;
  tty->scroll_y = scroll_y;
}

void TTY_GetScrollOffset(TTY* tty, int* scroll_x, int* scroll_y)
{
  *scroll_x = tty->scroll_x;
  *scroll_y = tty->scroll_y;
}

void TTY_SetCursor(TTY* tty, int x, int y)
{
  tty->cursor_x = modulo(x + tty->scroll_x, tty->width);
  tty->cursor_y = modulo(y + tty->scroll_y, tty->height);
}

void TTY_GetCursor(TTY* tty, int* x, int* y)
{
  *x = tty->cursor_x - tty->scroll_x;
  *y = tty->cursor_y - tty->scroll_y;
}

void TTY_Clear(TTY* tty)
{
  int y;
  for(y = 0; y < tty->height; ++y)
    memset(tty->framebuffer[y], 0, tty->width);
}

void TTY_putchar_nomove(TTY* tty, char chr)
{
  if (chr != '\n' && chr != '\r')
    tty->framebuffer[tty->cursor_y][tty->cursor_x] = chr;
}

void TTY_putchar(TTY* tty, char chr)
{
  if (chr == '\n')
    {
      tty->cursor_x = modulo(tty->scroll_x, tty->width);
      tty->cursor_y = modulo(tty->cursor_y  + 1, tty->height);

      if (modulo(tty->cursor_y - tty->scroll_y, tty->height) == 0)
        {
          tty->scroll_y = modulo(tty->scroll_y + 1, tty->height);
          memset(tty->framebuffer[tty->cursor_y], 0, tty->width);
        }
    }
  else if (chr == '\r')
    {
      tty->cursor_x = tty->scroll_x;
    }
  else
    {
      tty->framebuffer[tty->cursor_y][tty->cursor_x] = chr;

      tty->cursor_x += 1;
      if (tty->cursor_x == tty->width)
        {
          tty->cursor_x = tty->scroll_x;
          tty->cursor_y = modulo(tty->cursor_y  + 1, tty->height);

          if (modulo(tty->cursor_y - tty->scroll_y, tty->height) == 0)
            {
              tty->scroll_y = modulo(tty->scroll_y + 1, tty->height);
              memset(tty->framebuffer[tty->cursor_y], 0, tty->width);
            }
        }
    }
}

char TTY_GetChar(TTY* tty, int x, int y)
{
  x = modulo(x + tty->scroll_x, tty->width);
  y = modulo(y + tty->scroll_y, tty->height);

  return tty->framebuffer[y][x];
}

void TTY_write(TTY* tty, const char* buffer, int len)
{
  int i;
  for(i = 0; i < len; ++i)
    TTY_putchar(tty, buffer[i]);
}

void TTY_print(TTY* tty, const char* buffer)
{
  TTY_write(tty, buffer, strlen(buffer));
}

void TTY_SetCursorCharacter(TTY* tty, int chr)
{
  tty->cursor_character = chr;
}

void TTY_EnableVisibleCursor(TTY* tty, int i)
{
  tty->print_cursor = i;
}

void TTY_Blit(TTY* tty, SDL_Surface* screen, int screen_x, int screen_y)
{
  SDL_Rect src_rect;
  SDL_Rect dst_rect;

  int x;
  int y;
  for(y = 0; y < tty->height; ++y)
    {
      for(x = 0; x < tty->width; ++x)
        {
          if (tty->print_cursor)
            {
              if (modulo(x + tty->scroll_x, tty->width)  == tty->cursor_x &&
                  modulo(y + tty->scroll_y, tty->height) == tty->cursor_y &&
                  (SDL_GetTicks()/200) % 2 == 0)
                {
                  FNT_GetGlyph(tty->font, tty->cursor_character, &src_rect);

                  dst_rect.x = screen_x + x * tty->font->glyph_width;
                  dst_rect.y = screen_y + y * tty->font->glyph_height;

                  SDL_BlitSurface(tty->font->surface, &src_rect, screen, &dst_rect);
                }
              else
                {
                  char chr = tty->framebuffer[modulo(y + tty->scroll_y, tty->height)][modulo(x + tty->scroll_x, tty->width)];
                  if (chr)
                    {
                      FNT_GetGlyph(tty->font, chr, &src_rect);

                      dst_rect.x = screen_x + x * tty->font->glyph_width;
                      dst_rect.y = screen_y + y * tty->font->glyph_height;

                      SDL_BlitSurface(tty->font->surface, &src_rect, screen, &dst_rect);
                    }
                }
            }
          else
            {
              char chr = tty->framebuffer[modulo(y + tty->scroll_y, tty->height)][modulo(x + tty->scroll_x, tty->width)];
              if (chr)
                {
                  FNT_GetGlyph(tty->font, chr, &src_rect);

                  dst_rect.x = screen_x + x * tty->font->glyph_width;
                  dst_rect.y = screen_y + y * tty->font->glyph_height;

                  SDL_BlitSurface(tty->font->surface, &src_rect, screen, &dst_rect);
                }
            }
        }
    }
}

void TTY_printf(TTY* tty, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char* str = FNT_create_string(fmt, ap);
  TTY_print(tty, str);
  free(str);
}

/* EOF */
