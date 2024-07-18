#include <stdint.h>
#include <stdlib.h>

#include <SDL_image.h>

void write_escaped_string(FILE* out, char const* glyphs)
{
  int i;
  int len = strlen(glyphs);
  fputc('"', out);

  uint8_t const* codepoints = (uint8_t const*)glyphs;
  for(i = 0; i < len; ++i)
  {
    if (codepoints[i] == '"') {
      fprintf(out, "\\\"");
    } else if (codepoints[i] == '\\') {
      fprintf(out, "\\\\");
    } else if (codepoints[i] >= 0x7f) {
      fprintf(out, "\\x%x", (int)codepoints[i]);
    } else {
      fputc(codepoints[i], out);
    }
  }
  fputc('"', out);
}

int main(int argc, char** argv)
{
  if (argc != 6) {
    fprintf(stderr, "Usage: fontdump FONTNAME IMAGEFILE GLYPHWIDTH GLYPHHEIGHT GLYPHS\n");
    exit(EXIT_FAILURE);
  }

  if (SDL_Init(0) != 0) {
    fprintf(stderr, "error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  char const* font_name    = argv[1];
  int const glyph_width  = atoi(argv[3]);
  int const glyph_height = atoi(argv[4]);
  char const* glyphs       = argv[5];

  /* Dump code */
  SDL_Surface* surface = IMG_Load(argv[2]);
  if (!surface) {
    fprintf(stderr, "error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  {
    FILE* out = stdout;

    SDL_LockSurface(surface);
    fprintf(out, "/* automatically generated file */\n\n");
    fprintf(out, "char   %s_glyphs[] = ", font_name); write_escaped_string(out, glyphs); fprintf(out, ";\n");
    fprintf(out, "int    %s_width  = %d;\n", font_name, surface->w);
    fprintf(out, "int    %s_height = %d;\n", font_name, surface->h);
    fprintf(out, "int    %s_pitch  = %d;\n", font_name, surface->pitch);
    fprintf(out, "int    %s_bpp    = %d;\n", font_name, surface->format->BitsPerPixel);
    fputc('\n', out);
    fprintf(out, "Uint32 %s_rmask  = 0x%08x;\n", font_name, surface->format->Rmask);
    fprintf(out, "Uint32 %s_gmask  = 0x%08x;\n", font_name, surface->format->Gmask);
    fprintf(out, "Uint32 %s_bmask  = 0x%08x;\n", font_name, surface->format->Bmask);
    fprintf(out, "Uint32 %s_amask  = 0x%08x;\n", font_name, surface->format->Amask);
    fputc('\n', out);
    fprintf(out, "int    %s_glyph_width  = %d;\n", font_name, glyph_width);
    fprintf(out, "int    %s_glyph_height = %d;\n", font_name, glyph_height);
    fputc('\n', out);
    fprintf(out, "unsigned char %s_data[] = \n{\n  ", font_name);
    for(int i = 0; i < (surface->w * surface->h * 4); ++i)
    {
      fprintf(out, "0x%02x", ((unsigned char*)(surface->pixels))[i]);
      if (i != ((surface->w * surface->h * 4) - 1))
        fprintf(out, ", ");
      else
        fprintf(out, "\n");

      if (((i+1) % 12) == 0)
        fprintf(out, "\n  ");
    }
    fprintf(out, "};\n\n/* EOF */\n");
    fclose(out);
    SDL_UnlockSurface(surface);
  }

  return 0;
}

/* EOF */
