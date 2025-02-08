#define UNIT_TEST_PREFIX ""
#define UNIT_STATIC
#include "unit.h"

#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_UTF8

#define PNTR_IMPLEMENTATION
#define PNTR_ASSERT(condition) EQUALS((bool)(condition), true)
#include "../pntr.h"

#define COLOREQUALS PNTR_ASSERT_COLOR_EQUALS
#define IMAGEEQUALS PNTR_ASSERT_IMAGE_EQUALS
#define RECTEQUALS PNTR_ASSERT_RECT_EQUALS
#include "../pntr_assert.h"

bool pntr_utf8() {
    #ifdef PNTR_ENABLE_UTF8
        return true;
    #else
        return false;
    #endif
}

MODULE(pntr_math, {
    IT("PNTR_SINF", {
        EQUALS((int)PNTR_SINF(PNTR_PI / 2.0f), 1);
    });

    IT("PNTR_COSF", {
        float value = PNTR_COSF(PNTR_PI * 2.0f);
        if (value < 0.9f || value > 1.1f) {
            EQUALS(0, 1);
        }
    });

    IT("PNTR_CEILF", {
        EQUALS((int)PNTR_CEILF(2.4f), 3);
        EQUALS((int)PNTR_CEILF(-2.0f), -2);
        EQUALS((int)PNTR_CEILF(0.0f), 0);
    });

    IT("PNTR_FABS", {
        EQUALS((int)PNTR_FABSF(3.0f), 3);
        EQUALS((int)PNTR_FABSF(-3.0f), 3);
        EQUALS((int)PNTR_FABSF(0.0f), 0);
    });

    IT("PNTR_FLOORF", {
        EQUALS((int)PNTR_FLOORF(2.7f), 2);
        EQUALS((int)PNTR_FLOORF(-2.7f), -3);
        EQUALS((int)PNTR_FLOORF(0.0f), 0);
    });

    IT("PNTR_FMODF", {
        EQUALS((int)PNTR_FMODF(10.0f, 3.0f), 1);
        EQUALS((int)PNTR_FMODF(9.0f, 3.0f), 0);
    });
})

