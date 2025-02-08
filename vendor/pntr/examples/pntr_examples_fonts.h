void pntr_examples_fonts() {
    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);

    // Default Font
    pntr_font* defaultFont = pntr_load_font_default();

    pntr_draw_image(canvas, defaultFont->atlas, 0, 0);

    // Font Drawing
    pntr_draw_text(canvas, defaultFont, "Default Font Example", 10, 50, PNTR_BLACK);

    // BM Font
    pntr_font* bmFont = pntr_load_font_bmf("resources/bmfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/");
    pntr_draw_rectangle_fill(canvas, 0, 90, 200, 20, PNTR_BLACK);
    pntr_draw_text(canvas, bmFont, "BM Font Example", 10, 90, PNTR_WHITE);

    // TTY Font
    pntr_font* ttyFont = pntr_load_font_tty("resources/ttyfont-16x16.png", 16, 16,
        "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
    pntr_color background = pntr_get_color(0x0000caff);
    pntr_color border = pntr_get_color(0x8a8affff);
    pntr_draw_rectangle_fill(canvas, 0, 120, canvas->width, 60, border);
    pntr_draw_rectangle_fill(canvas, 0, 130, canvas->width, 40, background);

    const char* text = "*** TTY Font Example ***";
    int textWidth = pntr_measure_text(ttyFont, text);
    pntr_draw_text(canvas, ttyFont, text, canvas->width / 2 - textWidth / 2, 140, PNTR_WHITE);

    // TTF Font
    pntr_font* ttfFont = pntr_load_font_ttf("resources/tuffy.ttf", 28);
    const char* ttfText = "Привіт Світ!";
    pntr_vector textSize = pntr_measure_text_ex(ttfFont, ttfText, 0);
    pntr_draw_text(canvas, ttfFont, ttfText, 200, 20, PNTR_DARKPURPLE);

    // Resize the default font
    pntr_font* resizedFont = pntr_font_scale(defaultFont, 2.0f, 2.0f, PNTR_FILTER_NEARESTNEIGHBOR);
    pntr_draw_text(canvas, resizedFont, "Blue Text", 10, 65, PNTR_BLUE);
    pntr_unload_font(resizedFont);

    // Word-wrapped
    pntr_draw_rectangle(canvas, 225, 50, 150, 60, PNTR_BLUE);
    pntr_draw_text_wrapped(canvas, bmFont, "The quick brown fox jumps over the lazy dog.", 225, 50, 150, PNTR_RED);

    pntr_save_image(canvas, "pntr_examples_fonts.png");

    pntr_unload_font(defaultFont);
    pntr_unload_font(ttyFont);
    pntr_unload_font(bmFont);
    pntr_unload_font(ttfFont);
    pntr_unload_image(canvas);
}
