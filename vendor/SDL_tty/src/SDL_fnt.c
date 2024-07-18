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

#include "SDL_tty.h"
#include "SDL_fnt.h"

char *
FNT_create_string(const char *fmt, va_list ap)
{
  /* Guess we need no more than 100 bytes. */
  int n, size = 100;
  char *p, *np;

  if ((p = (char*)malloc (size)) == NULL)
    return NULL;

  while (1) {
    /* Try to print in the allocated space. */
    //va_start(ap, fmt);

    n = vsnprintf (p, size, fmt, ap);
    va_end(ap);
    /* If that worked, return the string. */
    if (n > -1 && n < size)
      return p;
    /* Else try again with more space. */
    if (n > -1)    /* glibc 2.1 */
      size = n+1; /* precisely what is needed */
    else           /* glibc 2.0 */
      size *= 2;  /* twice the old size */
    if ((np = (char*)realloc (p, size)) == NULL) {
      free(p);
      return NULL;
    } else {
      p = np;
    }
  }
}

TTY_Font*
FNT_Create(SDL_Surface* surface, int glyph_width, int glyph_height, const char* letters)
{
  int i;
  TTY_Font* font = (TTY_Font*)malloc(sizeof(TTY_Font));

  font->surface = SDL_DisplayFormatAlpha(surface);

  if (!font->surface)
    {
      TTY_SetError("TTY_CreateFont: conversation of surface failed");
      return 0;
    }

  memset(font->transtbl, 0, 256);
  for(i = 0; letters[i] != '\0'; ++i)
    font->transtbl[(int)letters[i]] = i;

  font->glyph_width  = glyph_width;
  font->glyph_height = glyph_height;

  return font;
}

void
FNT_Free(TTY_Font* font)
{
  SDL_FreeSurface(font->surface);
  free(font);
}

void
FNT_GetGlyph(TTY_Font* font, char idx, SDL_Rect* rect)
{
  idx = font->transtbl[(int)idx];

  rect->x = (idx % (font->surface->w / font->glyph_width)) * font->glyph_width;
  rect->y = (idx / (font->surface->w / font->glyph_width)) * font->glyph_height;

  rect->w = font->glyph_width;
  rect->h = font->glyph_height;
}

void
FNT_Printf(TTY_Font* font, SDL_Surface* screen, int x, int y, Uint32 flags, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char* str = FNT_create_string(fmt, ap);
  FNT_Print(font, screen, x, y, flags, str);
  free(str);
}

int
FNT_GetGlyphWidth(TTY_Font* font, char c)
{
  return font->glyph_width;
}

int
FNT_GetGlyphHeight(TTY_Font* font, char c)
{
  return font->glyph_height;
}

int
FNT_GetTextHeight(TTY_Font* font, const char* text)
{
  int lines = 1;
  int i;
  for(i = 0; text[i] != '\0'; ++i)
    {
      if (text[i] == '\n')
        {
          lines += 1;
        }
    }
  return lines * font->glyph_height;
}

int
FNT_GetTextWidth(TTY_Font* font, const char* text)
{
  int longest_line = 0;
  int line = 0;
  int i;
  for(i = 0; text[i] != '\0'; ++i)
    {
      if (text[i] == '\n')
        {
          if (line > longest_line)
            longest_line = line;
          line = 0;
        }
      else
        {
          line += 1;
        }
    }

  if (line > longest_line)
    longest_line = line;

  return longest_line * font->glyph_width;
}

int FNT_GetTextLineWidth(TTY_Font* font, const char* text)
{
  int i;
  for(i = 0; text[i] != '\0' && text[i] != '\n'; ++i);
  return i * font->glyph_width;
}

void
FNT_Print(TTY_Font* font, SDL_Surface* screen, int x, int y, Uint32 flags, const char *str)
{
  /* FIXME: If flags is 0 this code will not behave correctly, should default to FNT_ALIGN_LEFT if flags is 0  */

  SDL_Rect src_rect;
  SDL_Rect dst_rect;

  int x_of = 0;
  int y_of = 0;

  int i;

  int text_width  = FNT_GetTextWidth(font, str);
  int text_height = FNT_GetTextHeight(font, str);

  if ((flags & FNT_ALIGN_LEFT) && (flags & FNT_ALIGN_RIGHT))
    {
      x -= text_width/2;
    }
  else if (flags & FNT_ALIGN_LEFT)
    {
    }
  else if (flags & FNT_ALIGN_RIGHT)
    {
      x -= text_width;
    }

  if ((flags & FNT_ALIGN_TOP) && (flags & FNT_ALIGN_BOTTOM))
    {
      y -= text_height/2;
    }
  else if (flags & FNT_ALIGN_TOP)
    {
    }
  else if (flags & FNT_ALIGN_BOTTOM)
    {
      y -= text_height;
    }

  for(i = 0; str[i] != '\0'; ++i)
    {
      if (str[i] == '\n')
        {
          if ((flags & FNT_ALIGN_LEFT) && (flags & FNT_ALIGN_RIGHT))
            {
              x_of = text_width/2 - FNT_GetTextLineWidth(font, str+i+1)/2;
            }
          else if (flags & FNT_ALIGN_LEFT)
            {
              x_of = 0;
            }
          else if (flags & FNT_ALIGN_RIGHT)
            {
              x_of = text_width - FNT_GetTextLineWidth(font, str+i+1);
            }

          y_of += font->glyph_height;
        }
      else
        {
          FNT_GetGlyph(font, str[i], &src_rect);

          dst_rect.x = x + x_of;
          dst_rect.y = y + y_of;

          SDL_BlitSurface(font->surface, &src_rect, screen, &dst_rect);

          x_of += font->glyph_width;
        }
    }
}

/* EOF */