MODULE(pntr, {
    IT("pntr_load_memory(), pntr_unload_memory()", {
        void* memory = pntr_load_memory(100);
        NEQUALS(memory, NULL);
        pntr_unload_memory(memory);
    });

    IT("pntr_set_error(), pntr_get_error(), pntr_get_error_code()", {
        pntr_set_error(PNTR_ERROR_NONE);
        EQUALS(pntr_get_error(), NULL);
        pntr_image* image = pntr_new_image(-500, -500);
        EQUALS(image, NULL);
        NEQUALS(pntr_get_error(), NULL);
        STREQUALS(pntr_get_error(), "Invalid arguments");
        EQUALS(pntr_get_error_code(), PNTR_ERROR_INVALID_ARGS);
        pntr_unload_image(image);
        pntr_set_error(PNTR_ERROR_NONE);
        EQUALS(pntr_get_error_code(), PNTR_ERROR_NONE);
    });

    IT("pntr_color_rgba()", {
        pntr_color color = PNTR_RED;
        EQUALS(pntr_color_r(color), 230);
        EQUALS(pntr_color_g(color), 41);
        EQUALS(pntr_color_b(color), 55);
        EQUALS(pntr_color_a(color), 255);
        EQUALS(color.rgba.r, 230);
        EQUALS(color.rgba.g, 41);
        EQUALS(color.rgba.b, 55);
        EQUALS(color.rgba.a, 255);
    });

    IT("pntr_color_set_*()", {
        pntr_color blank = PNTR_BLANK;
        pntr_color_set_r(&blank, 10);
        pntr_color_set_g(&blank, 20);
        pntr_color_set_b(&blank, 30);
        pntr_color_set_a(&blank, 40);
        EQUALS(blank.rgba.r, 10);
        EQUALS(blank.rgba.g, 20);
        EQUALS(blank.rgba.b, 30);
        EQUALS(blank.rgba.a, 40);
    });

    IT("pntr_get_color()", {
        pntr_color color = pntr_get_color(0x052c46ff);
        EQUALS(color.rgba.r, 5);
        EQUALS(color.rgba.g, 44);
        EQUALS(color.rgba.b, 70);
        EQUALS(color.rgba.a, 255);
    });

    IT("pntr_new_color()", {
        pntr_color color = pntr_new_color(100, 120, 130, 200);
        EQUALS(color.rgba.r, 100);
        EQUALS(color.rgba.g, 120);
        EQUALS(color.rgba.b, 130);
        EQUALS(color.rgba.a, 200);
    });

    IT("pntr_gen_image_color(), pntr_image_get_color()", {
        pntr_image* image = pntr_gen_image_color(640, 480, PNTR_SKYBLUE);
        NEQUALS(image, NULL);
        EQUALS(image->width, 640);
        EQUALS(image->height, 480);

        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_SKYBLUE);

        pntr_draw_point(image, 10, 10, PNTR_PURPLE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_PURPLE);

        pntr_unload_image(image);
    });

    IT("pntr_clear_background(), pntr_draw_rectangle_fill()", {
        pntr_image* image = pntr_new_image(100, 100);
        NEQUALS(image, NULL);
        pntr_clear_background(image, PNTR_RED);

        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);

        pntr_clear_background(image, PNTR_BLANK);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_BLANK);

        pntr_draw_rectangle_fill(image, 9, 9, 3, 3, PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_BLUE);
        pntr_unload_image(image);
    });

    IT("pntr_draw_point()", {
        pntr_image* image = pntr_gen_image_color(50, 50, PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 10, 9), PNTR_WHITE);
        pntr_draw_point(image, 10, 10, PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 9), PNTR_WHITE);
        pntr_unload_image(image);
    });

    IT("pntr_draw_points()", {
        pntr_image* image = pntr_gen_image_color(50, 50, PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 15, 30), PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 40, 40), PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 0, 5), PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 0, 4), PNTR_WHITE);
        pntr_vector points[10];
        points[0] = PNTR_CLITERAL(pntr_vector) {10, 10};
        points[1] = PNTR_CLITERAL(pntr_vector) {15, 30};
        points[2] = PNTR_CLITERAL(pntr_vector) {40, 40};
        points[3] = PNTR_CLITERAL(pntr_vector) {0, 5};
        pntr_draw_points(image, points, 4, PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 15, 30), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 40, 40), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 0, 5), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 0, 4), PNTR_WHITE);
        pntr_unload_image(image);
    });

    IT("pntr_get_file_image_type()", {
        EQUALS(pntr_get_file_image_type("myimage.png"), PNTR_IMAGE_TYPE_PNG);
        EQUALS(pntr_get_file_image_type("my/path/ima.ge.png"), PNTR_IMAGE_TYPE_PNG);
        EQUALS(pntr_get_file_image_type("myimage.jpg"), PNTR_IMAGE_TYPE_JPG);
        EQUALS(pntr_get_file_image_type("myimage.jpeg"), PNTR_IMAGE_TYPE_JPG);
        EQUALS(pntr_get_file_image_type("myimage.bmp"), PNTR_IMAGE_TYPE_BMP);
        EQUALS(pntr_get_file_image_type("myimage.exe"), PNTR_IMAGE_TYPE_UNKNOWN);
        EQUALS(pntr_get_file_image_type(NULL), PNTR_IMAGE_TYPE_UNKNOWN);
        EQUALS(pntr_get_file_image_type(""), PNTR_IMAGE_TYPE_UNKNOWN);
    });

    IT("pntr_load_image()", {
        pntr_image* image = pntr_load_image("NotFoundImage.png");
        EQUALS(image, NULL);
        pntr_set_error(PNTR_ERROR_NONE);

        image = pntr_load_image("resources/image.png");
        NEQUALS(image, NULL);
        EQUALS(image->width, 128);
        EQUALS(image->height, 128);
        NEQUALS(image->data, NULL);
        pntr_unload_image(image);
    });

    IT("pntr_load_image_from_memory()", {
        unsigned int bytes;
        unsigned char* fileData = pntr_load_file("resources/image.png", &bytes);

        pntr_image* image = pntr_load_image_from_memory(PNTR_IMAGE_TYPE_PNG, fileData, bytes);
        NEQUALS(image, NULL);
        EQUALS(image->width, 128);
        EQUALS(image->height, 128);

        pntr_unload_image(image);
        pntr_unload_file(fileData);
    });

    IT("pntr_load_font_bmf(), pntr_unload_font(), pntr_draw_text()", {
        pntr_font* font = pntr_load_font_bmf("resources/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/");
        NEQUALS(font, NULL);
        GREATER(font->charactersLen, 10);

        pntr_image* image = pntr_gen_image_color(200, 200, PNTR_DARKBROWN);
        NEQUALS(image, NULL);
        pntr_draw_text(image, font, "Hello World!", 10, 10, PNTR_WHITE);
        pntr_draw_text_wrapped(image, font, "The quick brown fox jumped over the lazy dog.", 10, 10, 100, PNTR_BLUE);

        pntr_unload_image(image);
        pntr_unload_font(font);
    });

    IT("pntr_measure_text(), pntr_measure_text_ex(), pntr_gen_image_text()", {
        pntr_font* font = pntr_load_font_bmf("resources/font.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/");
        GREATER(pntr_measure_text(font, "Hello World!"), 50);
        pntr_vector size = pntr_measure_text_ex(font, "Hello World!", 0);
        GREATER(size.x, 50);
        EQUALS(size.y, font->atlas->height);

        pntr_image* textImage = pntr_gen_image_text(font, "Hello World!", PNTR_WHITE, PNTR_BLANK);
        NEQUALS(textImage, NULL);
        EQUALS(textImage->width, size.x);
        EQUALS(textImage->height, size.y);
        pntr_unload_image(textImage);

        size = pntr_measure_text_ex(font, "On\nNew\nLines", 0);
        EQUALS(size.y, font->atlas->height * 3);

        pntr_unload_font(font);
    });

    IT("pntr_load_font_tty()", {
        pntr_font* font = pntr_load_font_tty("resources/font-tty-8x8.png", 8, 8, "\x7f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
        NEQUALS(font, NULL);
        GREATER(font->charactersLen, 20);
        pntr_unload_font(font);
    });

    IT("pntr_load_font_default()", {
        pntr_font* font = pntr_load_font_default();
        NEQUALS(font, NULL);
        NEQUALS(font->atlas, NULL);
        GREATER(font->charactersLen, 10);
        pntr_unload_font(font);
    });

    IT("pntr_image_resize()", {
        pntr_image* image = pntr_new_image(300, 100);
        NEQUALS(image, NULL);

        IT("pntr_image_resize(PNTR_FILTER_NEARESTNEIGHBOR)", {
            pntr_image* resized = pntr_image_resize(image, 100, 100, PNTR_FILTER_NEARESTNEIGHBOR);
            NEQUALS(resized, NULL);
            EQUALS(resized->width, 100);
            EQUALS(resized->height, 100);
            pntr_unload_image(resized);
        });

        IT("pntr_image_resize(PNTR_FILTER_BILINEAR)", {
            pntr_image* resized = pntr_image_resize(image, 400, 300, PNTR_FILTER_BILINEAR);
            NEQUALS(resized, NULL);
            EQUALS(resized->width, 400);
            EQUALS(resized->height, 300);
            pntr_unload_image(resized);
        });

        pntr_unload_image(image);
    });

    IT("pntr_image_scale()", {
        pntr_image* image = pntr_new_image(100, 200);
        NEQUALS(image, NULL);

        pntr_image* scaled = pntr_image_scale(image, 1.5f, 2.5f, PNTR_FILTER_BILINEAR);
        NEQUALS(scaled, NULL);
        EQUALS(scaled->width, 150);
        EQUALS(scaled->height, 500);
        pntr_unload_image(scaled);

        scaled = pntr_image_scale(image, -2.0f, -3.0f, PNTR_FILTER_NEARESTNEIGHBOR);
        EQUALS(scaled, NULL);
        EQUALS(pntr_get_error_code(), PNTR_ERROR_INVALID_ARGS);

        pntr_unload_image(image);
    });

    IT("pntr_image_copy()", {
        pntr_image* image = pntr_gen_image_color(10, 10, PNTR_RED);
        pntr_draw_point(image, 5, 5, PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 5, 5), PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 2, 2), PNTR_RED);

        pntr_image* copy = pntr_image_copy(image);
        NEQUALS(image, copy);
        IMAGEEQUALS(image, copy);
        COLOREQUALS(pntr_image_get_color(copy, 5, 5), PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(copy, 2, 2), PNTR_RED);

        pntr_unload_image(copy);
        pntr_unload_image(image);
    });

    IT("pntr_image_color_replace()", {
        pntr_image* image = pntr_gen_image_color(100, 100, PNTR_BLUE);
        NEQUALS(image, NULL);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_BLUE);

        pntr_image_color_replace(image, PNTR_BLUE, PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);

        pntr_unload_image(image);
    });

    IT("pntr_color_invert()", {
        pntr_color color = pntr_new_color(21, 16, 171, 255);
        COLOREQUALS(pntr_color_invert(color), pntr_new_color(234, 239, 84, 255));
        color = pntr_new_color(64, 148, 81, 255);
        COLOREQUALS(pntr_color_invert(color), pntr_new_color(191, 107, 174, 255));
    });

    IT("pntr_image_color_invert()", {
        pntr_color color = pntr_new_color(21, 16, 171, 255);
        pntr_color invert = pntr_new_color(234, 239, 84, 255);
        pntr_image* image = pntr_gen_image_color(100, 100, color);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), color);
        pntr_image_color_invert(image);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), invert);
        pntr_unload_image(image);
    });

    IT("pntr_color_tint()", {
        pntr_color color = PNTR_WHITE;
        pntr_color tinted = pntr_color_tint(color, PNTR_RED);
        COLOREQUALS(tinted, PNTR_RED);
    });

    IT("pntr_image_color_tint()", {
        pntr_image* image = pntr_gen_image_color(100, 100, PNTR_WHITE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_WHITE);
        pntr_image_color_tint(image, PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);
        pntr_unload_image(image);
    });

    IT("pntr_color_fade()", {
        pntr_color color = PNTR_RED;
        EQUALS(color.rgba.a, 255);
        EQUALS(color.rgba.r, 230);

        pntr_color faded = pntr_color_fade(color, -0.5f);
        EQUALS(faded.rgba.a, 127);
        EQUALS(faded.rgba.r, 230);

        faded = pntr_color_fade(faded, 0.5f);
        EQUALS(faded.rgba.a, 191);
        EQUALS(faded.rgba.r, 230);
    });

    IT("pntr_image_color_fade()", {
        pntr_color red = PNTR_RED;
        pntr_image* image = pntr_gen_image_color(50, 50, red);
        NEQUALS(image, NULL);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), red);
        pntr_image_color_fade(image, -0.5f);
        red.rgba.a = 127;
        COLOREQUALS(pntr_image_get_color(image, 10, 10), red);
        pntr_unload_image(image);
    });

    IT("pntr_load_file(), pntr_unload_file()", {
        unsigned int bytesRead;
        unsigned char* fileData = pntr_load_file("resources/text.txt", &bytesRead);

        GREATER(bytesRead, 5);
        STRCEQUALS((const char*)fileData, "Hello", 5);
        pntr_unload_file(fileData);

        // Try to load a file that doesn't exist.
        unsigned char* fileNotFound = pntr_load_file("FileNotFound.txt", NULL);
        EQUALS(fileNotFound, NULL);

        // Expect an error to result.
        const char* error = pntr_get_error();
        NEQUALS(error, NULL);
        pntr_set_error(PNTR_ERROR_NONE);
    });

    IT("pntr_load_file_text()", {
        const char* text = pntr_load_file_text("resources/text.txt");
        STRCEQUALS(text, "Hello, World!", 13);
        pntr_unload_file_text(text);
    });

    IT("pntr_load_font_ttf()", {
        pntr_font* font = pntr_load_font_ttf("resources/tuffy.ttf", 20);
        NEQUALS(font, NULL);
        GREATER(font->charactersLen, 20);

        pntr_image* canvas = pntr_gen_image_text(font, "Hello World!", PNTR_RED, PNTR_BLANK);
        NEQUALS(canvas, NULL);
        GREATER(canvas->width, 10);
        GREATER(canvas->height, 10);

        IT("pntr_measure_text_ex()", {
            pntr_vector size = pntr_measure_text_ex(font, "Hello!!", 0);
            GREATER(size.x, 20);
            GREATER(size.y, 5);
        });

        pntr_unload_image(canvas);
        pntr_unload_font(font);
    });

    IT("pntr_save_file()", {
        const char* fileName = "tempFile.txt";
        const char* fileData = "Hello World!";
        unsigned int bytes = 12;
        bool result = pntr_save_file(fileName, (unsigned char*)fileData, bytes);
        EQUALS(result, true);

        unsigned char* fileDataResult = pntr_load_file(fileName, &bytes);
        GREATER(bytes, 5);
        STRCEQUALS((const char*)fileDataResult, "Hello", 5);
        pntr_unload_file(fileDataResult);
    });

    IT("pntr_save_image()", {
        int width = 400;
        int height = 300;
        pntr_image* saveImage = pntr_gen_image_color(width, height, PNTR_RED);
        NEQUALS(saveImage, NULL);
        pntr_draw_circle_fill(saveImage, 200, 150, 80, PNTR_BLUE);
        pntr_draw_rectangle_fill(saveImage, 10, 10, 20, 20, PNTR_GREEN);
        bool result = pntr_save_image(saveImage, "saveImage.png");
        EQUALS(result, true);
        pntr_unload_image(saveImage);

        pntr_image* loadedImage = pntr_load_image("saveImage.png");
        NEQUALS(loadedImage, NULL);
        EQUALS(loadedImage->width, 400);
        EQUALS(loadedImage->height, height);
        COLOREQUALS(pntr_image_get_color(loadedImage, 15, 15), PNTR_GREEN);
        pntr_unload_image(loadedImage);
    });

    IT("pntr_get_pixel_data_size()", {
        EQUALS(pntr_get_pixel_data_size(1, 1, PNTR_PIXELFORMAT_RGBA8888), 4);
        EQUALS(pntr_get_pixel_data_size(2, 3, PNTR_PIXELFORMAT_RGBA8888), 24);
        EQUALS(pntr_get_pixel_data_size(3, 2, PNTR_PIXELFORMAT_ARGB8888), 24);
        EQUALS(pntr_get_pixel_data_size(4, 4, PNTR_PIXELFORMAT_GRAYSCALE), 16);
    });

    IT("pntr_image_alpha_border(), pntr_image_alpha_crop()", {
        pntr_image* image = pntr_gen_image_color(400, 400, PNTR_BLANK);
        NEQUALS(image, NULL);
        EQUALS(image->width, 400);
        EQUALS(image->height, 400);

        pntr_draw_rectangle_fill(image, 100, 100, 200, 200, PNTR_BLUE);

        pntr_rectangle crop = pntr_image_alpha_border(image, 0);
        EQUALS(crop.x, 100);
        EQUALS(crop.y, 100);
        EQUALS(crop.width, 200);
        EQUALS(crop.height, 200);

        pntr_image_alpha_crop(image, 0);
        NEQUALS(image, NULL);
        EQUALS(image->width, 200);
        EQUALS(image->height, 200);

        COLOREQUALS(pntr_image_get_color(image, 50, 50), PNTR_BLUE);

        pntr_unload_image(image);
    });

    IT("pntr_image_crop()", {
        pntr_image* image = pntr_gen_image_color(200, 200, PNTR_RED);
        NEQUALS(image, NULL);
        pntr_image_crop(image, 10, 30, 20, 50);
        NEQUALS(image, NULL);
        EQUALS(image->width, 20);
        EQUALS(image->height, 50);
        COLOREQUALS(pntr_image_get_color(image, 10, 20), PNTR_RED);
        pntr_unload_image(image);
    });

    IT("pntr_image_flip()", {
        pntr_image* image = pntr_gen_image_color(100, 100, PNTR_RED);
        NEQUALS(image, NULL);
        pntr_draw_rectangle_fill(image, 0, 0, 20, 20, PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 90, 10), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 90), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 90, 90), PNTR_RED);
        pntr_image_flip(image, true, true);
        COLOREQUALS(pntr_image_get_color(image, 10, 10), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 90, 10), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 10, 90), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 90, 90), PNTR_BLUE);
        pntr_unload_image(image);
    });

    IT("pntr_image_resize_canvas()", {
        pntr_image* image = pntr_gen_image_color(200, 200, PNTR_BLUE);
        NEQUALS(image, NULL);
        EQUALS(image->width, 200);
        EQUALS(image->height, 200);
        pntr_image_resize_canvas(image, 400, 400, 100, 100, PNTR_RED);
        NEQUALS(image, NULL);
        EQUALS(image->width, 400);
        EQUALS(image->height, 400);
        COLOREQUALS(pntr_image_get_color(image, 50, 50), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 150, 150), PNTR_BLUE);
        pntr_unload_image(image);
    });

    IT("pntr_image_rotate()", {
        pntr_image* image = pntr_gen_image_color(40, 30, PNTR_BLUE);
        NEQUALS(image, NULL);
        pntr_draw_rectangle_fill(image, 9, 9, 3, 3, PNTR_RED);

        IT("pntr_image_rotate(image, 0.0f)", {
            pntr_image* rotated = pntr_image_rotate(image, 0.0f, PNTR_FILTER_NEARESTNEIGHBOR);
            NEQUALS(rotated, NULL);
            EQUALS(rotated->width, 40);
            EQUALS(rotated->height, 30);
            pntr_unload_image(rotated);
        });

        IT("pntr_image_rotate(image, 90.0f)", {
            pntr_image* rotated = pntr_image_rotate(image, 90.0f, PNTR_FILTER_BILINEAR);
            NEQUALS(rotated, NULL);
            EQUALS(rotated->width, image->height);
            EQUALS(rotated->height, image->width);
            COLOREQUALS(pntr_image_get_color(rotated, 10, 10), PNTR_BLUE);
            COLOREQUALS(pntr_image_get_color(rotated, 10, 30), PNTR_RED);
            pntr_unload_image(rotated);
        });

        IT("pntr_image_rotate(image, 180.0f)", {
            pntr_image* rotated = pntr_image_rotate(image, 180.0f, PNTR_FILTER_BILINEAR);
            NEQUALS(rotated, NULL);
            EQUALS(rotated->width, image->width);
            EQUALS(rotated->height, image->height);
            COLOREQUALS(pntr_image_get_color(rotated, 10, 10), PNTR_BLUE);
            COLOREQUALS(pntr_image_get_color(rotated, 30, 20), PNTR_RED);
            pntr_unload_image(rotated);
        });

        IT("pntr_image_rotate(image, 270.0f)", {
            pntr_image* rotated = pntr_image_rotate(image, 270.0f, PNTR_FILTER_NEARESTNEIGHBOR);
            NEQUALS(rotated, NULL);
            EQUALS(rotated->width, image->height);
            EQUALS(rotated->height, image->width);
            COLOREQUALS(pntr_image_get_color(rotated, 10, 10), PNTR_BLUE);
            COLOREQUALS(pntr_image_get_color(rotated, 20, 10), PNTR_RED);
            pntr_unload_image(rotated);
        });

        IT("pntr_image_rotate(image, 48.0f)", {
            pntr_image* rotated = pntr_image_rotate(image, 48.0f, PNTR_FILTER_BILINEAR);
            NEQUALS(rotated, NULL);
            NEQUALS(rotated->width, image->height);
            NEQUALS(rotated->height, image->width);
            COLOREQUALS(pntr_image_get_color(rotated, 5, 5), PNTR_BLANK);
            COLOREQUALS(pntr_image_get_color(rotated, rotated->width / 2, rotated->height / 2), PNTR_BLUE);
            pntr_unload_image(rotated);
        });

        IT("pntr_gen_image_gradient", {
            pntr_image* image = pntr_gen_image_gradient(500, 500, PNTR_RED, PNTR_GREEN, PNTR_BLUE, PNTR_GOLD);
            NEQUALS(image, NULL);

            pntr_color red = pntr_image_get_color(image, 0, 0);
            COLOREQUALS(red, PNTR_RED);
            pntr_color green = pntr_image_get_color(image, image->width - 1, 0);
            GREATER(green.rgba.g, 220);
            pntr_color blue = pntr_image_get_color(image, 0, image->height - 1);
            GREATER(blue.rgba.b, 230);
            pntr_color gold = pntr_image_get_color(image, image->width - 1, image->height - 1);
            GREATER(gold.rgba.r, 230);
            GREATER(gold.rgba.g, 180);
            pntr_unload_image(image);
        });

        pntr_unload_image(image);
    });

    IT("pntr_font_copy()", {
        pntr_font* font = pntr_load_font_default();
        NEQUALS(font, NULL);

        pntr_font* copy = pntr_font_copy(font);
        NEQUALS(copy, NULL);

        EQUALS(font->charactersLen, copy->charactersLen);
        EQUALS(font->atlas->width, copy->atlas->width);
        EQUALS(font->atlas->height, copy->atlas->height);
        NEQUALS(font->atlas, copy->atlas);

        pntr_unload_font(copy);
        pntr_unload_font(font);
    });

    IT("pntr_font_scale()", {
        pntr_font* font = pntr_load_font_default();
        NEQUALS(font, NULL);

        int scaleX = 5;
        int scaleY = 2;
        pntr_font* resized = pntr_font_scale(font, (float)scaleX, (float)scaleY, PNTR_FILTER_BILINEAR);
        NEQUALS(resized, NULL);

        EQUALS(font->charactersLen, resized->charactersLen);
        EQUALS(font->atlas->width * scaleX, resized->atlas->width);
        EQUALS(font->atlas->height * scaleY, resized->atlas->height);
        EQUALS(resized->glyphRects[0].width, font->glyphRects[0].width * scaleX);
        NEQUALS(font->atlas, resized->atlas);

        pntr_unload_font(font);
        pntr_unload_font(resized);
    });

    IT("pntr_image_subimage", {
        pntr_image* image = pntr_gen_image_color(300, 300, PNTR_RED);
        pntr_draw_rectangle_fill(image, 100, 100, 100, 100, PNTR_BLUE);

        COLOREQUALS(pntr_image_get_color(image, 50, 50), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 150, 150), PNTR_BLUE);

        pntr_image* subimage = pntr_image_subimage(image, 100, 100, 100, 100);
        COLOREQUALS(pntr_image_get_color(subimage, 50, 50), PNTR_BLUE);

        pntr_unload_image(subimage);
        pntr_unload_image(image);
    });

    IT("pntr_image_set_clip", {
        pntr_image* image = pntr_gen_image_color(300, 300, PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 50, 50), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 125, 125), PNTR_RED);

        pntr_image_set_clip(image, 100, 100, 50, 50);
        pntr_draw_rectangle_fill(image, 0, 0, image->width, image->height, PNTR_BLUE);
        COLOREQUALS(pntr_image_get_color(image, 50, 50), PNTR_RED);
        COLOREQUALS(pntr_image_get_color(image, 125, 125), PNTR_BLUE);

        pntr_unload_image(image);
    });

    IT("pntr_image_get_clip", {
        pntr_image* image = pntr_gen_image_color(300, 100, PNTR_RED);

        pntr_rectangle expected;
        expected.width = 300;
        expected.height = 100;
        expected.x = 0;
        expected.y = 0;
        RECTEQUALS(expected, pntr_image_get_clip(image));

        expected.width = 0;
        expected.height = 0;
        expected.x = 0;
        expected.y = 0;
        RECTEQUALS(expected, pntr_image_get_clip(NULL));

        pntr_unload_image(image);
    });

    IT("pntr_image_reset_clip", {
        pntr_image* image = pntr_gen_image_color(300, 300, PNTR_RED);

        EQUALS(image->clip.x, 0);
        EQUALS(image->clip.y, 0);
        EQUALS(image->clip.width, image->width);
        EQUALS(image->clip.height, image->height);

        pntr_image_set_clip(image, 100, 200, 50, 60);

        EQUALS(image->clip.x, 100);
        EQUALS(image->clip.y, 200);
        EQUALS(image->clip.width, 50);
        EQUALS(image->clip.height, 60);

        pntr_image_reset_clip(image);

        EQUALS(image->clip.x, 0);
        EQUALS(image->clip.y, 0);
        EQUALS(image->clip.width, image->width);
        EQUALS(image->clip.height, image->height);

        pntr_unload_image(image);
    });

    IT("_pntr_rectangle_intersect", {
        pntr_rectangle out;
        EQUALS(_pntr_rectangle_intersect(-10, -10, 5, 5, 0, 0, 100, 100, &out), false);
        EQUALS(_pntr_rectangle_intersect(5, 6, 10, 5, 0, 0, 100, 100, &out), true);
        EQUALS(out.x, 5);
        EQUALS(out.y, 6);
        EQUALS(out.width, 10);
        EQUALS(out.height, 5);
        EQUALS(_pntr_rectangle_intersect(-5, -5, 10, 10, 0, 0, 20, 20, &out), true);
        EQUALS(out.x, 0);
        EQUALS(out.y, 0);
        EQUALS(out.width, 5);
        EQUALS(out.height, 5);

        EQUALS(_pntr_rectangle_intersect(10, 10, 50, 50, 20, 20, 10, 10, &out), true);
        pntr_rectangle expected = (pntr_rectangle) {20, 20, 10, 10};
        RECTEQUALS(out, expected);
    });

    if (pntr_utf8()) {
        IT("PNTR_ENABLE_UTF8", {
            pntr_font* font = pntr_load_font_ttf("resources/tuffy.ttf", 38);
            NEQUALS(font, NULL);

            // Generate the image displaying UTF-8 text.
            const char* text = "Добрий день!";
            pntr_image* image = pntr_gen_image_text(font, text, PNTR_BLACK, PNTR_WHITE);
            NEQUALS(image, NULL);
            pntr_save_image(image, "pntr_test_utf8.png");

            EQUALS(image->width, 190);
            EQUALS(image->height, 37);

            pntr_unload_font(font);
            pntr_unload_image(image);
        });
    }
    else {
        IT("PNTR_ENABLE_UTF8: Not enabled", {
            // Nothing
        });
    }

    IT("No reported errors", {
        const char* err = "";
        if (pntr_get_error() != NULL) {
            err = pntr_get_error();
        }

        STREQUALS(err, "");
    });
})

int main() {
    UNIT_CREATE("pntr");
    UNIT_MODULE(pntr);
    UNIT_MODULE(pntr_math);
    return UNIT_RUN();
}
