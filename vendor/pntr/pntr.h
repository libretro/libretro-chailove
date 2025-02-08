/**
 * pntr: Image manipulation library for C99 and C++, with a focus on ease-of-use.
 *
 *   https://github.com/robloach/pntr
 *
 * Configuration:
 * - PNTR_IMPLEMENTATION: Define this in one of your .c files, before including pntr.h
 * - PNTR_PIXELFORMAT_RGBA: Use the RGBA format
 * - PNTR_PIXELFORMAT_ARGB: Use the ARGB pixel format
 * - PNTR_NO_ALPHABLEND: Skips alpha blending when rendering images
 * - PNTR_ENABLE_DEFAULT_FONT: Enables the default font
 * - PNTR_ENABLE_JPEG: When available, support JPEG image loading
 * - PNTR_ENABLE_MATH: When enabled, will use C's math.h library, rather than internal implementations
 * - PNTR_ENABLE_TTF: Enables support for loading TrueType fonts
 * - PNTR_ENABLE_UTF8: Enables support for UTF-8 text rendering
 * - PNTR_ENABLE_VARGS: Adds support for functions that require variadic arguments.
 * - PNTR_LOAD_FILE: Callback used to load a file in pntr_load_file(). By default, will use stdio.h.
 * - PNTR_LOAD_IMAGE_FROM_MEMORY: Callback to load an image from memory in pntr_load_image_from_memory(). By default, will use cute_png.
 * - PNTR_SAVE_FILE: Callback used to save a file in pntr_save_file(). By default, will use stdio.h.
 * - PNTR_SAVE_IMAGE_TO_MEMORY: Callback to save an image to memory in pntr_save_image_to_memory(). By default, will use cute_png.
 * - PNTR_NO_STDIO: When enabled, will disable the standard file loading/saving calls for PNTR_LOAD_FILE and PNTR_SAVE_FILE.
 * - PNTR_NO_SAVE_IMAGE: Disables the default behaviour of saving images.
 * - PNTR_NO_LOAD_IMAGE: Disables the default behavior of loading images.
 * - PNTR_NO_CUTE_PNG_IMPLEMENTATION: Skips defining CUTE_PNG_IMPLEMENTATION. Useful if you're using cute_png elsewhere.
 * - PNTR_NO_STB_IMAGE_IMPLEMENTATION: Skips defining STB_IMAGE_IMPLEMENTATION. Useful if you're using stb_image elsewhere.
 * - PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION: Skips defining STB_IMAGE_WRITE_IMPLEMENTATION. Useful if you're using stb_image_write elsewhere.
 * - PNTR_NO_STB_TRUETYPE_IMPLEMENTATION: Skips defining STB_TRUETYPE_IMPLEMENTATION. Useful if you're using stb_truetype elsewhere.
 *
 * @file pntr.h
 *
 * @copyright 2023 Rob Loach (@RobLoach, https://robloach.net)
 *
 * @license Zlib
 *
 * Copyright (c) 2023 Rob Loach (@RobLoach, https://robloach.net)
 *
 * This software is provided "as-is", without any express or implied warranty. In no event
 * will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 * applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not claim that you
 *   wrote the original software. If you use this software in a product, an acknowledgment
 *   in the product documentation would be appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *   as being the original software.
 *
 *   3. This notice may not be removed or altered from any source distribution.
 */
#ifndef PNTR_H__
#define PNTR_H__

#include <stdint.h> // uint32_t
#include <stdbool.h> // bool
#include <stddef.h> // size_t

/**
 * @defgroup pntr pntr
 * @{
 *
 * @brief Image manipulation library for C99 or C++, with a focus on ease-of-use.
 *
 * Make sure to define `PNTR_IMPLEMENTATION` before including in one of your `.c` files.
 *
 * @code
 * #define PNTR_IMPLEMENTATION
 * #include "pntr.h"
 *
 * int main() {
 *     pntr_image* image = pntr_new_image(200, 200);
 *     pntr_draw_circle_fill(image, 100, 100, 80, PNTR_RED);
 *     pntr_save_image(image, "output.png");
 *     pntr_unload_image(image);
 *
 *     return 0;
 * }
 * @endcode
 *
 * @see PNTR_IMPLEMENTATION
 */

#ifdef _DOXYGEN_
    /**
     * @defgroup config Configuration
     * @{
     */

    /**
     * Define `PNTR_IMPLEMENTATION` in **one** of your `.c` files before including `pntr.h`.
     *
     * This will let pntr.h know where to implement its functions.
     *
     * @code
     * #define PNTR_IMPLEMENTATION
     * #include "pntr.h"
     *
     * int main() {
     *     return 0;
     * }
     * @endcode
     */
    #define PNTR_IMPLEMENTATION

    /**
     * When defined, will use the RGBA format.
     *
     * @see PNTR_PIXELFORMAT_RGBA8888
     */
    #define PNTR_PIXELFORMAT_RGBA

    /**
     * When defined, will use the ARGB pixel format.
     *
     * @see PNTR_PIXELFORMAT_ARGB8888
     */
    #define PNTR_PIXELFORMAT_ARGB

    /**
     * Enables support for pntr's default font. It's a small 8x8 font.
     *
     * @see pntr_load_font_default()
     */
    #define PNTR_ENABLE_DEFAULT_FONT

    /**
     * Enables support for loading TrueType fonts with `stb_truetype.h`.
     *
     * @see pntr_load_font_ttf()
     * @see https://github.com/nothings/stb/blob/master/stb_truetype.h
     */
    #define PNTR_ENABLE_TTF

    /**
     * Enable UTF-8 character set support for font loading, and text rendering, with `utf8.h`.
     *
     * @note When this is enabled, there is an increase in font memory usage.
     *
     * @see https://github.com/sheredom/utf8.h
     */
    #define PNTR_ENABLE_UTF8

    /**
     * Callback to use when saving an image to memory. By default, will use stb_image_write.
     *
     * @see pntr_save_image_to_memory()
     * @see PNTR_STB_IMAGE
     * @see PNTR_CUTE_PNG
     * @see pntr_stb_image_save_image_to_memory()
     * @see pntr_cute_png_save_image_to_memory()
     */
    #define PNTR_SAVE_IMAGE_TO_MEMORY

    /**
     * Callback to use when loading an image. By default, will use stb_image.
     *
     * @see pntr_stb_image_load_image_from_memory()
     * @see pntr_cute_png_load_image_from_memory()
     * @see pntr_load_image_from_memory()
     * @see PNTR_CUTE_PNG
     * @see PNTR_STB_IMAGE
     */
    #define PNTR_LOAD_IMAGE_FROM_MEMORY

    /**
     * When enabled, will use C's standard math.h library for math functions, rather than pntr's internally build in methods.
     */
    #define PNTR_ENABLE_MATH

    /**
     * Callback to use when loading a file. Must match the `pntr_load_file()` definition.
     *
     * @see pntr_load_file()
     * @see PNTR_NO_STDIO
     */
    #define PNTR_LOAD_FILE

    /**
     * Callback to use when saving a file. Must match the `pntr_save_file()` definition.
     *
     * @see pntr_save_file()
     * @see PNTR_NO_STDIO
     */
    #define PNTR_SAVE_FILE

    /**
     * When defined, will use `stb_image.h` for loading images, and `stb_image_write.h` for saving.
     *
     * @details By default, `stb_image` will be used if a custom implementation isn't defined.
     *
     * @see pntr_load_image()
     * @see pntr_save_image()
     * @see PNTR_CUTE_PNG
     * @see PNTR_SAVE_IMAGE_TO_MEMORY
     * @see PNTR_LOAD_IMAGE_FROM_MEMORY
     */
    #define PNTR_STB_IMAGE

    /**
     * When defined, will use `cute_png.h` for loading and saving.
     *
     * @details While cute_png takes up less memory than stb_image, it doesn't support as many of the features.
     *
     * @see pntr_load_image()
     * @see pntr_save_image()
     * @see PNTR_STB_IMAGE
     * @see PNTR_SAVE_IMAGE_TO_MEMORY
     * @see PNTR_LOAD_IMAGE_FROM_MEMORY
     */
    #define PNTR_CUTE_PNG

    /**
     * Skips alpha blending when rendering images. Defining this will improve performance.
     *
     * @see pntr_color_alpha_blend()
     */
    #define PNTR_NO_ALPHABLEND

    /**
     * Will disable the default use of `stdio.h` for file saving/loading with `PNTR_LOAD_FILE` and `PNTR_SAVE_FILE`.
     *
     * @see PNTR_LOAD_FILE
     * @see PNTR_SAVE_FILE
     */
    #define PNTR_NO_STDIO

    /**
     * Will disable image loading.
     *
     * @see PNTR_LOAD_IMAGE_FROM_MEMORY
     */
    #define PNTR_NO_LOAD_IMAGE

    /**
     * Will disable image saving.
     *
     * @see PNTR_SAVE_IMAGE_TO_MEMORY
     */
    #define PNTR_NO_SAVE_IMAGE

    /**
     * Skips defining `CUTE_PNG_IMPLEMENTATION`. Useful if you're using cute_png elsewhere.
     */
    #define PNTR_NO_CUTE_PNG_IMPLEMENTATION

    /**
     * Skips defining `STB_IMAGE_WRITE_IMPLEMENTATION`. Useful if you're using stb_image_write elsewhere.
     */
    #define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION

    /**
     * Skips defining `STB_IMAGE_IMPLEMENTATION`. Useful if you're using stb_image elsewhere.
     */
    #define PNTR_NO_STB_IMAGE_IMPLEMENTATION

    /**
     * Skips defining `STB_TRUETYPE_IMPLEMENTATION`. Useful if you're using stb_truetype elsewhere.
     */
    #define PNTR_NO_STB_TRUETYPE_IMPLEMENTATION

    /**
     * @}
     */
#endif

#ifndef PNTR_API
    /**
     * Prefix applied to all pntr methods.
     *
     * If you're using Emscripten, for instance, you could use the following to export all pntr methods:
     *
     *     #define PNTR_API EMSCRIPTEN_KEEPALIVE
     */
    #define PNTR_API
#endif

// Pixel Format. Default to PNTR_PIXELFORMAT_RGBA
#if !defined(PNTR_PIXELFORMAT_RGBA) && !defined(PNTR_PIXELFORMAT_ARGB)
    #define PNTR_PIXELFORMAT_RGBA
#endif
#if defined(PNTR_PIXELFORMAT_RGBA) && defined(PNTR_PIXELFORMAT_ARGB)
    #undef PNTR_PIXELFORMAT_ARGB
#endif

#ifdef PNTR_PIXELFORMAT
    #undef PNTR_PIXELFORMAT
#endif
#ifdef PNTR_PIXELFORMAT_RGBA
    /**
     * The set pixel format for the application.
     *
     * Will become either `PNTR_PIXELFORMAT_ARGB8888` or `PNTR_PIXELFORMAT_RGBA8888`, with the default being `PNTR_PIXELFORMAT_RGBA8888`.
     *
     * @see PNTR_PIXELFORMAT_RGBA8888
     * @see PNTR_PIXELFORMAT_ARGB8888
     */
    #define PNTR_PIXELFORMAT PNTR_PIXELFORMAT_RGBA8888
#elif defined(PNTR_PIXELFORMAT_ARGB)
    #define PNTR_PIXELFORMAT PNTR_PIXELFORMAT_ARGB8888
#endif

#ifndef PNTR_CLITERAL
    #if defined(__cplusplus)
        #define PNTR_CLITERAL(type)      type
    #else
        /**
         * Compound literal to initialize a structure.
         *
         * @param type The type of the structure to intiailize.
         * @return The initialized structure.
         * @note MSVC C++ compiler does not support compound literals (C99 feature)
         *
         * @code
         * pntr_color color = PNTR_CLITERAL(pntr_color) { 255, 255, 255, 255 };
         * @endif
         */
        #define PNTR_CLITERAL(type)      (type)
    #endif
#endif

/**
 * Color, represented by an unsigned 32-bit integer.
 *
 * Has four components: Red, Green, Blue, and Alpha. Depending on the pixel format, will
 * shift the order in which the components are defines.
 *
 * @see pntr_new_color()
 * @see pntr_get_color()
 * @see PNTR_PIXELFORMAT_RGBA
 * @see PNTR_PIXELFORMAT_ARGB
 */
typedef union pntr_color {
    /**
     * The color value, represented by an unsigned 32-bit integer.
     */
    uint32_t value;

    /**
     * Union data representing the 32-bit integer, split into four bytes.
     *
     * The order in which the values are sorted depends on which pixel format you're using.
     *
     * @see PNTR_PIXELFORMAT_RGBA
     * @see PNTR_PIXELFORMAT_ARGB
     */
    struct pntr_color_rgba_t {
        #if defined(PNTR_PIXELFORMAT_RGBA)
            unsigned char r; /** Red channel. */
            unsigned char g; /** Green channel. */
            unsigned char b; /** Blue channel. */
            unsigned char a; /** Alpha channel. */
        #elif defined(PNTR_PIXELFORMAT_ARGB)
            unsigned char b; /** Blue channel. */
            unsigned char g; /** Green channel. */
            unsigned char r; /** Red channel. */
            unsigned char a; /** Alpha channel. */
        #endif
    } rgba;
} pntr_color;

/**
 * A rectangle.
 */
typedef struct pntr_rectangle {
    int x; /** The x position of the rectangle. */
    int y; /** The y position of the rectangle. */
    int width; /** The width of the rectangle. */
    int height; /** The height of the rectangle. */
} pntr_rectangle;

/**
 * An image, represented by pixel data.
 *
 * @see pntr_new_image()
 * @see pntr_gen_image_color()
 */
typedef struct pntr_image {
    pntr_color* data; /** The pixel data for the image. */
    int width; /** The width of the image. */
    int height; /** The height of the image. */
    int pitch; /** The amount of bytes of one row of the image. */

    /**
     * Whether or not the image is a portion of another image, sharing the same image data.
     *
     * @see pntr_image_subimage()
     */
    bool subimage;

    /**
     * A rectangle representing the region of the image that can be changed.
     *
     * @see pntr_image_set_clip()
     * @see pntr_image_reset_clip()
     * @see pntr_image_get_clip()
     */
    pntr_rectangle clip;
} pntr_image;

/**
 * A vector, represented by x and y coordinates.
 */
typedef struct pntr_vector {
    int x; /** The X coordinate. */
    int y; /** The Y coordinate. */
} pntr_vector;

/**
 * Font used to render text.
 *
 * @see pntr_load_font_tty()
 * @see pntr_load_font_ttf()
 * @see pntr_load_font_bmf()
 * @see PNTR_ENABLE_UTF8
 * @see PNTR_ENABLE_TTF
 */
typedef struct pntr_font {
    pntr_image* atlas; /** The image used for the character atlas for the font. */
    pntr_rectangle* srcRects; /** The glyph source rectangles on the atlas. */
    pntr_rectangle* glyphRects; /** How the glyph appears when rendering. */
    char* characters; /** An array of characters that are available in the font's atlas. */
    int charactersLen; /** The number of characters that the font implements. */
    void* user_data; /** General extra user data that can be referenced to by the font. */
} pntr_font;

/**
 * Pixel format.
 */
typedef enum pntr_pixelformat {
    PNTR_PIXELFORMAT_RGBA8888 = 0, /** RGBA, with 8 bytes for each component. */
    PNTR_PIXELFORMAT_ARGB8888, /** ARGB, with 8 bytes for each component. */
    PNTR_PIXELFORMAT_GRAYSCALE /** Grayscale, with one byte for each pixel, 0 - 255. 0 being disabled, 255 being enabled. */
} pntr_pixelformat;

/**
 * Possible image filters to apply.
 */
typedef enum pntr_filter {
    PNTR_FILTER_NEARESTNEIGHBOR = 0, /** Nearest-neighbor interpolation for fast processing. Good for a pixel art look. */
    PNTR_FILTER_BILINEAR /** Bilinear interpolation will combine multiple pixels together when processing for smoother scaling. */
} pntr_filter;

/**
 * Error states definitions.
 *
 * @see pntr_set_error()
 * @see pntr_get_error()
 */
typedef enum pntr_error {
    PNTR_ERROR_NONE = 0, /** No error */
    PNTR_ERROR_INVALID_ARGS = -1, /** Invalid arguments */
    PNTR_ERROR_NO_MEMORY = -2, /** Not enough memory */
    PNTR_ERROR_NOT_SUPPORTED = -3, /** Not supported */
    PNTR_ERROR_FAILED_TO_OPEN = -4, /** Failed to open */
    PNTR_ERROR_FAILED_TO_WRITE = -5, /** Failed to write */
    PNTR_ERROR_UNKNOWN = -6 /** Unknown error occurred */
} pntr_error;

/**
 * The associated image format.
 */
typedef enum pntr_image_type {
    PNTR_IMAGE_TYPE_UNKNOWN = 0, /** Image type: Unknown. */
    PNTR_IMAGE_TYPE_PNG, /** Image type: PNG - Portable Network Graphics */
    PNTR_IMAGE_TYPE_JPG, /** Image type: JPEG - Joint Photographic Experts Group */
    PNTR_IMAGE_TYPE_BMP /** Image type: BMP - Bitmap */
} pntr_image_type;

#ifdef __cplusplus
extern "C" {
#endif

PNTR_API pntr_image* pntr_new_image(int width, int height);
PNTR_API pntr_image* pntr_gen_image_color(int width, int height, pntr_color color);
PNTR_API pntr_image* pntr_image_copy(pntr_image* image);
PNTR_API pntr_image* pntr_image_from_image(pntr_image* image, int x, int y, int width, int height);
PNTR_API pntr_image* pntr_image_subimage(pntr_image* image, int x, int y, int width, int height);
PNTR_API pntr_rectangle pntr_image_get_clip(pntr_image* image);
PNTR_API void pntr_image_set_clip(pntr_image* image, int x, int y, int width, int height);
PNTR_API void pntr_image_set_clip_rec(pntr_image* image, pntr_rectangle clip);
PNTR_API void pntr_image_reset_clip(pntr_image* image);
PNTR_API void pntr_unload_image(pntr_image* image);
PNTR_API void pntr_clear_background(pntr_image* image, pntr_color color);
PNTR_API void pntr_draw_point(pntr_image* dst, int x, int y, pntr_color color);
PNTR_API void pntr_draw_point_vec(pntr_image* dst, pntr_vector* point, pntr_color color);
PNTR_API void pntr_draw_points(pntr_image* dst, pntr_vector* points, int pointsCount, pntr_color color);
PNTR_API void pntr_draw_line(pntr_image* dst, int startPosX, int startPosY, int endPosX, int endPosY, pntr_color color);
PNTR_API void pntr_draw_line_curve(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_vector point4, int segments, pntr_color color);
PNTR_API void pntr_draw_line_vec(pntr_image* dst, pntr_vector start, pntr_vector end, pntr_color color);
PNTR_API void pntr_draw_line_vertical(pntr_image* dst, int posX, int posY, int height, pntr_color color);
PNTR_API void pntr_draw_line_horizontal(pntr_image* dst, int posX, int posY, int width, pntr_color color);
PNTR_API void pntr_draw_rectangle(pntr_image* dst, int posX, int posY, int width, int height, pntr_color color);
PNTR_API void pntr_draw_rectangle_rec(pntr_image* dst, pntr_rectangle rec, pntr_color color);
PNTR_API void pntr_draw_rectangle_fill(pntr_image* dst, int posX, int posY, int width, int height, pntr_color color);
PNTR_API void pntr_draw_rectangle_fill_rec(pntr_image* dst, pntr_rectangle rect, pntr_color color);
PNTR_API void pntr_draw_rectangle_gradient(pntr_image* dst, int x, int y, int width, int height, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight);
PNTR_API void pntr_draw_rectangle_gradient_rec(pntr_image* dst, pntr_rectangle rect, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight);
PNTR_API void pntr_draw_triangle(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, pntr_color color);
PNTR_API void pntr_draw_triangle_vec(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_color color);
PNTR_API void pntr_draw_triangle_fill(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, pntr_color color);
PNTR_API void pntr_draw_triangle_fill_vec(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_color color);
PNTR_API void pntr_draw_ellipse(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, pntr_color color);
PNTR_API void pntr_draw_ellipse_fill(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, pntr_color color);
PNTR_API void pntr_draw_circle(pntr_image* dst, int centerX, int centerY, int radius, pntr_color color);
PNTR_API void pntr_draw_circle_fill(pntr_image* dst, int centerX, int centerY, int radius, pntr_color color);
PNTR_API void pntr_draw_polygon(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color);
PNTR_API void pntr_draw_polygon_fill(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color);
PNTR_API void pntr_draw_polyline(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color);
PNTR_API void pntr_draw_arc(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, pntr_color color);
PNTR_API void pntr_draw_arc_fill(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, pntr_color color);
PNTR_API void pntr_draw_rectangle_rounded(pntr_image* dst, int x, int y, int width, int height, int topLeftRadius, int topRightRadius, int bottomLeftRadius, int bottomRightRadius, pntr_color color);
PNTR_API void pntr_draw_rectangle_rounded_fill(pntr_image* dst, int x, int y, int width, int height, int cornerRadius, pntr_color color);
PNTR_API void pntr_draw_image(pntr_image* dst, pntr_image* src, int posX, int posY);
PNTR_API void pntr_draw_image_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY);
PNTR_API void pntr_draw_image_tint(pntr_image* dst, pntr_image* src, int posX, int posY, pntr_color tint);
PNTR_API void pntr_draw_image_tint_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, pntr_color tint);
PNTR_API void pntr_draw_image_rotated(pntr_image* dst, pntr_image* src, int posX, int posY, float degrees, float offsetX, float offsetY, pntr_filter filter);
PNTR_API void pntr_draw_image_rotated_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, float degrees, float offsetX, float offsetY, pntr_filter filter);
PNTR_API void pntr_draw_image_flipped(pntr_image* dst, pntr_image* src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
PNTR_API void pntr_draw_image_flipped_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRec, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal);
PNTR_API void pntr_draw_image_scaled(pntr_image* dst, pntr_image* src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter);
PNTR_API void pntr_draw_image_scaled_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter);
PNTR_API void pntr_draw_text(pntr_image* dst, pntr_font* font, const char* text, int posX, int posY, pntr_color tint);
PNTR_API void pntr_draw_text_len(pntr_image* dst, pntr_font* font, const char* text, int textLength, int posX, int posY, pntr_color tint);
PNTR_API void pntr_draw_text_wrapped(pntr_image* dst, pntr_font* font, const char* text, int posX, int posY, int maxWidth, pntr_color tint);
#ifdef PNTR_ENABLE_VARGS
PNTR_API void pntr_draw_text_ex(pntr_image* dst, pntr_font* font, int posX, int posY, pntr_color tint, const char* text, ...);
#endif
PNTR_API pntr_color pntr_new_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
PNTR_API pntr_color pntr_get_color(unsigned int hexValue);
PNTR_API unsigned char pntr_color_r(pntr_color color);
PNTR_API unsigned char pntr_color_g(pntr_color color);
PNTR_API unsigned char pntr_color_b(pntr_color color);
PNTR_API unsigned char pntr_color_a(pntr_color color);
PNTR_API void pntr_color_set_r(pntr_color* color, unsigned char r);
PNTR_API void pntr_color_set_g(pntr_color* color, unsigned char g);
PNTR_API void pntr_color_set_b(pntr_color* color, unsigned char b);
PNTR_API void pntr_color_set_a(pntr_color* color, unsigned char a);
PNTR_API pntr_color pntr_image_get_color(pntr_image* image, int x, int y);
PNTR_API bool pntr_save_file(const char *fileName, const void *data, unsigned int bytesToWrite);
PNTR_API void* pntr_image_to_pixelformat(pntr_image* image, unsigned int* dataSize, pntr_pixelformat pixelFormat);
PNTR_API bool pntr_save_image(pntr_image* image, const char* fileName);
PNTR_API unsigned char* pntr_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize);
PNTR_API int pntr_get_pixel_data_size(int width, int height, pntr_pixelformat pixelFormat);
PNTR_API pntr_image* pntr_load_image(const char* fileName);
PNTR_API pntr_image* pntr_load_image_from_memory(pntr_image_type type, const unsigned char* fileData, unsigned int dataSize);
PNTR_API pntr_image* pntr_image_from_pixelformat(const void* data, int width, int height, pntr_pixelformat pixelFormat);
PNTR_API void* pntr_set_error(pntr_error error);
PNTR_API const char* pntr_get_error(void);
PNTR_API pntr_error pntr_get_error_code(void);
PNTR_API pntr_image* pntr_image_resize(pntr_image* image, int newWidth, int newHeight, pntr_filter filter);
PNTR_API pntr_image* pntr_image_scale(pntr_image* image, float scaleX, float scaleY, pntr_filter filter);
PNTR_API void pntr_image_color_replace(pntr_image* image, pntr_color color, pntr_color replace);
PNTR_API pntr_color pntr_color_tint(pntr_color color, pntr_color tint);
PNTR_API void pntr_image_color_tint(pntr_image* image, pntr_color color);
PNTR_API pntr_color pntr_color_fade(pntr_color color, float alpha);
PNTR_API void pntr_image_color_fade(pntr_image* image, float alpha);
PNTR_API pntr_color pntr_color_brightness(pntr_color color, float factor);
PNTR_API pntr_color pntr_get_pixel_color(void* srcPtr, pntr_pixelformat srcPixelFormat);
PNTR_API void pntr_set_pixel_color(void* dstPtr, pntr_pixelformat dstPixelFormat, pntr_color color);
PNTR_API pntr_font* pntr_load_font_default(void);
PNTR_API void pntr_unload_font(pntr_font* font);
PNTR_API pntr_font* pntr_font_copy(pntr_font* font);
PNTR_API pntr_font* pntr_font_scale(pntr_font* font, float scaleX, float scaleY, pntr_filter filter);
PNTR_API pntr_font* pntr_load_font_bmf(const char* fileName, const char* characters);
PNTR_API pntr_font* pntr_load_font_bmf_from_image(pntr_image* image, const char* characters);
PNTR_API pntr_font* pntr_load_font_bmf_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* characters);
PNTR_API int pntr_measure_text(pntr_font* font, const char* text);
PNTR_API pntr_vector pntr_measure_text_ex(pntr_font* font, const char* text, int textLength);
PNTR_API pntr_image* pntr_gen_image_text(pntr_font* font, const char* text, pntr_color tint, pntr_color backgroundColor);
PNTR_API pntr_font* pntr_load_font_tty(const char* fileName, int glyphWidth, int glyphHeight, const char* characters);
PNTR_API pntr_font* pntr_load_font_tty_from_memory(const unsigned char* fileData, unsigned int dataSize, int glyphWidth, int glyphHeight, const char* characters);
PNTR_API pntr_font* pntr_load_font_tty_from_image(pntr_image* image, int glyphWidth, int glyphHeight, const char* characters);
PNTR_API unsigned char* pntr_load_file(const char *fileName, unsigned int *bytesRead);
PNTR_API void pntr_unload_file(unsigned char* fileData);
PNTR_API const char* pntr_load_file_text(const char *fileName);
PNTR_API void pntr_unload_file_text(const char* text);
PNTR_API pntr_font* pntr_load_font_ttf(const char* fileName, int fontSize);
PNTR_API pntr_font* pntr_load_font_ttf_from_memory(const unsigned char* fileData, unsigned int dataSize, int fontSize);
PNTR_API pntr_color pntr_color_invert(pntr_color color);
PNTR_API void pntr_image_color_invert(pntr_image* image);
PNTR_API pntr_color pntr_color_alpha_blend(pntr_color dst, pntr_color src);
PNTR_API pntr_rectangle pntr_image_alpha_border(pntr_image* image, float threshold);
PNTR_API bool pntr_image_crop(pntr_image* image, int x, int y, int width, int height);
PNTR_API void pntr_image_alpha_crop(pntr_image* image, float threshold);
PNTR_API void pntr_image_color_brightness(pntr_image* image, float factor);
PNTR_API void pntr_image_flip(pntr_image* image, bool horizontal, bool vertical);
PNTR_API pntr_color pntr_color_contrast(pntr_color color, float contrast);
PNTR_API void pntr_image_color_contrast(pntr_image* image, float contrast);
PNTR_API void pntr_image_alpha_mask(pntr_image* image, pntr_image* alphaMask, int posX, int posY);
PNTR_API bool pntr_image_resize_canvas(pntr_image* image, int newWidth, int newHeight, int offsetX, int offsetY, pntr_color fill);
PNTR_API pntr_image* pntr_image_rotate(pntr_image* image, float degrees, pntr_filter filter);
PNTR_API pntr_image* pntr_gen_image_gradient(int width, int height, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight);
PNTR_API pntr_color pntr_color_bilinear_interpolate(pntr_color color00, pntr_color color01, pntr_color color10, pntr_color color11, float coordinateX, float coordinateY);
PNTR_API void* pntr_load_memory(size_t size);
PNTR_API void pntr_unload_memory(void* pointer);
PNTR_API void* pntr_memory_copy(void* destination, void* source, size_t size);
PNTR_API pntr_image_type pntr_get_file_image_type(const char* filePath);

PNTR_API void pntr_draw_line_thick(pntr_image* dst, int startPosX, int startPosY, int endPosX, int endPosY, int thickness, pntr_color color);
PNTR_API void pntr_draw_line_thick_vec(pntr_image* dst, pntr_vector start, pntr_vector end, int thickness, pntr_color color);
PNTR_API void pntr_draw_rectangle_thick(pntr_image* dst, int posX, int posY, int width, int height, int thickness, pntr_color color);
PNTR_API void pntr_draw_rectangle_thick_rec(pntr_image* dst, pntr_rectangle rect, int thickness, pntr_color color);
PNTR_API void pntr_draw_triangle_thick(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, pntr_color color);
PNTR_API void pntr_draw_triangle_thick_vec(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, int thickness, pntr_color color);
PNTR_API void pntr_draw_ellipse_thick(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, int thickness, pntr_color color);
PNTR_API void pntr_draw_circle_thick(pntr_image* dst, int centerX, int centerY, int radius, int thickness, pntr_color color);
PNTR_API void pntr_draw_polygon_thick(pntr_image* dst, pntr_vector* points, int numPoints, int thickness, pntr_color color);
PNTR_API void pntr_draw_polyline_thick(pntr_image* dst, pntr_vector* points, int numPoints, int thickness, pntr_color color);
PNTR_API void pntr_draw_arc_thick(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, int thickness, pntr_color color);
PNTR_API void pntr_draw_rectangle_thick_rounded(pntr_image* dst, int x, int y, int width, int height, int topLeftRadius, int topRightRadius, int bottomLeftRadius, int bottomRightRadius, int thickness, pntr_color color);
PNTR_API void pntr_draw_line_vertical_thick(pntr_image* dst, int posX, int posY, int height, int thickness, pntr_color color);
PNTR_API void pntr_draw_line_horizontal_thick(pntr_image* dst, int posX, int posY, int width, int thickness, pntr_color color);
PNTR_API void pntr_draw_line_curve_thick(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_vector point4, int segments, int thickness, pntr_color color);

// Internal
PNTR_API void pntr_put_horizontal_line_unsafe(pntr_image* dst, int posX, int posY, int width, pntr_color color);
PNTR_API void pntr_draw_point_unsafe(pntr_image* dst, int x, int y, pntr_color color);

#ifdef __cplusplus
}
#endif

/**
 * @defgroup colors Colors
 * @{
 */

#ifndef PNTR_LIGHTGRAY
/**
 * Light gray.
 */
#define PNTR_LIGHTGRAY  pntr_new_color(200, 200, 200, 255)
#endif
#ifndef PNTR_GRAY
/**
 * Gray.
 */
#define PNTR_GRAY       pntr_new_color(130, 130, 130, 255)
#endif
#ifndef PNTR_DARKGRAY
/**
 * Dark gray.
 */
#define PNTR_DARKGRAY   pntr_new_color(80, 80,  80, 255)
#endif
#ifndef PNTR_YELLOW
/**
 * Yellow.
 */
#define PNTR_YELLOW     pntr_new_color(253, 249, 0, 255)
#endif
#ifndef PNTR_GOLD
/**
 * Gold.
 */
#define PNTR_GOLD       pntr_new_color(255, 203, 0, 255)
#endif
#ifndef PNTR_ORANGE
/**
 * Orange.
 */
#define PNTR_ORANGE     pntr_new_color(255, 161, 0, 255)
#endif
#ifndef PNTR_PINK
/**
 * Pink.
 */
#define PNTR_PINK       pntr_new_color(255, 109, 194, 255)
#endif
#ifndef PNTR_RED
/**
 * Red.
 */
#define PNTR_RED        pntr_new_color(230, 41, 55, 255)
#endif
#ifndef PNTR_MAROON
/**
 * Maroon.
 */
#define PNTR_MAROON     pntr_new_color(190, 33, 55, 255)
#endif
#ifndef PNTR_GREEN
/**
 * Green.
 */
#define PNTR_GREEN      pntr_new_color(0, 228, 48, 255)
#endif
#ifndef PNTR_LIME
/**
 * Lime.
 */
#define PNTR_LIME       pntr_new_color(0, 158, 47, 255)
#endif
#ifndef PNTR_DARKGREEN
/**
 * Dark green.
 */
#define PNTR_DARKGREEN  pntr_new_color(0, 117, 44, 255)
#endif
#ifndef PNTR_SKYBLUE
/**
 * Sky blue.
 */
#define PNTR_SKYBLUE    pntr_new_color(102, 191, 255, 255)
#endif
#ifndef PNTR_BLUE
/**
 * Blue.
 */
#define PNTR_BLUE       pntr_new_color(0, 121, 241, 255)
#endif
#ifndef PNTR_DARKBLUE
/**
 * Dark blue.
 */
#define PNTR_DARKBLUE   pntr_new_color(0, 82, 172, 255)
#endif
#ifndef PNTR_PURPLE
/**
 * Purple.
 */
#define PNTR_PURPLE     pntr_new_color(200, 122, 255, 255)
#endif
#ifndef PNTR_VIOLET
/**
 * Violet.
 */
#define PNTR_VIOLET     pntr_new_color(135, 60, 190, 255)
#endif
#ifndef PNTR_DARKPURPLE
/**
 * Dark purple.
 */
#define PNTR_DARKPURPLE pntr_new_color(112, 31, 126, 255)
#endif
#ifndef PNTR_BEIGE
/**
 * Beige.
 */
#define PNTR_BEIGE      pntr_new_color(211, 176, 131, 255)
#endif
#ifndef PNTR_BROWN
/**
 * Brown.
 */
#define PNTR_BROWN      pntr_new_color(127, 106, 79, 255)
#endif
#ifndef PNTR_DARKBROWN
/**
 * Dark brown.
 */
#define PNTR_DARKBROWN  pntr_new_color(76, 63, 47, 255)
#endif
#ifndef PNTR_WHITE
/**
 * White.
 */
#define PNTR_WHITE      pntr_new_color(255, 255, 255, 255)
#endif

#ifndef PNTR_WHITE_VALUE
/**
 * The integer representation of PNTR_WHITE.
 *
 * @note This is the same as \c PNTR_WHITE.value .
 *
 * @private
 * @internal
 */
#define PNTR_WHITE_VALUE 4294967295
#endif  // PNTR_WHITE_VALUE

#ifndef PNTR_BLACK
/**
 * Black.
 */
#define PNTR_BLACK      pntr_new_color(0, 0, 0, 255)
#endif
#ifndef PNTR_BLANK
/**
 * Blank, or transparent.
 */
#define PNTR_BLANK      pntr_new_color(0, 0, 0, 0)
#endif
#ifndef PNTR_MAGENTA
/**
 * Magenta.
 */
#define PNTR_MAGENTA    pntr_new_color(255, 0, 255, 255)
#endif
#ifndef PNTR_RAYWHITE
/**
 * The white used in raylib.
 */
#define PNTR_RAYWHITE   pntr_new_color(245, 245, 245, 255)
#endif

/**
 * @}
 */

#endif  // PNTR_H__

#ifdef PNTR_IMPLEMENTATION
#ifndef PNTR_IMPLEMENTATION_ONCE
#define PNTR_IMPLEMENTATION_ONCE

#if defined(PNTR_ENABLE_UTF8) && !defined(_DOXYGEN_)
    #include "external/utf8.h"
    #define PNTR_STRSTR utf8str
    #define PNTR_STRCHR utf8chr
    #define PNTR_STRLEN utf8len
    #define PNTR_STRSIZE utf8size
    #define PNTR_STRCODEPOINT utf8codepoint
    typedef utf8_int32_t pntr_codepoint_t;
#else
    /**
     * A type representing a single character or UTF-8 codepoint.
     *
     * With UTF-8, a single character can be up to 4 bytes, so having this type define that helps determine its size quickly.
     *
     * @see PNTR_ENABLE_UTF8
     */
    typedef char pntr_codepoint_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup memory Memory
 * @{
 */

#ifndef PNTR_MALLOC
    #include <stdlib.h>
    /**
     * Allocates the requested memory and returns a pointer to it.
     *
     * @param size (size_t) number of bytes to allocate
     *
     * @return On success, returns the pointer to the beginning of newly allocated memory.
     * @see PNTR_FREE
     * @see https://en.cppreference.com/w/c/memory/malloc
     */
    #define PNTR_MALLOC(size) malloc(size)
#endif  // PNTR_MALLOC

#ifndef PNTR_FREE
    #include <stdlib.h>
    /**
     * Deallocates the previously allocated memory.
     *
     * @param ptr (void*) pointer to the memory to deallocate
     *
     * @see PNTR_MALLOC
     * @see https://en.cppreference.com/w/c/memory/free
     */
    #define PNTR_FREE(ptr) free(ptr)
#endif  // PNTR_FREE

#ifndef PNTR_REALLOC
    #include <stdlib.h>
    /**
     * Attempts to resize the memory block pointed to that was previously allocated.
     *
     * @param ptr (void*) pointer to the memory area to be reallocated
     * @param new_size (size_t) new size of the array in bytes
     *
     * @return On success, returns the pointer to the beginning of newly allocated memory. To avoid a memory leak, the returned pointer must be deallocated with free or realloc. The original pointer ptr is invalidated and any access to it is undefined behavior (even if reallocation was in-place).
     *
     * @see https://en.cppreference.com/w/c/memory/realloc
     */
    #define PNTR_REALLOC(ptr, new_size) realloc(ptr, new_size)
#endif  // PNTR_REALLOC

#ifndef PNTR_MEMCPY
    #include <string.h>
    /**
     * Copies data from memory area src to the destination memory.
     *
     * @param dest (void*) pointer to the object to copy to
     * @param src (const void*) pointer to the object to copy from
     * @param n (size_t) number of bytes to copy
     *
     * @see https://en.cppreference.com/w/c/string/byte/memcpy
     */
    #define PNTR_MEMCPY(dest, src, n) memcpy(dest, src, (n))
#endif  // PNTR_MEMCPY

#ifndef PNTR_MEMSET
    #include <string.h>
    /**
     * Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.
     */
    #define PNTR_MEMSET(str, c, n) memset((str), (c), (n))
#endif  // PNTR_MEMSET

/**
 * @}
 */

/**
 * @defgroup strings String Manipulation
 * @{
 */

#ifndef PNTR_STRSTR
    #include <string.h>
    /**
     * Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
     *
     * By default, will use string.h's `strstr`. When `PNTR_ENABLE_UTF8` is enabled, will be `utf8str`.
     *
     * @param str1 (const char*) C string to be scanned.
     * @param str2 (const char*) containing the sequence of characters to match.
     *
     * @return A pointer to the first occurrence in str1 of the entire sequence of characters specified in str2, or a null pointer if the sequence is not present in str1.
     *
     * @see PNTR_ENABLE_UTF8
     */
    #define PNTR_STRSTR strstr
#endif

#ifndef PNTR_STRCHR
    #include <string.h>
    /**
     * Returns a pointer to the first occurance of a character in a string.
     *
     * By default, will use string.h's `strchr`. When `PNTR_ENABLE_UTF8` is enabled, will be `utf8chr`.
     *
     * @see PNTR_ENABLE_UTF8
     */
    #define PNTR_STRCHR strchr
#endif

#ifndef PNTR_STRLEN
    #include <string.h>
    /**
     * Returns the length of a string.
     *
     * By default, will use string.h's `strlen`. When `PNTR_ENABLE_UTF8` is enabled, will be `utf8len`.
     *
     * @see PNTR_ENABLE_UTF8
     */
    #define PNTR_STRLEN strlen
#endif

#ifndef PNTR_STRSIZE
    #include <string.h>
    /**
     * Calculates the amount of bytes in a string, including the null character.
     *
     * By default, will use string.h's `strlen(text) + 1`. When `PNTR_ENABLE_UTF8` is enabled, this will be `utf8size`.
     *
     * @see PNTR_ENABLE_UTF8
     */
    #define PNTR_STRSIZE(text) ((PNTR_STRLEN(text) + (size_t)1))
#endif

#ifndef PNTR_STRCODEPOINT
    /**
     * Sets out_codepoint to the current utf8 codepoint in str, and returns the address of the next utf8 codepoint after the current one in str.
     *
     * @param str The string to get the codepoint from
     * @param out_codepoint The codepoint to set
     *
     * @return The address of the next codepoint.
     *
     * @private
     * @internal
     * @see PNTR_ENABLE_UTF8
     * @see utf8codepoint
     */
    char* pntr_strcodepoint(const char * str, char* out_codepoint) {
        if (str == NULL) {
            *out_codepoint = 0;
        }

        *out_codepoint = str[0];
        return (char*)(str + 1);
    }

    /**
     * Sets out_codepoint to the current utf8 codepoint in str, and returns the address of the next utf8 codepoint after the current one in str.
     *
     * When `PNTR_ENABLE_UTF8` is enabled, will be `utf8codepoint`.
     *
     * @see PNTR_ENABLE_UTF8
     * @see pntr_strcodepoint
     */
    #define PNTR_STRCODEPOINT pntr_strcodepoint
#endif

/**
 * @}
 */

/**
 * @defgroup math Math
 * @{
 */

#ifndef PNTR_PI
    /**
     * Pi as a floating point value.
     *
     * @see https://en.wikipedia.org/wiki/Pi
     */
    #define PNTR_PI 3.1415926535897932f
#endif

#ifndef PNTR_DEG2RAD
    /**
     * Convert a degree to radians with a floating point value. PI / 180.
     *
     * @code
     * float radians = degrees * PNTR_DEG2RAD
     * @endcode
     */
    #define PNTR_DEG2RAD 0.017453293f
#endif

#if !defined(PNTR_ENABLE_MATH) || defined(_DOXYGEN_)
    #ifndef PNTR_SINF
        /**
         * @internal
         *
         * @see PNTR_SINF
         */
        float _pntr_sinf(float x) {
            static const float a0 = +1.91059300966915117e-31f;
            static const float a1 = +1.00086760103908896f;
            static const float a2 = -1.21276126894734565e-2f;
            static const float a3 = -1.38078780785773762e-1f;
            static const float a4 = -2.67353392911981221e-2f;
            static const float a5 = +2.08026600266304389e-2f;
            static const float a6 = -3.03996055049204407e-3f;
            static const float a7 = +1.38235642404333740e-4f;
            return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*a7))))));
        }

        /**
         * Calculates sine of the given value in radians.
         *
         * @param value The input value of sinf()
         *
         * @return The sine of the given value.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/sin
         * @see https://github.com/Immediate-Mode-UI/Nuklear/blob/master/nuklear.h
         */
        #define PNTR_SINF(value) _pntr_sinf(value)
    #endif  // PNTR_SINF

    #ifndef PNTR_COSF
        /**
         * @internal
         *
         * @see PNTR_COSF
         */
        float _pntr_cosf(float x) {
            static const float a0 = 9.9995999154986614e-1f;
            static const float a1 = 1.2548995793001028e-3f;
            static const float a2 = -5.0648546280678015e-1f;
            static const float a3 = 1.2942246466519995e-2f;
            static const float a4 = 2.8668384702547972e-2f;
            static const float a5 = 7.3726485210586547e-3f;
            static const float a6 = -3.8510875386947414e-3f;
            static const float a7 = 4.7196604604366623e-4f;
            static const float a8 = -1.8776444013090451e-5f;
            return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*(a5 + x*(a6 + x*(a7 + x*a8)))))));
        }

        /**
         * Calculates cosine of the given value.
         *
         * @param value Floating-point value representing angle in radians
         *
         * @return The cosine of the given value.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/cos
         * @see https://github.com/Immediate-Mode-UI/Nuklear/blob/master/nuklear.h
         */
        #define PNTR_COSF(value) _pntr_cosf(value)
    #endif  // PNTR_COSF

    #ifndef PNTR_CEILF
        /**
         * @internal
         *
         * @see PNTR_CEILF
         */
        float _pntr_ceilf(float x) {
            if (x >= 0.0f) {
                int i = (int)x;
                return (x > i) ? (float)i + 1.0f : (float)i;
            } else {
                int t = (int)x;
                float r = x - (float)t;
                return (r > 0.0f) ? (float)t + 1.0f: (float)t;
            }
        }

        /**
         * Computes the smallest integer value not less than arg.
         *
         * @param x Floating-point value
         *
         * @return The smallest integer value not less than arg, that is ⌈arg⌉, is returned.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/ceil
         */
        #define PNTR_CEILF(x) _pntr_ceilf(x)
    #endif  // PNTR_CEILF

    #ifndef PNTR_FABSF
        /**
         * Computes the absolute value of a floating point value.
         *
         * @param x Floating point value
         *
         * @return The absolute value of the given value.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/fabs
         */
        #define PNTR_FABSF(x) (((x) < 0) ? -(x) : (x))
    #endif  // PNTR_FABSF

    #ifndef PNTR_FLOORF
        /**
         * Computes the largest integer value not greater than arg.
         *
         * @param x Floating point value.
         *
         * @return The largest integer value not greater than arg.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/floor
         */
        #define PNTR_FLOORF(x) (float)(((int)(x)) - (((x) < 0.0f) ? 1 : 0))
    #endif  // PNTR_FLOORF

    #ifndef PNTR_FMODF
        /**
         * Computes the floating-point remainder of the division operation x/y.
         *
         * @param dividend floating point value
         * @param divisor floating point value
         * @return The modulus of the division operation.
         *
         * @see https://en.cppreference.com/w/c/numeric/math/fmod
         */
        #define PNTR_FMODF(dividend, divisor) ((divisor) == 0.0f ? 0.0f : (dividend) - ((int)((dividend) / (divisor))) * (divisor))
    #endif  // PNTR_FMOD
#else
    #ifndef PNTR_SINF
        #include <math.h>
        #define PNTR_SINF sinf
    #endif  // PNTR_SINF

    #ifndef PNTR_COSF
        #include <math.h>
        #define PNTR_COSF cosf
    #endif  // PNTR_COSF

    #ifndef PNTR_CEILF
        #include <math.h>
        #define PNTR_CEILF ceilf
    #endif  // PNTR_CEILF

    #ifndef PNTR_FABSF
        #include <math.h>
        #define PNTR_FABSF fabsf
    #endif  // PNTR_FABSF

    #ifndef PNTR_FLOORF
        #include <math.h>
        #define PNTR_FLOORF floorf
    #endif  // PNTR_FLOORF

    #ifndef PNTR_SQRTF
        #include <math.h>
        #define PNTR_SQRTF sqrtf
    #endif  // PNTR_SQRTF

    #ifndef PNTR_FMODF
        #include <math.h>
        #define PNTR_FMODF fmodf
    #endif  // PNTR_FMODF
#endif  // PNTR_ENABLE_MATH

#ifndef PNTR_MAX
    /**
     * Return the largest value of the two given values.
     *
     * @param a The first value to compare.
     * @param b The second value to compare.
     *
     * @return Which value is larger.
     */
    #define PNTR_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef PNTR_MIN
    /**
     * Return the smallest value of the two given values.
     *
     * @param a The first value to compare.
     * @param b The second value to compare.
     *
     * @return Which value is smaller.
     */
    #define PNTR_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

/**
 * @}
 */

// STB TrueType
#ifdef PNTR_ENABLE_TTF
    #ifdef PNTR_NO_STB_TRUETYPE_IMPLEMENTATION
        #ifdef STB_TRUETYPE_IMPLEMENTATION
            #undef STB_TRUETYPE_IMPLEMENTATION
        #endif  // STB_TRUETYPE_IMPLEMENTATION
    #else  // PNTR_NO_STB_TRUETYPE_IMPLEMENTATION

        #ifndef STBTT_ifloor
            #define STBTT_ifloor(x) ((int)PNTR_FLOORF(x))
        #endif

        #ifndef STBTT_iceil
            #define STBTT_iceil(x) ((int)PNTR_CEILF(x))
        #endif

        #ifndef STBTT_fmod
            #define STBTT_fmod(x, y) PNTR_FMODF((x), (y))
        #endif

        #ifndef STBTT_cos
            #define STBTT_cos(x) PNTR_COSF((float)(x))
        #endif

        #ifndef STBTT_fabs
            #define STBTT_fabs(x) PNTR_FABSF(x)
        #endif

        #ifndef PNTR_ENABLE_MATH
            #ifndef STBTT_sqrt
                float _pntr_sqrtf(float number) {
                    float guess = number / 2.0f;
                    float epsilon = 1e-6f;
                    while (true) {
                        float next_guess = 0.5f * (guess + number / guess);
                        if (PNTR_FABSF(next_guess - guess) < epsilon) {
                            return next_guess;
                        }
                        guess = next_guess;
                    }
                }
                #define STBTT_sqrt(x) _pntr_sqrtf(x)
            #endif  // PNTR_SQRTF

            #ifndef STBTT_pow
                float _pntr_pow(float base, float exponent) {
                    float result = 1.0f;
                    if (exponent >= 0) {
                        for (int i = 0; i < exponent; i++) {
                            result *= base;
                        }
                    } else {
                        for (int i = 0; i > exponent; i--) {
                            result /= base;
                        }
                    }
                    return result;
                }
                #define STBTT_pow(x, y) _pntr_pow((x), (y))
            #endif

            #ifndef STBTT_acos
                float _pntr_acos(float x) {
                    float negate = (float)(x < 0);
                    x = PNTR_FABSF(x);
                    float ret = -0.0187293f;
                    ret = ret * x;
                    ret = ret + 0.0742610f;
                    ret = ret * x;
                    ret = ret - 0.2121144f;
                    ret = ret * x;
                    ret = ret + 1.5707288f;
                    ret = ret * STBTT_sqrt(1.0f - x);
                    ret = ret - 2 * negate * ret;
                    return negate * PNTR_PI + ret;
                }
                #define STBTT_acos(x) _pntr_acos((x))
            #endif
        #else  // PNTR_ENABLE_MATH
            #ifndef STBTT_sqrt
                #define STBTT_sqrt(x) sqrt(x)
            #endif
            #ifndef STBTT_pow
                #define STBTT_pow(x, y) pow(x, y)
            #endif
            #ifndef STBTT_acos
                #define STBTT_acos(x) acos(x)
            #endif
        #endif  // PNTR_ENABLE_MATH

        #ifndef STBTT_malloc
            #define STBTT_malloc(x,u) ((void)(u), PNTR_MALLOC(x))
        #endif  // STBTT_malloc

        #ifndef STBTT_free
            #define STBTT_free(x,u)   ((void)(u), PNTR_FREE(x))
        #endif  // STBTT_free

        #ifndef STBTT_assert
            #define STBTT_assert(x) ((void)(0))
        #endif  // STBTT_assert

        #ifndef STBTT_strlen
            #define STBTT_strlen(x) PNTR_STRLEN(x)
        #endif  // STBTT_strlen

        #ifndef STBTT_memcpy
            #define STBTT_memcpy PNTR_MEMCPY
        #endif  // STBTT_memcpy

        #ifndef STBTT_memset
            #define STBTT_memset PNTR_MEMSET
        #endif  // STBTT_memset

        #define STB_TRUETYPE_IMPLEMENTATION
    #endif  // PNTR_NO_STB_TRUETYPE_IMPLEMENTATION

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wpragmas"
        #pragma GCC diagnostic ignored "-Wunknown-pragmas"
        #pragma GCC diagnostic ignored "-Wsign-conversion"
        #pragma GCC diagnostic ignored "-Wconversion"
    #endif  // defined(__GNUC__) || defined(__clang__)

    #include "external/stb_truetype.h"
    #define PNTR_NO_STB_TRUETYPE_IMPLEMENTATION

    #if defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #endif  // defined(__GNUC__) || defined(__clang__)
#endif  // PNTR_ENABLE_TTF

#ifdef PNTR_ENABLE_VARGS
    // For pntr_draw_text_ex()
    #include <stdarg.h> // va_list, va_start, va_end
    #include <stdio.h> // vsprintf
#endif

/**
 * Retrieve the pixel at the given x,y coordinate of the image.
 *
 * @param image The image to check against.
 * @param x The x coordinate.
 * @param y The y coordinate.
 *
 * @return The pixel color at the given coordinate.
 * @internal
 */
#define PNTR_PIXEL(image, x, y) image->data[(y) * (image->pitch >> 2) + (x)]

/**
 * Create a new color with the given red, green, blue, and alpha values.
 *
 * @def PNTR_NEW_COLOR(red, green, blue, alpha)
 * @param r The red value.
 * @param g The green value.
 * @param b The blue value.
 * @param a The alpha value.
 *
 * @return The new color.
 * @internal
 */
#ifndef PNTR_NEW_COLOR
    #if defined(PNTR_PIXELFORMAT_RGBA)
        #define PNTR_NEW_COLOR(red, green, blue, alpha) PNTR_CLITERAL(pntr_color) { \
            .rgba = { \
                .r = red, \
                .g = green, \
                .b = blue, \
                .a = alpha \
            } \
        }
    #elif defined(PNTR_PIXELFORMAT_ARGB)
        #define PNTR_NEW_COLOR(red, green, blue, alpha) PNTR_CLITERAL(pntr_color) { \
            .rgba = { \
                .b = blue, \
                .g = green, \
                .r = red, \
                .a = alpha, \
            } \
        }
    #endif
#endif

/**
 * The last error that was reported from pntr.
 *
 * This will not work across different threads.
 *
 * @see pntr_get_error
 * @see pntr_set_error
 * @internal
 * @private
 */
pntr_error _pntr_error;

PNTR_API const char* pntr_get_error(void) {
    switch (_pntr_error) {
        case PNTR_ERROR_NONE: return NULL;
        case PNTR_ERROR_INVALID_ARGS: return "Invalid arguments";
        case PNTR_ERROR_NO_MEMORY: return "No memory";
        case PNTR_ERROR_NOT_SUPPORTED: return "Not supported";
        case PNTR_ERROR_FAILED_TO_OPEN: return "Failed to open";
        case PNTR_ERROR_FAILED_TO_WRITE: return "Failed to write";
        case PNTR_ERROR_UNKNOWN: return "Unknown error";
    }

    return NULL;
}

PNTR_API pntr_error pntr_get_error_code(void) {
    return _pntr_error;
}

/**
 * Sets an error.
 *
 * @param error A string representing the error that had just occured.
 *
 * @return Always returns NULL.
 */
PNTR_API void* pntr_set_error(pntr_error error) {
    _pntr_error = error;

    #ifdef PNTR_SET_ERROR
    PNTR_SET_ERROR(error);
    #endif

    return NULL;
}

/**
 * Create a new image at the given width and height.
 *
 * This method will not clear the image upon instantiation.
 *
 * @param width The width of the new image.
 * @param height The height of the new image.
 *
 * @return The new image that is the size of the given width/height.
 *
 * @see pntr_gen_image_color()
 */
PNTR_API pntr_image* pntr_new_image(int width, int height) {
    if (width <= 0 || height <= 0) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* image = (pntr_image*)PNTR_MALLOC(sizeof(pntr_image));
    if (image == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    image->pitch = width * (int)sizeof(pntr_color);
    image->width = width;
    image->height = height;
    pntr_image_reset_clip(image);
    image->subimage = false;
    image->data = (pntr_color*)PNTR_MALLOC((size_t)(image->pitch * height));
    if (image->data == NULL) {
        PNTR_FREE(image);
        return (pntr_image*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    return image;
}

/**
 * Generate a new image with the given color.
 *
 * @param width The width of the new image.
 * @param height The height of the given image.
 * @param color The desired color that will fill the new image.
 *
 * @return A pointer to the new image in memory.
 */
PNTR_API pntr_image* pntr_gen_image_color(int width, int height, pntr_color color) {
    pntr_image* image = pntr_new_image(width, height);
    pntr_clear_background(image, color);

    return image;
}

/**
 * Create an image duplicate.
 *
 * @param image The image that you want to copy.
 *
 * @return A pointer to the new image that is a copy of the original image.
 */
PNTR_API pntr_image* pntr_image_copy(pntr_image* image) {
    if (image == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* newImage = pntr_gen_image_color(image->width, image->height, PNTR_BLANK);
    if (newImage == NULL) {
        return NULL;
    }

    pntr_draw_image(newImage, image, 0, 0);
    newImage->clip = image->clip;

    return newImage;
}

/**
 * Alpha blend the source color into the destination color.
 *
 * @param dst The destination color.
 * @param src The source color.
 *
 * @see PNTR_NO_ALPHABLEND
 * @see pntr_color_alpha_blend()
 */
PNTR_API
#ifdef PNTR_NO_ALPHABLEND
inline
#endif
void pntr_blend_color(pntr_color* dst, pntr_color src) {
    if (src.rgba.a == 255) {
        *dst = src;
        return;
    }
    #ifndef PNTR_NO_ALPHABLEND
        if (src.rgba.a == 0) {
            return;
        }

        unsigned int alpha = (unsigned int)src.rgba.a + 1;     // We are shifting by 8 (dividing by 256), so we need to take that excess into account
        unsigned int dstAlpha = (unsigned int)dst->rgba.a * (256 - alpha);
        dst->rgba.a = (unsigned char)((alpha * 256 + dstAlpha) >> 8);

        if (dst->rgba.a > 0) {
            dst->rgba.r = (unsigned char)((((unsigned int)src.rgba.r * alpha * 256 + (unsigned int)dst->rgba.r * dstAlpha) / dst->rgba.a) >> 8);
            dst->rgba.g = (unsigned char)((((unsigned int)src.rgba.g * alpha * 256 + (unsigned int)dst->rgba.g * dstAlpha) / dst->rgba.a) >> 8);
            dst->rgba.b = (unsigned char)((((unsigned int)src.rgba.b * alpha * 256 + (unsigned int)dst->rgba.b * dstAlpha) / dst->rgba.a) >> 8);
        }
    #endif
}

/**
 * Get a new rectangle representing the intersection of the two given rectangles.
 *
 * @code
 * pntr_rectangle dstRect;
 * if (!_pntr_rectangle_intersect(10, 10, 20, 20, image->clip.x, image->clip.y, image->clip.width, image>clip.height, dstRect)) {
 *     return;
 * }
 * @endcode
 *
 * @param x The input rectangle's x coordinate.
 * @param y The input rectangle's y coordinate.
 * @param width The input rectangle's width.
 * @param height The input rectangle's height.
 * @param destX The destination x coordinate.
 * @param destY The destination y coordinate.
 * @param destWidth The destination rectangle's width.
 * @param destHeight The destination rectangle's height.
 * @param out The normalized rectangle.
 *
 * @return True if the intersect of the rectangle has a width and height greater than 0, false otherwise.
 */
PNTR_API bool _pntr_rectangle_intersect(int x, int y, int width, int height, int destX, int destY, int destWidth, int destHeight, pntr_rectangle *out) {
    if (width <= 0 || height <= 0) {
        return false;
    }

    out->x = PNTR_MAX(x, destX);
    out->width = PNTR_MIN(x + width, destX + destWidth) - out->x;
    if (out->width <= 0) {
        return false;
    }

    out->y = PNTR_MAX(y, destY);
    out->height = PNTR_MIN(y + height, destY + destHeight) - out->y;
    if (out->height <= 0) {
        return false;
    }

    return true;
}

/**
 * Creates a new image from a section of the original image.
 *
 * The new image must be cleared with pntr_unload_image().
 *
 * @param image The original image to build the new image from.
 * @param x The x coordinate to build the new image from.
 * @param y The y coordinate to build the new image from.
 * @param width The width of the new image.
 * @param height The height of the new image.
 *
 * @return A new image that is based off of the section of the original image.
 *
 * @see pntr_image_subimage()
 * @see pntr_unload_image()
 */
PNTR_API pntr_image* pntr_image_from_image(pntr_image* image, int x, int y, int width, int height) {
    if (image == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_rectangle dstRect;
    if (!_pntr_rectangle_intersect(x, y, width, height, 0, 0, image->width, image->height, &dstRect)) {
        return NULL;
    }

    pntr_image* result = pntr_new_image(dstRect.width, dstRect.height);
    if (result == NULL) {
        return NULL;
    }

    for (int destY = 0; destY < dstRect.height; destY++) {
        PNTR_MEMCPY(&PNTR_PIXEL(result, 0, destY),
            &PNTR_PIXEL(image, dstRect.x, dstRect.y + destY),
            (size_t)result->pitch);
    }

    return result;
}

/**
 * Creates an image that references a section of another image.
 *
 * This is useful to have images reference a sprite in a tileset. Sub-images still need to be cleared with pntr_unload_image().
 *
 * @param image The original image to reference for the new portion of the image.
 * @param x The X coorindate of the subimage.
 * @param y The Y coordinate of the subimage.
 * @param width The width of the subimage.
 * @param height The height of the subimage.
 *
 * @return The pntr_image referencing the section of the given image.
 *
 * @see pntr_image_from_image()
 * @see pntr_unload_image()
 */
PNTR_API pntr_image* pntr_image_subimage(pntr_image* image, int x, int y, int width, int height) {
    if (image == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Ensure we are referencing an actual portion of the image.
    pntr_rectangle dstRect;
    if (!_pntr_rectangle_intersect(x, y, width, height, 0, 0, image->width, image->height, &dstRect)) {
        return NULL;
    }

    // Build the subimage.
    pntr_image* subimage = (pntr_image*)PNTR_MALLOC(sizeof(pntr_image));
    if (subimage == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    subimage->pitch = image->pitch;
    subimage->width = dstRect.width;
    subimage->height = dstRect.height;
    subimage->subimage = true;
    pntr_image_reset_clip(subimage);
    subimage->data = &PNTR_PIXEL(image, dstRect.x, dstRect.y);

    return subimage;
}

/**
 * Unloads the given image from memory.
 *
 * @param image The image to unload from memory.
 */
PNTR_API void pntr_unload_image(pntr_image* image) {
    if (image == NULL) {
        return;
    }

    // Only clear full image data.
    if (!image->subimage && image->data != NULL) {
        PNTR_FREE(image->data);
    }

    PNTR_FREE(image);
}

/**
 * Draws a line on the destination image.
 */
PNTR_API void pntr_put_horizontal_line_unsafe(pntr_image* dst, int posX, int posY, int width, pntr_color color) {
    pntr_color *row = &PNTR_PIXEL(dst, posX, posY);
    while (--width >= 0) {
        row[width] = color;
    }
}

/**
 * Clears an image with the given color.
 *
 * @details Clearing the background ignores clipping.
 *
 * @param image The image to clear.
 * @param color The color to fill the image with.
 */
PNTR_API void pntr_clear_background(pntr_image* image, pntr_color color) {
    if (image == NULL) {
        return;
    }

    // Blank or white can have some performance optimization.
    if (!image->subimage) {
        // White
        if (color.value == PNTR_WHITE_VALUE) {
            PNTR_MEMSET((void*)image->data, 255, (size_t)(image->height * image->pitch));
            return;
        }

        // Blank
        if (color.rgba.a == 0) {
            PNTR_MEMSET((void*)image->data, 0, (size_t)(image->height * image->pitch));
            return;
        }
    }

    // Draw the first line
    pntr_put_horizontal_line_unsafe(image, 0, 0, image->width, color);

    // Copy the line for the rest of the background
    for (int y = 1; y < image->height; y++) {
        PNTR_MEMCPY(&PNTR_PIXEL(image, 0, y), image->data, (size_t)image->pitch);
    }
}

/**
 * Creates a new color, provided the given red, green, blue, and alpha colors.
 *
 * @param red The red channel.
 * @param green The green channel.
 * @param blue The blue channel.
 * @param alpha The alpha channel.
 *
 * @return The color with the given red, green, blue, and alpha components.
 */
PNTR_API pntr_color pntr_new_color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    return PNTR_NEW_COLOR(red, green, blue, alpha);
}

/**
 * Get a pntr_color from a RGBA hexadecimal value
 *
 * @param hexValue The RGBA hexadecimal value representing the color. For example: 0x052c46ff.
 *
 * @return The color representing the given hex value.
 */
PNTR_API pntr_color pntr_get_color(unsigned int hexValue) {
    return PNTR_NEW_COLOR(
        (unsigned char)((hexValue >> 24U) & (unsigned int)0xFF),
        (unsigned char)((hexValue >> 16U) & (unsigned int)0xFF),
        (unsigned char)((hexValue >> 8U) & (unsigned int)0xFF),
        (unsigned char)(hexValue & (unsigned int)0xFF)
    );
}

PNTR_API unsigned char pntr_color_r(pntr_color color) {
    return color.rgba.r;
}

PNTR_API unsigned char pntr_color_g(pntr_color color) {
    return color.rgba.g;
}

PNTR_API unsigned char pntr_color_b(pntr_color color) {
    return color.rgba.b;
}

PNTR_API unsigned char pntr_color_a(pntr_color color) {
    return color.rgba.a;
}

PNTR_API void pntr_color_set_r(pntr_color* color, unsigned char r) {
    color->rgba.r = r;
}

PNTR_API void pntr_color_set_g(pntr_color* color, unsigned char g) {
    color->rgba.g = g;
}

PNTR_API void pntr_color_set_b(pntr_color* color, unsigned char b) {
    color->rgba.b = b;
}

PNTR_API void pntr_color_set_a(pntr_color* color, unsigned char a) {
    color->rgba.a = a;
}

/**
 * Draws a point on the given image, without safety checks.
 */
PNTR_API void pntr_draw_point_unsafe(pntr_image* dst, int x, int y, pntr_color color) {
    pntr_blend_color(&PNTR_PIXEL(dst, x, y), color);
}

/**
 * Draws a pixel on the given image.
 */
PNTR_API void pntr_draw_point(pntr_image* dst, int x, int y, pntr_color color) {
   if ((color.rgba.a == 0) || (dst == NULL) || (x < dst->clip.x) || (x >= dst->clip.x + dst->clip.width) || (y < dst->clip.y) || (y >= dst->clip.y + dst->clip.height)) {
        return;
    }

    pntr_draw_point_unsafe(dst, x, y, color);
}

PNTR_API void pntr_draw_point_vec(pntr_image* dst, pntr_vector* point, pntr_color color) {
    if (point != NULL) {
        pntr_draw_point(dst, point->x, point->y, color);
    }
}

PNTR_API void pntr_draw_points(pntr_image* dst, pntr_vector* points, int pointsCount, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0 || points == NULL || pointsCount <= 0) {
        return;
    }

    for (int i = 0; i < pointsCount; i++) {
        if (points[i].x >= dst->clip.x && points[i].x < dst->clip.x + dst->clip.width && points[i].y >= dst->clip.y && points[i].y < dst->clip.y + dst->clip.height) {
            pntr_draw_point_unsafe(dst, points[i].x, points[i].y, color);
        }
    }
}

/**
 * Draws a line on the given image.
 *
 * TODO: pntr_draw_line: Add anti-aliased, and thickness to the lines.
 *
 * @see pntr_draw_line_horizontal()
 * @see pntr_draw_line_vertical()
 */
PNTR_API void pntr_draw_line(pntr_image *dst, int startPosX, int startPosY, int endPosX, int endPosY, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0) {
        return;
    }

    int changeInX = (endPosX - startPosX);
    int absChangeInX = (changeInX < 0) ? -changeInX : changeInX;
    int changeInY = (endPosY - startPosY);
    int absChangeInY = (changeInY < 0) ? -changeInY : changeInY;

    // Drawing a straight line is fast.
    if (startPosX == endPosX) {
        pntr_draw_line_vertical(dst, startPosX, (startPosY > endPosY) ? endPosY : startPosY, absChangeInY, color);
        return;
    }

    if (startPosY == endPosY) {
        pntr_draw_line_horizontal(dst, (startPosX > endPosX) ? endPosX : startPosX, startPosY, absChangeInX, color);
        return;
    }

    int startU, startV, endU, stepV;
    int A, B, P;
    int reversedXY = (absChangeInY < absChangeInX);

    if (reversedXY) {
        A = 2 * absChangeInY;
        B = A - 2 * absChangeInX;
        P = A - absChangeInX;

        if (changeInX > 0) {
            startU = startPosX;
            startV = startPosY;
            endU = endPosX;
            //endV = endPosY;
        }
        else {
            startU = endPosX;
            startV = endPosY;
            endU = startPosX;
            //endV = startPosY;

            // Since start and end are reversed
            changeInX = -changeInX;
            changeInY = -changeInY;
        }

        stepV = (changeInY < 0) ? -1 : 1;

        pntr_draw_point(dst, startU, startV, color);
    }
    else {
        A = 2 * absChangeInX;
        B = A - 2 * absChangeInY;
        P = A - absChangeInY;

        if (changeInY > 0) {
            startU = startPosY;
            startV = startPosX;
            endU = endPosY;
        }
        else {
            startU = endPosY;
            startV = endPosX;
            endU = startPosY;

            changeInX = -changeInX;
            changeInY = -changeInY;
        }

        stepV = (changeInX < 0) ? -1 : 1;

        pntr_draw_point(dst, startV, startU, color);
    }

    for (int u = startU + 1, v = startV; u <= endU; u++) {
        if (P >= 0) {
            v += stepV;
            P += B;
        }
        else {
            P += A;
        }

        if (reversedXY) {
            pntr_draw_point(dst, u, v, color);
        }
        else {
            pntr_draw_point(dst, v, u, color);
        }
    }
}

/**
 * Draws a line on the given image, with thickness
 */
PNTR_API void pntr_draw_line_thick(pntr_image *dst, int startPosX, int startPosY, int endPosX, int endPosY, int thickness, pntr_color color) {
    if (thickness < 1) {
        return;
    }
    if (thickness == 1) {
        pntr_draw_line(dst, startPosX, startPosY, endPosX, endPosY, color);
        return;
    }

    if (dst == NULL || color.rgba.a == 0) {
        return;
    }

    int changeInX = (endPosX - startPosX);
    int absChangeInX = (changeInX < 0) ? -changeInX : changeInX;
    int changeInY = (endPosY - startPosY);
    int absChangeInY = (changeInY < 0) ? -changeInY : changeInY;

    // Drawing a straight line is fast.
    if (startPosX == endPosX) {
        pntr_draw_line_vertical_thick(dst, startPosX, (startPosY > endPosY) ? endPosY : startPosY, absChangeInY, thickness, color);
        return;
    }

    if (startPosY == endPosY) {
        pntr_draw_line_horizontal_thick(dst, (startPosX > endPosX) ? endPosX : startPosX, startPosY, absChangeInX, thickness, color);
        return;
    }

    int startU, startV, endU, stepV;
    int A, B, P;
    int reversedXY = (absChangeInY < absChangeInX);

    if (reversedXY) {
        A = 2 * absChangeInY;
        B = A - 2 * absChangeInX;
        P = A - absChangeInX;

        if (changeInX > 0) {
            startU = startPosX;
            startV = startPosY;
            endU = endPosX;
            //endV = endPosY;
        }
        else {
            startU = endPosX;
            startV = endPosY;
            endU = startPosX;
            //endV = startPosY;

            // Since start and end are reversed
            changeInX = -changeInX;
            changeInY = -changeInY;
        }

        stepV = (changeInY < 0) ? -1 : 1;

        // pntr_draw_point(dst, startU, startV, color);
        pntr_draw_circle_fill(dst, startU, startV, thickness/2, color);
    }
    else {
        A = 2 * absChangeInX;
        B = A - 2 * absChangeInY;
        P = A - absChangeInY;

        if (changeInY > 0) {
            startU = startPosY;
            startV = startPosX;
            endU = endPosY;
        }
        else {
            startU = endPosY;
            startV = endPosX;
            endU = startPosY;

            changeInX = -changeInX;
            changeInY = -changeInY;
        }

        stepV = (changeInX < 0) ? -1 : 1;

        // pntr_draw_point(dst, startV, startU, color);
        pntr_draw_circle_fill(dst, startV, startU, thickness/2, color);

    }

    for (int u = startU + 1, v = startV; u <= endU; u++) {
        if (P >= 0) {
            v += stepV;
            P += B;
        }
        else {
            P += A;
        }

        if (reversedXY) {
            // pntr_draw_point(dst, u, v, color);
            pntr_draw_circle_fill(dst, u, v, thickness/2, color);
        }
        else {
            // pntr_draw_point(dst, v, u, color);
            pntr_draw_circle_fill(dst, v, u, thickness/2, color);
        }
    }
}

PNTR_API void pntr_draw_line_curve(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_vector point4, int segments, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0 || segments <= 0) {
        return;
    }

    float t_step = 1.0f / (float)segments;
    pntr_vector last = point1;
    for (int i_step = 1; i_step <= segments; ++i_step) {
        float t = t_step * (float)i_step;
        float u = 1.0f - t;
        float w1 = u * u * u;
        float w2 = 3 * u * u * t;
        float w3 = 3 * u * t * t;
        float w4 = t * t * t;
        float x = w1 * (float)point1.x + w2 * (float)point2.x + w3 * (float)point3.x + w4 * (float)point4.x;
        float y = w1 * (float)point1.y + w2 * (float)point2.y + w3 * (float)point3.y + w4 * (float)point4.y;
        pntr_draw_line(dst, last.x, last.y, (int)x, (int)y, color);
        last.x = (int)x;
        last.y = (int)y;
    }
}

PNTR_API void pntr_draw_line_curve_thick(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_vector point4, int segments, int thickness, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0 || segments <= 0) {
        return;
    }

    float t_step = 1.0f / (float)segments;
    pntr_vector last = point1;
    for (int i_step = 1; i_step <= segments; ++i_step) {
        float t = t_step * (float)i_step;
        float u = 1.0f - t;
        float w1 = u * u * u;
        float w2 = 3 * u * u * t;
        float w3 = 3 * u * t * t;
        float w4 = t * t * t;
        float x = w1 * (float)point1.x + w2 * (float)point2.x + w3 * (float)point3.x + w4 * (float)point4.x;
        float y = w1 * (float)point1.y + w2 * (float)point2.y + w3 * (float)point3.y + w4 * (float)point4.y;
        pntr_draw_line_thick(dst, last.x, last.y, (int)x, (int)y, thickness, color);
        last.x = (int)x;
        last.y = (int)y;
    }
}

PNTR_API void pntr_draw_polyline(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL || numPoints <= 0 || points == NULL) {
        return;
    }

    if (numPoints == 1) {
        pntr_draw_point_vec(dst, points, color);
        return;
    }

    for (int i = 0; i < numPoints - 1; i++) {
        pntr_draw_line_vec(dst, points[i], points[i + 1], color);
    }
}

PNTR_API void pntr_draw_polyline_thick(pntr_image* dst, pntr_vector* points, int numPoints, int thickness, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL || numPoints <= 0 || points == NULL) {
        return;
    }

    if (numPoints == 1) {
        pntr_draw_point_vec(dst, points, color);
        return;
    }

    for (int i = 0; i < numPoints - 1; i++) {
        pntr_draw_line_thick_vec(dst, points[i], points[i + 1], thickness, color);
    }
}

/**
 * Draw a horizontal line at the given x, y coordinates.
 *
 * @param dst The destination image.
 * @param posX The X position.
 * @param posY The Y position.
 * @param width How long the line should be.
 * @param color The color of the line.
 *
 * TODO: pntr_draw_line_horizontal: Support negative width.
 */
PNTR_API void pntr_draw_line_horizontal(pntr_image* dst, int posX, int posY, int width, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL || posY < dst->clip.y || posY >= dst->clip.y + dst->clip.height || posX >= dst->clip.x + dst->clip.width || posX + width < dst->clip.x) {
        return;
    }

    if (posX < dst->clip.x) {
        width += posX - dst->clip.x;
        posX = dst->clip.x;
    }
    if (posX + width >= dst->clip.x + dst->clip.width) {
        width = dst->clip.x + dst->clip.width - posX;
    }

    if (color.rgba.a == 255) {
        pntr_put_horizontal_line_unsafe(dst, posX, posY, width, color);
    }
    else {
        pntr_color *row = &PNTR_PIXEL(dst, posX, posY);
        while (--width >= 0) {
            pntr_blend_color(row + width, color);
        }
    }
}

PNTR_API void pntr_draw_line_horizontal_thick(pntr_image* dst, int posX, int posY, int width, int thickness, pntr_color color) {
    pntr_draw_rectangle_fill(dst, posX, posY - thickness / 2, width, thickness, color);
    pntr_draw_circle_fill(dst, posX, posY, thickness / 2, color);
    pntr_draw_circle_fill(dst, posX + width, posY, thickness / 2, color);
}

/**
 * Draw a vertical line at the given x, y coordinates.
 *
 * @param dst The destination image.
 * @param posX The X position.
 * @param posY The Y position.
 * @param height How tall the line should be.
 * @param color The color of the line.
 *
 * TODO: pntr_draw_line_vertical: Support negative height.
 */
PNTR_API void pntr_draw_line_vertical(pntr_image* dst, int posX, int posY, int height, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL || posX < dst->clip.x || posX >= dst->clip.x + dst->clip.width || posY >= dst->clip.y + dst->clip.height || posY + height < dst->clip.y) {
        return;
    }

    if (posY < dst->clip.y) {
        height += posY - dst->clip.y;
        posY = dst->clip.y;
    }
    if (posY + height >= dst->clip.y + dst->clip.height) {
        height = dst->clip.y + dst->clip.height - posY;
    }

    if (color.rgba.a == 255) {
        for (int y = 0; y < height; y++) {
            PNTR_PIXEL(dst, posX, posY + y) = color;
        }
    }
    else {
        for (int y = 0; y < height; y++) {
            pntr_blend_color(&PNTR_PIXEL(dst, posX, posY + y), color);
        }
    }
}

PNTR_API void pntr_draw_line_vertical_thick(pntr_image* dst, int posX, int posY, int height, int thickness, pntr_color color) {
    pntr_draw_rectangle_fill(dst, posX - thickness / 2, posY, thickness, height, color);
    pntr_draw_circle_fill(dst, posX, posY, thickness / 2, color);
    pntr_draw_circle_fill(dst, posX, posY + height, thickness / 2, color);
}

/**
 * Draws a rectangle using a rectangle.
 *
 * @param dst Where to draw the rectangle.
 * @param rec The rectangle of which to draw.
 * @param color The color of the lines for the rectangle.
 */
PNTR_API void pntr_draw_rectangle_rec(pntr_image* dst, pntr_rectangle rec, pntr_color color) {
    pntr_draw_rectangle(dst, rec.x, rec.y, rec.width, rec.height, color);
}

/**
 * Draw a rectangle on the given image.
 *
 * @param dst The destination image.
 * @param posX The X position.
 * @param posY The Y position.
 * @param width How wide the rectangle should be.
 * @param height How tall the rectangle should be.
 * @param color The color of the line.
 *
 * @see pntr_draw_rectangle_rec()
 * @see pntr_draw_rectangle_fill()
 */
PNTR_API void pntr_draw_rectangle(pntr_image* dst, int posX, int posY, int width, int height, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL || width <= 0 || height <= 0) {
        return;
    }

    pntr_draw_line_horizontal(dst, posX, posY, width, color);
    pntr_draw_line_horizontal(dst, posX, posY + height - 1, width, color);
    pntr_draw_line_vertical(dst, posX, posY + 1, height - 2, color);
    pntr_draw_line_vertical(dst, posX + width - 1, posY + 1, height - 2, color);
}

PNTR_API void pntr_draw_rectangle_thick(pntr_image* dst, int posX, int posY, int width, int height, int thickness, pntr_color color) {
    for (int i = 0; i < thickness; i++) {
        pntr_draw_rectangle(dst, posX + i, posY + i, width - i * 2, height - i * 2, color);
    }
}

PNTR_API void pntr_draw_rectangle_thick_rec(pntr_image* dst, pntr_rectangle rect, int thickness, pntr_color color) {
    pntr_draw_rectangle_thick(dst, rect.x, rect.y, rect.width, rect.height, thickness, color);
}

/**
 * Draws a filled rectangle on the given image.
 *
 * @param dst The destination image.
 * @param posX The X position.
 * @param posY The Y position.
 * @param width How wide the rectangle should be.
 * @param height How tall the rectangle should be.
 * @param color The color of the rectangle.
 *
 * @see pntr_draw_rectangle()
 */
PNTR_API void pntr_draw_rectangle_fill(pntr_image* dst, int posX, int posY, int width, int height, pntr_color color) {
    pntr_draw_rectangle_fill_rec(dst, PNTR_CLITERAL(pntr_rectangle) { posX, posY, width, height }, color);
}

/**
 * Draws a filled rectangle on the given image, using a rectangle as input data.
 *
 * @param dst The destination image.
 * @param rect The rectangle of which to draw.
 * @param color The color of the rectangle.
 *
 * @see pntr_draw_rectangle_fill()
 */
PNTR_API void pntr_draw_rectangle_fill_rec(pntr_image* dst, pntr_rectangle rect, pntr_color color) {
    if (color.rgba.a == 0 || dst == NULL) {
        return;
    }

    if (!_pntr_rectangle_intersect(rect.x, rect.y, rect.width, rect.height, dst->clip.x, dst->clip.y, dst->clip.width, dst->clip.height, &rect)) {
        return;
    }

    // When the color is solid, we can do some performance improvements.
    if (color.rgba.a == 255) {
        pntr_put_horizontal_line_unsafe(dst, rect.x, rect.y, rect.width, color);

        pntr_color* srcPixel = &PNTR_PIXEL(dst, rect.x, rect.y);
        for (int y = rect.y + 1; y < rect.y + rect.height; y++) {
            PNTR_MEMCPY(&PNTR_PIXEL(dst, rect.x, y), srcPixel, (size_t)rect.width * sizeof(pntr_color));
        }
    }
    else {
        for (int y = 0; y < rect.height; y++) {
            pntr_color* col = &PNTR_PIXEL(dst, rect.x, rect.y + y);
            for (int x = 0; x < rect.width; x++) {
                pntr_blend_color(col++, color);
            }
        }
    }
}

PNTR_API void pntr_draw_rectangle_gradient_rec(pntr_image* dst, pntr_rectangle rect, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight) {
    if (dst == NULL) {
        return;
    }

    pntr_rectangle dstRect;
    if (!_pntr_rectangle_intersect(rect.x, rect.y, rect.width, rect.height, dst->clip.x, dst->clip.y, dst->clip.width, dst->clip.height, &dstRect)) {
        return;
    }

    float width = (float)rect.width;
    float height = (float)rect.height;
    for (int x = dstRect.x; x < dstRect.x + dstRect.width; x++) {
        float factorX = (float)(x - rect.x) / width;
        for (int y = dstRect.y; y < dstRect.y + dstRect.height; y++) {
            pntr_draw_point_unsafe(dst, x, y, pntr_color_bilinear_interpolate(
                topLeft, bottomLeft,
                topRight, bottomRight,
                factorX,
                (float)(y - rect.y) / height
            ));
        }
    }
}

PNTR_API void pntr_draw_rectangle_gradient(pntr_image* dst, int x, int y, int width, int height, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight) {
    pntr_draw_rectangle_gradient_rec(dst, PNTR_CLITERAL(pntr_rectangle) {x, y, width, height}, topLeft, topRight, bottomLeft, bottomRight);
}

/**
 * Draws a circle from the given center, with the given radius.
 *
 * This uses the Midpoint Circle Algorithm:
 *   https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *
 * TODO: pntr_draw_circle: Add anti-aliased, and thickness.
 *
 * @param dst The image to draw the circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radius The radius of the circle.
 * @param color The desired color of the circle.
 *
 * @see pntr_draw_circle_fill()
 */
PNTR_API void pntr_draw_circle(pntr_image* dst, int centerX, int centerY, int radius, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0) {
        return;
    }

    if (radius < 0) {
        radius = -radius;
    }

    // Check that the circle is in the bounds.
    if (centerX + radius < dst->clip.x || centerY + radius < dst->clip.y || centerX - radius > dst->clip.x + dst->clip.width || centerY - radius > dst->clip.y + dst->clip.height) {
        return;
    }

    int largestX = radius;
    int r2 = radius * radius;
    for (int y = 0; y <= radius; ++y) {
        int y2 = y * y;
        for (int x = largestX; x >= 0; --x) {
            if (x * x + y2 <= r2) {
                pntr_draw_point(dst, centerX + x, centerY + y, color);
                pntr_draw_point(dst, centerX - x, centerY + y, color);
                pntr_draw_point(dst, centerX + x, centerY - y, color);
                pntr_draw_point(dst, centerX - x, centerY - y, color);
                pntr_draw_point(dst, centerX + y, centerY + x, color);
                pntr_draw_point(dst, centerX - y, centerY + x, color);
                pntr_draw_point(dst, centerX + y, centerY - x, color);
                pntr_draw_point(dst, centerX - y, centerY - x, color);
                largestX = x;
                break;
            }
        }
    }
}

/**
 * Draws a filled circle on the given image.
 *
 * TODO: pntr_draw_circle_fill: Add anti-aliased.
 *
 * @param dst The image to draw the filled circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radius The radius of the circle.
 * @param color The desired fill color of the circle.
 *
 * @see pntr_draw_circle()
 */
PNTR_API void pntr_draw_circle_fill(pntr_image* dst, int centerX, int centerY, int radius, pntr_color color) {
    if (radius < 0) {
        radius = -radius;
    }

    if (dst == NULL || color.rgba.a == 0 || radius == 0 || centerX + radius < dst->clip.x || centerX - radius >= dst->clip.x + dst->clip.width || centerY + radius < dst->clip.y || centerY - radius >= dst->clip.y + dst->clip.height) {
        return;
    }

    int largestX = radius;
    int r2 = radius * radius;
    for (int y = 0; y <= radius; ++y) {
        int y2 = y * y;
        for (int x = largestX; x >= 0; --x) {
            if (x * x + y2 <= r2) {
                pntr_draw_line_horizontal(dst, centerX - x, centerY + y, x, color);
                pntr_draw_line_horizontal(dst, centerX - x, centerY - y, x, color);
                pntr_draw_line_horizontal(dst, centerX, centerY + y, x, color);
                pntr_draw_line_horizontal(dst, centerX, centerY - y, x, color);
                largestX = x;
                break;
            }
        }
    }
}

/**
 * Draws a circle from the given center, with the given radius & line-thickness.
 *
 * @param dst The image to draw the circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radius The radius of the circle.
 * @param color The desired color of the circle.
 *
 */
PNTR_API void pntr_draw_circle_thick(pntr_image* dst, int centerX, int centerY, int radius, int thickness, pntr_color color) {
    if (thickness < 1) {
        return;
    }
    if (thickness == 1) {
        pntr_draw_circle(dst, centerX, centerY, radius, color);
        return;
    }
    if (dst == NULL || color.rgba.a == 0) {
        return;
    }

    if (radius < 0) {
        radius = -radius;
    }

    // Check that the circle is in the bounds.
    if (centerX + radius < dst->clip.x || centerY + radius < dst->clip.y || centerX - radius > dst->clip.x + dst->clip.width || centerY - radius > dst->clip.y + dst->clip.height) {
        return;
    }

    int largestX = radius;
    int r2 = radius * radius;
    for (int y = 0; y <= radius; ++y) {
        int y2 = y * y;
        for (int x = largestX; x >= 0; --x) {
            if (x * x + y2 <= r2) {
                pntr_draw_circle_fill(dst, centerX + x, centerY + y, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX - x, centerY + y, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX + x, centerY - y, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX - x, centerY - y, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX + y, centerY + x, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX - y, centerY + x, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX + y, centerY - x, thickness/2, color);
                pntr_draw_circle_fill(dst, centerX - y, centerY - x, thickness/2, color);
                largestX = x;
                break;
            }
        }
    }
}

/**
 * Draws an ellipse on the given image.
 *
 * @param dst The image to draw the filled circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radiusX The  horizontal radius of the circle.
 * @param radiusY The vertical radius of the circle.
 * @param color The desired color of the circle.
 *
 * @see pntr_draw_ellipse_fill()
 */
PNTR_API void pntr_draw_ellipse(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, pntr_color color) {
    if (dst == NULL || radiusX == 0 || radiusY == 0 || color.rgba.a == 0) {
        return;
    }

    int x = 0;
    if (radiusX < 0) {
        radiusX = -radiusX;
    }
    if (radiusY < 0) {
        radiusY = -radiusY;
    }

    int radiusXSquared = radiusX * radiusX;
    int radiusXSquared2 = radiusXSquared * 2;
    int radiusYSquared = radiusY * radiusY;
    int radiusYSquared2 = radiusYSquared * 2;
    int error = radiusYSquared - radiusXSquared * radiusY;

    while (radiusY >= 0) {
        pntr_draw_point(dst, centerX + x, centerY + radiusY, color);
        pntr_draw_point(dst, centerX - x, centerY + radiusY, color);
        pntr_draw_point(dst, centerX - x, centerY - radiusY, color);
        pntr_draw_point(dst, centerX + x, centerY - radiusY, color);

        if (error <= 0) {
            x++;
            error += radiusYSquared2 * x + radiusYSquared;
        }
        if (error > 0) {
            radiusY--;
            error -= radiusXSquared2 * radiusY - radiusXSquared;
        }
    }
}

/**
 * Draws a filled ellipse on the given image.
 *
 * TODO: pntr_draw_ellipse_fill: Add anti-aliased
 *
 * @param dst The image to draw the filled circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radiusX The  horizontal radius of the circle.
 * @param radiusY The vertical radius of the circle.
 * @param color The desired fill color of the circle.
 *
 * @see pntr_draw_circle_fill()
 */
PNTR_API void pntr_draw_ellipse_fill(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, pntr_color color) {
    if (radiusX < 0) {
        radiusX = -radiusX;
    }
    if (radiusY < 0) {
        radiusY = -radiusY;
    }

    if (dst == NULL || radiusX == 0 || radiusY == 0 || color.rgba.a == 0 || centerX + radiusX < dst->clip.x || centerX - radiusX > dst->clip.x + dst->clip.width || centerY + radiusY < dst->clip.y || centerY - radiusY > dst->clip.y + dst->clip.height) {
        return;
    }

    int x = 0;
    int radiusXSquared = radiusX * radiusX;
    int radiusXSquared2 = radiusXSquared * 2;
    int radiusYSquared = radiusY * radiusY;
    int radiusYSquared2 = radiusYSquared * 2;
    int error = radiusYSquared - radiusXSquared * radiusY;

    while (radiusY >= 0) {
        pntr_draw_line_horizontal(dst, centerX - x, centerY + radiusY, x, color);
        pntr_draw_line_horizontal(dst, centerX - x, centerY - radiusY, x, color);
        pntr_draw_line_horizontal(dst, centerX, centerY + radiusY, x, color);
        pntr_draw_line_horizontal(dst, centerX, centerY - radiusY, x, color);

        if (error <= 0) {
            x++;
            error += radiusYSquared2 * x + radiusYSquared;
        }
        if (error > 0) {
            radiusY--;
            error -= radiusXSquared2 * radiusY - radiusXSquared;
        }
    }
}

/**
 * Draws an ellipse on the given image, with line-thikness.
 *
 * @param dst The image to draw the filled circle onto.
 * @param centerX The center of the circle at the X coordinate.
 * @param centerX The center of the circle at the Y coordinate.
 * @param radiusX The  horizontal radius of the circle.
 * @param radiusY The vertical radius of the circle.
 * @param thickness The thickness of the line
 * @param color The desired color of the circle.
 *
 */
PNTR_API void pntr_draw_ellipse_thick(pntr_image* dst, int centerX, int centerY, int radiusX, int radiusY, int thickness, pntr_color color) {
    if (thickness < 1) {
        return;
    }
    if (thickness == 1) {
        pntr_draw_ellipse(dst, centerX, centerY, radiusX, radiusY, color);
        return;
    }
    if (dst == NULL || radiusX == 0 || radiusY == 0 || color.rgba.a == 0) {
        return;
    }

    int x = 0;
    if (radiusX < 0) {
        radiusX = -radiusX;
    }
    if (radiusY < 0) {
        radiusY = -radiusY;
    }

    int radiusXSquared = radiusX * radiusX;
    int radiusXSquared2 = radiusXSquared * 2;
    int radiusYSquared = radiusY * radiusY;
    int radiusYSquared2 = radiusYSquared * 2;
    int error = radiusYSquared - radiusXSquared * radiusY;

    while (radiusY >= 0) {
        pntr_draw_circle_fill(dst, centerX + x, centerY + radiusY, thickness/2, color);
        pntr_draw_circle_fill(dst, centerX - x, centerY + radiusY, thickness/2, color);
        pntr_draw_circle_fill(dst, centerX - x, centerY - radiusY, thickness/2, color);
        pntr_draw_circle_fill(dst, centerX + x, centerY - radiusY, thickness/2, color);

        if (error <= 0) {
            x++;
            error += radiusYSquared2 * x + radiusYSquared;
        }
        if (error > 0) {
            radiusY--;
            error -= radiusXSquared2 * radiusY - radiusXSquared;
        }
    }
}

/**
 * Draw a triangle using vectors.
 *
 * @param dst Where to draw the triangle.
 * @param point1 The first point in the triangle.
 * @param point2 The second point in the triangle.
 * @param point3 The third point in the triangle.
 * @param color What color to draw the triangle.
 */
PNTR_API void pntr_draw_triangle_vec(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_color color) {
    pntr_draw_triangle(dst, point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color);
}

/**
 * Draw a triangle using vectors, with line-thickness.
 *
 * @param dst Where to draw the triangle.
 * @param point1 The first point in the triangle.
 * @param point2 The second point in the triangle.
 * @param point3 The third point in the triangle.
 * @param thickness The thickness of the line
 * @param color What color to draw the triangle.
 */
void pntr_draw_triangle_thick_vec(pntr_image *dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, int thickness, pntr_color color) {
    pntr_draw_line_thick(dst, point1.x, point1.y, point2.x, point2.y, thickness, color);
    pntr_draw_line_thick(dst, point2.x, point2.y, point3.x, point3.y, thickness, color);
    pntr_draw_line_thick(dst, point3.x, point3.y, point1.x, point1.y, thickness, color);
}

/**
 * Draw a triangle on an image.
 *
 * @param dst The image of which to draw the triangle.
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param x3 The x coordinate of the third point.
 * @param y3 The y coordinate of the third point.
 * @param color The line color for the triangle.
 */
PNTR_API void pntr_draw_triangle(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, pntr_color color) {
    pntr_draw_line(dst, x1, y1, x2, y2, color);
    pntr_draw_line(dst, x2, y2, x3, y3, color);
    pntr_draw_line(dst, x3, y3, x1, y1, color);
}

/**
 * Draw a triangle on an image, with line-thickness.
 *
 * @param dst The image of which to draw the triangle.
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param x3 The x coordinate of the third point.
 * @param y3 The y coordinate of the third point.
 * @param thickness The thickness of the line
 * @param color The line color for the triangle.
 */
PNTR_API void pntr_draw_triangle_thick(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, int thickness, pntr_color color) {
    pntr_draw_line_thick(dst, x1, y1, x2, y2, thickness, color);
    pntr_draw_line_thick(dst, x2, y2, x3, y3, thickness, color);
    pntr_draw_line_thick(dst, x3, y3, x1, y1, thickness, color);
}


/**
 * Draw a filled triangle on an image.
 *
 * @param dst The image of which to draw the triangle.
 * @param x1 The x coordinate of the first point.
 * @param y1 The y coordinate of the first point.
 * @param x2 The x coordinate of the second point.
 * @param y2 The y coordinate of the second point.
 * @param x3 The x coordinate of the third point.
 * @param y3 The y coordinate of the third point.
 * @param color The fill color of the triangle.
 */
PNTR_API void pntr_draw_triangle_fill(pntr_image* dst, int x1, int y1, int x2, int y2, int x3, int y3, pntr_color color) {
    pntr_draw_triangle_fill_vec(dst,
        PNTR_CLITERAL(pntr_vector) { .x = x1, .y = y1 },
        PNTR_CLITERAL(pntr_vector) { .x = x2, .y = y2 },
        PNTR_CLITERAL(pntr_vector) { .x = x3, .y = y3 },
        color
    );
}

PNTR_API void pntr_draw_line_vec(pntr_image* dst, pntr_vector start, pntr_vector end, pntr_color color) {
    pntr_draw_line(dst, start.x, start.y, end.x, end.y, color);
}

PNTR_API void pntr_draw_line_thick_vec(pntr_image* dst, pntr_vector start, pntr_vector end, int thickness, pntr_color color) {
    pntr_draw_line_thick(dst, start.x, start.y, end.x, end.y, thickness, color);
}

PNTR_API void pntr_draw_polygon(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0 || numPoints <= 0 || points == NULL) {
        return;
    }

    int nextPointIndex;
    for (int i = 0; i < numPoints; i++) {
        if (i < numPoints - 1) {
            nextPointIndex = i + 1;
        }
        else {
            nextPointIndex = 0;
        }

        pntr_draw_line(dst, points[i].x, points[i].y, points[nextPointIndex].x, points[nextPointIndex].y, color);
   }
}

PNTR_API void pntr_draw_polygon_thick(pntr_image* dst, pntr_vector* points, int numPoints, int thickness, pntr_color color) {
    if (dst == NULL || color.rgba.a == 0 || numPoints <= 0 || points == NULL) {
        return;
    }

    int nextPointIndex;
    for (int i = 0; i < numPoints; i++) {
        if (i < numPoints - 1) {
            nextPointIndex = i + 1;
        }
        else {
            nextPointIndex = 0;
        }

        pntr_draw_line_thick(dst, points[i].x, points[i].y, points[nextPointIndex].x, points[nextPointIndex].y, thickness, color);
   }
}

PNTR_API void pntr_draw_polygon_fill(pntr_image* dst, pntr_vector* points, int numPoints, pntr_color color) {
    if (dst == NULL || points == NULL || numPoints <= 0 || color.rgba.a == 0) {
        return;
    }

    int i = 0;
    int left = 10000, top = 10000, bottom = 0, right = 0;
    int nodes, pixelX, pixelY, j, swap;
    int* nodeX = (int*)PNTR_MALLOC(sizeof(int) * (size_t)numPoints);
    if (nodeX == NULL) {
        return;
    }

    /* Get polygon dimensions */
    for (i = 0; i < numPoints; i++) {
        if (left > points[i].x)
            left = points[i].x;
        if (right < points[i].x)
            right = points[i].x;
        if (top > points[i].y)
            top = points[i].y;
        if (bottom < points[i].y)
            bottom = points[i].y;
    }
    bottom++;
    right++;

    // Polygon scanline algorithm released under public-domain by Darel Rex Finley, 2007.
    // Loop through the rows of the image.
    for (pixelY = top; pixelY < bottom; pixelY ++) {
        nodes = 0; /*  Build a list of nodes. */
        j = numPoints - 1;
        for (i = 0; i < numPoints; i++) {
            if (((points[i].y < pixelY) && (points[j].y >= pixelY)) ||
                ((points[j].y < pixelY) && (points[i].y >= pixelY))) {
                nodeX[nodes++]= (int)((float)points[i].x
                     + ((float)pixelY - (float)points[i].y) / ((float)points[j].y - (float)points[i].y)
                     * ((float)points[j].x - (float)points[i].x));
            } j = i;
        }

        // Sort the nodes, via a simple “Bubble” sort.
        i = 0;
        while (i < nodes - 1) {
            if (nodeX[i] > nodeX[i+1]) {
                swap = nodeX[i];
                nodeX[i] = nodeX[i+1];
                nodeX[i+1] = swap;
                if (i) i--;
            } else i++;
        }
        // Fill the pixels between node pairs.
        for (i = 0; i < nodes; i += 2) {
            if (nodeX[i+0] >= right) break;
            if (nodeX[i+1] > left) {
                if (nodeX[i+0] < left) nodeX[i+0] = left ;
                if (nodeX[i+1] > right) nodeX[i+1] = right;
                for (pixelX = nodeX[i]; pixelX < nodeX[i + 1]; pixelX++)
                    pntr_draw_point(dst, pixelX, pixelY, color);
            }
        }
    }

    PNTR_FREE(nodeX);
}

/**
 * Draw a filled triangle using vectors.
 *
 * @param dst Where to draw the triangle.
 * @param point1 The first point in the triangle.
 * @param point2 The second point in the triangle.
 * @param point3 The third point in the triangle.
 * @param color What color to draw the triangle.
 */
PNTR_API void pntr_draw_triangle_fill_vec(pntr_image* dst, pntr_vector point1, pntr_vector point2, pntr_vector point3, pntr_color color) {
    pntr_vector points[3];
    points[0] = point1;
    points[1] = point2;
    points[2] = point3;
    pntr_draw_polygon_fill(dst, points, 3, color);
}

PNTR_API void pntr_draw_arc(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, pntr_color color) {
    if (radius == 0.0f) {
        pntr_draw_point(dst, centerX, centerY, color);
        return;
    }
    if (segments < 0) {
        return;
    }

    float startAngleRad = startAngle * PNTR_PI / 180.0f;
    float endAngleRad = endAngle * PNTR_PI / 180.0f;

    // Calculate how much distance between each segment
    float stepAngle = (endAngleRad - startAngleRad) / (float)(segments);

    // Draw the arc with line segments
    /*
    int x1 = centerX + (int)((float)radius * PNTR_COSF(startAngleRad));
    int y1 = centerY + (int)((float)radius * PNTR_SINF(startAngleRad));
    float angle;
    for (int i = 1; i < segments; i++) {
        angle = startAngleRad + (float)i * stepAngle;
        int x2 = centerX + (int)((float)radius * PNTR_COSF(angle));
        int y2 = centerY + (int)((float)radius * PNTR_SINF(angle));
        pntr_draw_line(dst, x1, y1, x2, y2, color);
        x1 = x2;
        y1 = y2;
    }
    */

    // Draw each line segment
    for (int i = 0; i < segments; i++) {
        endAngleRad = startAngleRad + (float)i * stepAngle;
        pntr_draw_point(dst,
            centerX + (int)(radius * PNTR_COSF(endAngleRad)), // TODO: arc angle: Is the - correct here?
            centerY + (int)(radius * PNTR_SINF(endAngleRad)),
            color);
    }
}

PNTR_API void pntr_draw_arc_thick(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, int thickness, pntr_color color) {
    if (radius == 0.0f) {
        pntr_draw_point(dst, centerX, centerY, color);
        return;
    }
    if (segments < 0) {
        return;
    }

    float startAngleRad = startAngle * PNTR_PI / 180.0f;
    float endAngleRad = endAngle * PNTR_PI / 180.0f;

    // Calculate how much distance between each segment
    float stepAngle = (endAngleRad - startAngleRad) / (float)(segments);

    // Draw the arc with line segments
    int x1 = centerX + (int)((float)radius * PNTR_COSF(startAngleRad));
    int y1 = centerY + (int)((float)radius * PNTR_SINF(startAngleRad));
    float angle;
    for (int i = 1; i < segments; i++) {
        angle = startAngleRad + (float)i * stepAngle;
        int x2 = centerX + (int)((float)radius * PNTR_COSF(angle));
        int y2 = centerY + (int)((float)radius * PNTR_SINF(angle));
        pntr_draw_line_thick(dst, x1, y1, x2, y2, thickness, color);
        x1 = x2;
        y1 = y2;
    }
}

PNTR_API void pntr_draw_arc_fill(pntr_image* dst, int centerX, int centerY, float radius, float startAngle, float endAngle, int segments, pntr_color color) {
    if (radius <= 0.0f) {
        pntr_draw_point(dst, centerX, centerY, color);
        return;
    }
    if (segments < 0) {
        return;
    }
    float startAngleRad = startAngle * PNTR_PI / 180.0f;
    float endAngleRad = endAngle * PNTR_PI / 180.0f;

    // Calculate how much distance between each segment
    float stepAngle = (endAngleRad - startAngleRad) / (float)segments;
    pntr_vector* points = (pntr_vector*)PNTR_MALLOC(sizeof(pntr_vector) * (size_t)segments + (size_t)1);

    // TODO: pntr_draw_arc_fill(): Is pntr_draw_polygon_fill ample here?
    for (int i = 0; i < segments; i++) {
        endAngleRad = startAngleRad + (float)i * stepAngle;
        points[i].x = centerX + (int)(radius * PNTR_COSF(endAngleRad));
        points[i].y = centerY + (int)(radius * PNTR_SINF(endAngleRad));
    }

    points[segments].x = centerX;
    points[segments].y = centerY;

    pntr_draw_polygon_fill(dst, points, segments + 1, color);
    pntr_unload_memory((void*)points);
}

PNTR_API void pntr_draw_rectangle_rounded(pntr_image* dst, int x, int y, int width, int height, int topLeftRadius, int topRightRadius, int bottomLeftRadius, int bottomRightRadius, pntr_color color) {
    pntr_draw_line_horizontal(dst, x + topLeftRadius, y, width - topLeftRadius - topRightRadius, color); // Top
    pntr_draw_line_horizontal(dst, x + bottomLeftRadius, y + height, width - bottomLeftRadius - bottomRightRadius - 1, color); // Bottom
    pntr_draw_line_vertical(dst, x, y + topLeftRadius, height - topLeftRadius - bottomLeftRadius, color); // Left
    pntr_draw_line_vertical(dst, x + width - 1, y + topRightRadius, height - topRightRadius - bottomRightRadius, color); // Right

    // TODO: pntr_draw_rectangle_rounded(): Do the angles here make sense?
    pntr_draw_arc(dst, x + topLeftRadius, y + topLeftRadius, (float)topLeftRadius, 180.0f, 270.0f, topLeftRadius * 2, color); // Top Left
    pntr_draw_arc(dst, x + width - topRightRadius - 1, y + topRightRadius, (float)topRightRadius, 0.0f, -90.0f, topRightRadius * 2, color); // Top Right
    pntr_draw_arc(dst, x + bottomLeftRadius, y + height - bottomLeftRadius, (float)bottomLeftRadius, -180.0f, -270.0f, bottomLeftRadius * 2, color); // Bottom Left
    pntr_draw_arc(dst, x + width - bottomRightRadius - 1, y + height - bottomRightRadius, (float)bottomRightRadius, 0.0f, 90.0f, bottomRightRadius * 2, color); // Bottom Right
}

PNTR_API void pntr_draw_rectangle_thick_rounded(pntr_image* dst, int x, int y, int width, int height, int topLeftRadius, int topRightRadius, int bottomLeftRadius, int bottomRightRadius, int thickness, pntr_color color) {
    if (thickness < 1) {
        return;
    }
    if (thickness == 1) {
        pntr_draw_rectangle_rounded(dst, x, y, width, height, topLeftRadius, topRightRadius, bottomLeftRadius, bottomRightRadius, color);
        return;
    }
    for (int offset = 0; offset < thickness; offset++ ) {
        pntr_draw_line_horizontal(dst, x + topLeftRadius - offset, y - offset, width - topLeftRadius - topRightRadius - offset, color); // Top
        pntr_draw_line_horizontal(dst, x + bottomLeftRadius - offset, y + height - offset, width - bottomLeftRadius - bottomRightRadius - 1 - offset, color); // Bottom
        pntr_draw_line_vertical(dst, x - offset, y + topLeftRadius - offset, height - topLeftRadius - bottomLeftRadius - offset, color); // Left
        pntr_draw_line_vertical(dst, x + width - 1 - offset, y + topRightRadius - offset, height - topRightRadius - bottomRightRadius - offset, color); // Right
    }
    pntr_draw_arc_thick(dst, x + topLeftRadius, y + topLeftRadius, (float)topLeftRadius, 180.0f, 270.0f, topLeftRadius * 2, thickness, color); // Top Left
    pntr_draw_arc_thick(dst, x + width - topRightRadius - 1, y + topRightRadius, (float)topRightRadius, 0.0f, -90.0f, topRightRadius * 2, thickness, color); // Top Right
    pntr_draw_arc_thick(dst, x + bottomLeftRadius, y + height - bottomLeftRadius, (float)bottomLeftRadius, -180.0f, -270.0f, bottomLeftRadius * 2, thickness, color); // Bottom Left
    pntr_draw_arc_thick(dst, x + width - bottomRightRadius - 1, y + height - bottomRightRadius, (float)bottomRightRadius, 0.0f, 90.0f, bottomRightRadius * 2, thickness, color); // Bottom Right
}

PNTR_API void pntr_draw_rectangle_rounded_fill(pntr_image* dst, int x, int y, int width, int height, int cornerRadius, pntr_color color) {
    // Corners
    // TODO: Replace this with pntr_draw_arc_fill()
    pntr_draw_circle_fill(dst, x + cornerRadius, y + cornerRadius, cornerRadius, color); // Top Left
    pntr_draw_circle_fill(dst, x + width - cornerRadius - 1, y + cornerRadius, cornerRadius, color); // Top Right
    pntr_draw_circle_fill(dst, x + cornerRadius, y + height - cornerRadius, cornerRadius, color); // Bottom Left
    pntr_draw_circle_fill(dst, x + width - cornerRadius - 1, y + height - cornerRadius, cornerRadius, color); // Bottom Right

    // Edge bars
    pntr_draw_rectangle_fill(dst, x, y + cornerRadius, cornerRadius, height - cornerRadius * 2, color); // Left bar
    pntr_draw_rectangle_fill(dst, x + width - cornerRadius - 1, y + cornerRadius, cornerRadius, height - cornerRadius * 2, color); // Right bar
    pntr_draw_rectangle_fill(dst, x + cornerRadius, y, width - cornerRadius * 2, cornerRadius, color); // Top bar
    pntr_draw_rectangle_fill(dst, x + cornerRadius, y + height - cornerRadius, width - cornerRadius * 2, cornerRadius, color); // Bottom bar

    // Center fill
    pntr_draw_rectangle_fill(dst, x + cornerRadius, y + cornerRadius, width - cornerRadius * 2, height - cornerRadius * 2, color);
}

/**
 * Get image pixel color at (x, y) position.
 *
 * @param image The image to get the color from.
 * @param x The x position of the pixel.
 * @param y The y position of the pixel.
 *
 * @return The color at (x, y) position from the image.
 */
PNTR_API pntr_color pntr_image_get_color(pntr_image* image, int x, int y) {
    if (image == NULL || x < 0 || y < 0 || x >= image->width || y >= image->height) {
        return PNTR_BLANK;
    }

    return PNTR_PIXEL(image, x, y);
}

/**
 * Get the file type of the given image, based on its filename.
 *
 * @param filePath The file path to the image.
 *
 * @return The type of the image, based on its file extension, or `PNTR_IMAGE_TYPE_UNKNOWN` if it's unknown.
 *
 * @see PNTR_IMAGE_TYPE_UNKNOWN
 * @see PNTR_IMAGE_TYPE_PNG
 * @see PNTR_IMAGE_TYPE_BMP
 * @see PNTR_IMAGE_TYPE_JPG
 */
PNTR_API pntr_image_type pntr_get_file_image_type(const char* filePath) {
    if (filePath == NULL) {
        return PNTR_IMAGE_TYPE_UNKNOWN;
    }

    if (PNTR_STRSTR(filePath, ".png") != NULL || PNTR_STRSTR(filePath, ".PNG") != NULL) {
        return PNTR_IMAGE_TYPE_PNG;
    }

    if (PNTR_STRSTR(filePath, ".bmp") != NULL || PNTR_STRSTR(filePath, ".BMP") != NULL) {
        return PNTR_IMAGE_TYPE_BMP;
    }

    if (PNTR_STRSTR(filePath, ".jpg") != NULL || PNTR_STRSTR(filePath, ".jpeg") != NULL || PNTR_STRSTR(filePath, ".JPG") != NULL || PNTR_STRSTR(filePath, ".JPEG") != NULL) {
        return PNTR_IMAGE_TYPE_JPG;
    }

    return PNTR_IMAGE_TYPE_UNKNOWN;
}

// Load stb_image or cute_png.
#ifndef PNTR_LOAD_IMAGE_FROM_MEMORY
    #ifdef PNTR_STB_IMAGE
        #include "extensions/pntr_stb_image.h"
    #elif defined(PNTR_CUTE_PNG)
        #include "extensions/pntr_cute_png.h"
    #else
        // Allow disabling image loading.
        #ifdef PNTR_NO_LOAD_IMAGE
            #define PNTR_LOAD_IMAGE_FROM_MEMORY(type, fileData, dataSize) NULL
        #else
            // Default to stb_image.
            #include "extensions/pntr_stb_image.h"
        #endif
    #endif
#endif

#ifndef PNTR_SAVE_IMAGE_TO_MEMORY
    #ifdef PNTR_STB_IMAGE
        #include "extensions/pntr_stb_image_write.h"
    #elif defined(PNTR_CUTE_PNG)
        #include "extensions/pntr_cute_png.h"
    #else
        // Allow disabling image saving.
        #ifdef PNTR_NO_SAVE_IMAGE
            #define PNTR_SAVE_IMAGE_TO_MEMORY(image, type, dataSize) NULL
        #else
            // Default to stb_image_write.
            #include "extensions/pntr_stb_image_write.h"
        #endif
    #endif
#endif

/**
 * Load an image from memory buffer.
 *
 * @note This can be overloaded by defining \c PNTR_LOAD_IMAGE_FROM_MEMORY .
 *
 * @param type The type of image to load.
 * @param fileData The data of the file to be loaded.
 * @param dataSize The size of the file data.
 *
 * @return A newly loaded image, or NULL on failure.
 *
 * @see PNTR_LOAD_IMAGE_FROM_MEMORY
 * @see PNTR_NO_LOAD_IMAGE
 */
PNTR_API pntr_image* pntr_load_image_from_memory(pntr_image_type type, const unsigned char *fileData, unsigned int dataSize) {
    if (fileData == NULL || dataSize == 0) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    return PNTR_LOAD_IMAGE_FROM_MEMORY(type, fileData, dataSize);
}

/**
 * Load an image from file.
 *
 * @param fileName The name of the file to load from the file system.
 *
 * @return The newly loaded file.
 *
 * @see PNTR_NO_LOAD_IMAGE
 */
PNTR_API pntr_image* pntr_load_image(const char* fileName) {
    if (fileName == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    unsigned int bytesRead;
    const unsigned char* fileData = pntr_load_file(fileName, &bytesRead);
    if (fileData == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
    }

    pntr_image_type type = pntr_get_file_image_type(fileName);
    pntr_image* output = pntr_load_image_from_memory(type, fileData, bytesRead);
    pntr_unload_file((unsigned char*)fileData);

    return output;
}

/**
 * Draw an image onto the destination image, with tint.
 *
 * @param dst The destination image where the source image will be drawn.
 * @param src The source image to be drawn.
 * @param posX The x-coordinate of the position where the source image will be drawn.
 * @param posY The y-coordinate of the position where the source image will be drawn.
 * @param tint The color to tint the image when drawing.
 */
PNTR_API void pntr_draw_image_tint(pntr_image* dst, pntr_image* src, int posX, int posY, pntr_color tint) {
    if (src == NULL) {
        return;
    }
    pntr_draw_image_tint_rec(dst, src,
        PNTR_CLITERAL(pntr_rectangle) { 0, 0, src->width, src->height },
        posX, posY, tint
    );
}

/**
 * Draw an image onto a destination image.
 *
 * @param dst The destination image where the source image will be drawn.
 * @param src The source image to be drawn.
 * @param posX The x-coordinate of the position where the source image will be drawn.
 * @param posY The y-coordinate of the position where the source image will be drawn.
 */
PNTR_API void pntr_draw_image(pntr_image* dst, pntr_image* src, int posX, int posY) {
    if (src == NULL) {
        return;
    }
    pntr_draw_image_tint_rec(dst, src,
        PNTR_CLITERAL(pntr_rectangle) { 0, 0, src->width, src->height },
        posX, posY, PNTR_WHITE);
}

/**
 * Get source alpha-blended into destination color.
 *
 * @param dst The destination color.
 * @param src The source color.
 *
 * @return The new alpha-blended color.
 *
 * @see PNTR_NO_ALPHABLEND
 */
PNTR_API pntr_color pntr_color_alpha_blend(pntr_color dst, pntr_color src) {
    pntr_blend_color(&dst, src);
    return dst;
}

/**
 * Draw a source image within a destination image.
 *
 * @param dst The destination image.
 * @param src The source image.
 * @param srcRect The source rectangle of what to draw from the source image.
 * @param posX Where to draw the image on the x coordinate.
 * @param posY Where to draw the image on the y coordinate.
 *
 * @see pntr_draw_image()
 */
PNTR_API void pntr_draw_image_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY) {
    pntr_draw_image_tint_rec(dst, src, srcRect, posX, posY, PNTR_WHITE);
}

/**
 * Draw a source image within a destination image, with tint.
 *
 * @param dst The destination image.
 * @param src The source image.
 * @param srcRect The source rectangle of what to draw from the source image.
 * @param posX Where to draw the image on the x coordinate.
 * @param posY Where to draw the image on the y coordinate.
 * @param tint The color to tint the image when drawing.
 *
 * @see pntr_draw_image()
 */
PNTR_API void pntr_draw_image_tint_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, pntr_color tint) {
    if (dst == NULL || src == NULL || posX >= dst->clip.x + dst->clip.width || posY >= dst->clip.y + dst->clip.height) {
        return;
    }

    // Make sure the source rectangle is within bounds.
    if (!_pntr_rectangle_intersect(srcRect.x, srcRect.y,
            srcRect.width <= 0 ? src->width : srcRect.width,
            srcRect.height <= 0 ? src->height : srcRect.height,
            0, 0,
            src->width, src->height, &srcRect)) {
        return;
    }

    // Update the source coordinates based on the destination
    if (posX < dst->clip.x) {
        srcRect.x -= posX - dst->clip.x;
        srcRect.width += posX - dst->clip.x;
        posX = dst->clip.x;
    }
    if (posY < dst->clip.y) {
        srcRect.y -= posY - dst->clip.y;
        srcRect.height += posY - dst->clip.y;
        posY = dst->clip.y;
    }

    // Confine the destination.
    pntr_rectangle dstRect = PNTR_CLITERAL(pntr_rectangle) { posX, posY, srcRect.width, srcRect.height };
    if (!_pntr_rectangle_intersect(dstRect.x, dstRect.y,
            srcRect.width,
            srcRect.height,
            dst->clip.x, dst->clip.y,
            dst->clip.width, dst->clip.height, &dstRect)) {
        return;
    }

    // Determine how many bits to skip for each line.
    int dst_skip = dst->pitch >> 2;
    int src_skip = src->pitch >> 2;

    // Find the first pixel to render.
    pntr_color *dstPixel = dst->data + dst_skip * dstRect.y + dstRect.x;
    pntr_color *srcPixel = src->data + src_skip * srcRect.y + srcRect.x;

    if (tint.value == PNTR_WHITE_VALUE) {
        while (dstRect.height-- > 0) {
            for (int x = 0; x < dstRect.width; ++x) {
                pntr_blend_color(dstPixel + x, srcPixel[x]);
            }

            dstPixel += dst_skip;
            srcPixel += src_skip;
        }
    }
    else {
        while (dstRect.height-- > 0) {
            for (int x = 0; x < dstRect.width; ++x) {
                pntr_blend_color(dstPixel + x, pntr_color_tint(srcPixel[x], tint));
            }

            dstPixel += dst_skip;
            srcPixel += src_skip;
        }
    }
}

/**
 * Creates a new image based on the given image data, from the given original pixel format.
 *
 * This will not clear the original imageData.
 *
 * @param imageData The data of the image in memory.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param pixelFormat The pixel format of the image in memory.
 *
 * @return A new image built from the given image data.
 */
PNTR_API pntr_image* pntr_image_from_pixelformat(const void* imageData, int width, int height, pntr_pixelformat pixelFormat) {
    if (imageData == NULL || width <= 0 || height <= 0 || pixelFormat < 0) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Check how we are to convert the pixel format.
    switch (pixelFormat) {
        case PNTR_PIXELFORMAT_GRAYSCALE: {
            pntr_image* output = pntr_new_image(width, height);
            if (output == NULL) {
                return NULL;
            }

            unsigned char* source = (unsigned char*)imageData;
            for (int i = 0; i < width * height; i++) {
                output->data[i] = pntr_get_pixel_color((void*)(source + i), pixelFormat);
            }

            return output;
        }

        case PNTR_PIXELFORMAT_ARGB8888:
        case PNTR_PIXELFORMAT_RGBA8888: {
            pntr_image* output = pntr_new_image(width, height);

            pntr_color* source = (pntr_color*)imageData;
            for (int i = 0; i < width * height; i++) {
                output->data[i] = pntr_get_pixel_color((void*)(source + i), pixelFormat);
            }

            return output;
        }

        default: {
            return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
        }
    }
}

/**
 * Scales an image either up or down.
 *
 * @param image The image to scale up or down.
 * @param scaleX The scale of which to apply to the width of the image.
 * @param scaleY The scale of which to apply to the height of the image.
 * @param filter The filter to apply when resizing.
 *
 * @return The newly scaled image.
 *
 * @see pntr_image_resize()
 */
PNTR_API pntr_image* pntr_image_scale(pntr_image* image, float scaleX, float scaleY, pntr_filter filter) {
    if (image == NULL || scaleX <= 0.0f || scaleY <= 0.0f) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    return pntr_image_resize(image, (int)((float)image->width * scaleX), (int)((float)image->height * scaleY), filter);
}

/**
 * Resize an image.
 *
 * @param image The image to resize.
 * @param newWidth The desired width of the new image.
 * @param newHeight THe desired height of the new image.
 * @param filter Which filter to apply when resizing.
 *
 * @return The newly resized image.
 *
 * @see pntr_image_scale()
 */
PNTR_API pntr_image* pntr_image_resize(pntr_image* image, int newWidth, int newHeight, pntr_filter filter) {
    if (image == NULL || newWidth <= 0 || newHeight <= 0 || filter < 0) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* output = pntr_new_image(newWidth, newHeight);
    if (output == NULL) {
        return NULL;
    }

    switch (filter) {
        case PNTR_FILTER_BILINEAR: {
            float xRatio = (float)image->width / (float)newWidth;
            float yRatio = (float)image->height / (float)newHeight;

            for (int y = 0; y < newHeight; y++) {
                float srcY = (float)y * yRatio;
                int srcYPixel = (int)srcY;
                int srcYPixelPlusOne = y == newHeight - 1 ? (int)srcY : (int)srcY + 1;
                for (int x = 0; x < newWidth; x++) {
                    float srcX = (float)x * xRatio;
                    int srcXPixel = (int)srcX;
                    int srcXPixelPlusOne = x == newWidth - 1 ? (int)srcX : (int)srcX + 1;
                    PNTR_PIXEL(output, x, y) = pntr_color_bilinear_interpolate(
                        image->data[srcYPixel * (image->pitch >> 2) + srcXPixel],
                        image->data[srcYPixelPlusOne * (image->pitch >> 2) + srcXPixel],
                        image->data[srcYPixel * (image->pitch >> 2) + srcXPixelPlusOne],
                        image->data[srcYPixelPlusOne * (image->pitch >> 2) + srcXPixelPlusOne],
                        srcX - PNTR_FLOORF(srcX),
                        srcY - PNTR_FLOORF(srcY)
                    );
                }
            }
        }
        break;
        case PNTR_FILTER_NEARESTNEIGHBOR:
        default: {
            int xRatio = (image->width << 16) / newWidth + 1;
            int yRatio = (image->height << 16) / newHeight + 1;

            for (int y = 0; y < newHeight; y++) {
                int y2 = (y * yRatio) >> 16;
                for (int x = 0; x < newWidth; x++) {
                    PNTR_PIXEL(output, x, y) = PNTR_PIXEL(image, (x * xRatio) >> 16, y2);
                }
            }
        }
        break;
    }

    // TODO: Copy the clip values scaled from the original image?

    return output;
}

/**
 * Flip an image, vertically, or horizontally, or both.
 *
 * @param image The image to flip.
 * @param horizontal Whether or not to flip the image horizontally.
 * @param vertical Whether or not to flip the image vertically.
 *
 * @see pntr_image_flip()
 */
PNTR_API void pntr_image_flip(pntr_image* image, bool horizontal, bool vertical) {
    if (image == NULL) {
        return;
    }

    pntr_color swap;
    if (vertical) {
        for (int y = 0; y < image->height / 2; y++) {
            for (int x = 0; x < image->width; x++) {
                swap = PNTR_PIXEL(image, x, y);
                PNTR_PIXEL(image, x, y) = PNTR_PIXEL(image, x, image->height - 1 - y);
                PNTR_PIXEL(image, x, image->height - 1 - y) = swap;
            }
        }
    }

    if (horizontal) {
        for (int y = 0; y < image->height; y++) {
            for (int x = 0; x < image->width / 2; x++) {
                swap = PNTR_PIXEL(image, x, y);
                PNTR_PIXEL(image, x, y) = PNTR_PIXEL(image, image->width - 1 - x, y);
                PNTR_PIXEL(image, image->width - 1 - x, y) = swap;
            }
        }
    }
}

/**
 * Replace the given color with another color on an image.
 *
 * @param image The image to process.
 * @param color The color to search for.
 * @param replace The color that will replace the original color.
 */
PNTR_API void pntr_image_color_replace(pntr_image* image, pntr_color color, pntr_color replace) {
    if (image == NULL) {
        return;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, 0, y);
        for (int x = image->clip.x; x < image->clip.x + image->clip.width; x++) {
            if (pixel->value == color.value) {
                *pixel = replace;
            }
            pixel++;
        }
    }
}

/**
 * Tints the given color by another color.
 *
 * @param color The source color to apply the tint to.
 * @param tint The tint color.
 *
 * @return The newly tinted color.
 *
 * @see pntr_image_color_tint()
 */
PNTR_API pntr_color pntr_color_tint(pntr_color color, pntr_color tint) {
    if (tint.value == PNTR_WHITE_VALUE) {
        return color;
    }

    return PNTR_NEW_COLOR(
        (unsigned char)(((float)color.rgba.r / 255.0f * (float)tint.rgba.r / 255.0f) * 255.0f),
        (unsigned char)(((float)color.rgba.g / 255.0f * (float)tint.rgba.g / 255.0f) * 255.0f),
        (unsigned char)(((float)color.rgba.b / 255.0f * (float)tint.rgba.b / 255.0f) * 255.0f),
        (unsigned char)(((float)color.rgba.a / 255.0f * (float)tint.rgba.a / 255.0f) * 255.0f)
    );
}

/**
 * Change brightness of the given color by a factor from -1.0f to 1.0f.
 *
 * @param color The color to change the brightness of.
 * @param factor The factor in which to change the brightness from -1.0f to 1.0f.
 *
 * @see pntr_image_color_brightness()
 */
PNTR_API pntr_color pntr_color_brightness(pntr_color color, float factor) {
    if (factor < -1.0f) {
        factor = -1.0f;
    }
    else if (factor > 1.0f) {
        factor = 1.0f;
    }

    if (factor < 0.0f) {
        factor = 1.0f + factor;
        color.rgba.r = (unsigned char)((float)color.rgba.r * factor);
        color.rgba.g = (unsigned char)((float)color.rgba.g * factor);
        color.rgba.b = (unsigned char)((float)color.rgba.b * factor);
    }
    else {
        color.rgba.r = (unsigned char)(((float)(255 - color.rgba.r) * factor) + color.rgba.r);
        color.rgba.g = (unsigned char)(((float)(255 - color.rgba.g) * factor) + color.rgba.g);
        color.rgba.b = (unsigned char)(((float)(255 - color.rgba.b) * factor) + color.rgba.b);
    }

    return color;
}

/**
 * Fades the given color by a factor from -1.0f to 1.0f.
 *
 * @param color The color that you would like to fade.
 * @param factor The factor of which to fade the color, from -1.0f to 1.0f.
 *
 * @return The faded new color.
 *
 * @see pntr_image_color_fade()
 */
PNTR_API pntr_color pntr_color_fade(pntr_color color, float factor) {
    if (factor < -1.0f) {
        factor = -1.0f;
    }
    else if (factor > 1.0f) {
        factor = 1.0f;
    }

    if (factor < 0.0f) {
        color.rgba.a = (unsigned char)((float)color.rgba.a * (1.0f + factor));
    }
    else {
        color.rgba.a = (unsigned char)(((float)(255 - color.rgba.a) * factor) + color.rgba.a);
    }

    return color;
}

/**
 * Fade an image by the given factor.
 *
 * @param image The image to fade.
 * @param factor The factor of which to fade the image, from -1.0f to 1.0f.
 *
 * @see pntr_color_fade()
 */
PNTR_API void pntr_image_color_fade(pntr_image* image, float factor) {
    if (image == NULL) {
        return;
    }

    if (factor < -1.0f) {
        factor = -1.0f;
    }
    else if (factor > 1.0f) {
        factor = 1.0f;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, image->clip.x, y);
        for (int x = 0; x < image->clip.width; x++) {
            if (pixel->rgba.a > 0) {
                *pixel = pntr_color_fade(*pixel, factor);
            }
            pixel++;
        }
    }
}

/**
 * Set the pixel color of the given pixel color pointer.
 *
 * @param dstPtr A pointer to the pixel in memory.
 * @param dstPixelFormat The desired destination pixel format.
 * @param color The color to apply.
 */
PNTR_API void pntr_set_pixel_color(void* dstPtr, pntr_pixelformat dstPixelFormat, pntr_color color) {
    if (PNTR_PIXELFORMAT == dstPixelFormat) {
        *((pntr_color*)dstPtr) = color;
        return;
    }

    switch (dstPixelFormat) {
        case PNTR_PIXELFORMAT_RGBA8888:
            *((uint32_t*)(dstPtr)) = ((uint32_t)color.rgba.a << 24) | ((uint32_t)color.rgba.b << 16) | ((uint32_t)color.rgba.g << 8) | (uint32_t)color.rgba.r;
        break;
        case PNTR_PIXELFORMAT_ARGB8888:
            *((uint32_t*)(dstPtr)) = ((uint32_t)color.rgba.b << 24) | ((uint32_t)color.rgba.g << 16) | ((uint32_t)color.rgba.r << 8) | (uint32_t)color.rgba.a;
        break;
        case PNTR_PIXELFORMAT_GRAYSCALE: {
            float r = (float)color.rgba.r / 255.0f;
            float g = (float)color.rgba.g / 255.0f;
            float b = (float)color.rgba.b / 255.0f;
            ((unsigned char *)dstPtr)[0] = (unsigned char)((r * 0.299f + g * 0.587f + b * 0.114f) * 255.0f);
        }
        break;
    }
}

/**
 * Gets the pixel color of the given pointer.
 *
 * @param srcPtr A pointer to the given source data.
 * @param srcPixelFormat The pixel format of the given source color.
 *
 * @return The color of the pixel in memory.
 */
PNTR_API pntr_color pntr_get_pixel_color(void* srcPtr, pntr_pixelformat srcPixelFormat) {
    switch (srcPixelFormat) {
        case PNTR_PIXELFORMAT_RGBA8888:
            return PNTR_NEW_COLOR(
                ((unsigned char *)srcPtr)[0],
                ((unsigned char *)srcPtr)[1],
                ((unsigned char *)srcPtr)[2],
                ((unsigned char *)srcPtr)[3]
            );
        case PNTR_PIXELFORMAT_ARGB8888:
            return PNTR_NEW_COLOR(
                ((unsigned char *)srcPtr)[1],
                ((unsigned char *)srcPtr)[2],
                ((unsigned char *)srcPtr)[3],
                ((unsigned char *)srcPtr)[0]
            );
        case PNTR_PIXELFORMAT_GRAYSCALE:
            // White, with alpha determining grayscale value. Use tint to change color afterwards.
            return PNTR_NEW_COLOR(255, 255, 255, ((unsigned char*)srcPtr)[0]);
    }

    return PNTR_BLANK;
}

/**
 * Tints the given image by the provided color.
 *
 * @param image The image to tint.
 * @param tint The color of which to tint the image by.
 *
 * @see pntr_color_tint()
 */
PNTR_API void pntr_image_color_tint(pntr_image* image, pntr_color tint) {
    if (image == NULL) {
        return;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, image->clip.x, y);
        for (int x = 0; x < image->clip.width; x++) {
            *pixel = pntr_color_tint(*pixel, tint);
            pixel++;
        }
    }
}

/**
 * Load a BMFont from the file system.
 *
 * @param fileName The name of the image file to load as the bmfont.
 * @param characters A string representing the characters to load from the atlas.
 *
 * @return The newly loaded font.
 *
 * @see examples/resources/bmfont.png
 */
PNTR_API pntr_font* pntr_load_font_bmf(const char* fileName, const char* characters) {
    pntr_image* image = pntr_load_image(fileName);
    if (image == NULL) {
        return NULL;
    }

    return pntr_load_font_bmf_from_image(image, characters);
}

/**
 * Load a BMFont from the given image data in memory.
 *
 * @param fileData A representation of the image data in memory.
 * @param dataSize The size of the image data.
 * @param characters A string representing the characters to load from the atlas.
 *
 * @return The newly loaded font, or NULL on failure.
 */
PNTR_API pntr_font* pntr_load_font_bmf_from_memory(const unsigned char* fileData, unsigned int dataSize, const char* characters) {
    if (fileData == NULL || dataSize == 0 || characters == NULL) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* image = pntr_load_image_from_memory(PNTR_IMAGE_TYPE_PNG, fileData, dataSize);
    if (image == NULL) {
        return NULL;
    }

    return pntr_load_font_bmf_from_image(image, characters);
}

/**
 * Creates a new pntr_font object, with the number of allocated characters, using the given image.
 *
 * @param numCharacters The amount of glyphs to prepare within the font.
 * @param characterByteSize The amount of bytes required to store the characters. If in ASCII, this is numCharacters.
 * @param atlas A pre-created image for the glyph atlas.
 *
 * @return The new font object allocated in memory.
 *
 * @internal
 */
PNTR_API pntr_font* _pntr_new_font(int numCharacters, size_t characterByteSize, pntr_image* atlas) {
    if (numCharacters <= 0) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Create the new font
    pntr_font* font = (pntr_font*)PNTR_MALLOC(sizeof(pntr_font));
    if (font == NULL) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    // Source Rectangles
    font->srcRects = (pntr_rectangle*)PNTR_MALLOC(sizeof(pntr_rectangle) * (size_t)numCharacters);
    if (font->srcRects == NULL) {
        PNTR_FREE(font);
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    // Glyph Rectangles
    font->glyphRects = (pntr_rectangle*)PNTR_MALLOC(sizeof(pntr_rectangle) * (size_t)numCharacters);
    if (font->glyphRects == NULL) {
        PNTR_FREE(font->srcRects);
        PNTR_FREE(font);
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    // Characters
    font->characters = (char*)PNTR_MALLOC(characterByteSize);
    if (font->characters == NULL) {
        PNTR_FREE(font->srcRects);
        PNTR_FREE(font->glyphRects);
        PNTR_FREE(font);
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    font->characters[0] = '\0';
    font->charactersLen = numCharacters;
    font->atlas = atlas;

    return font;
}

/**
 * Load a BMFont from the given image.
 *
 * @param image The BMFont image.
 * @param characters A string representing the characters to load from the atlas.
 *
 * @return The newly loaded font, or NULL on failure.
 */
PNTR_API pntr_font* pntr_load_font_bmf_from_image(pntr_image* image, const char* characters) {
    if (image == NULL || characters == NULL) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Set up the initial font data.
    size_t charactersSize = PNTR_STRSIZE(characters);
    pntr_color seperator = pntr_image_get_color(image, 0, 0);
    pntr_rectangle currentRectangle = PNTR_CLITERAL(pntr_rectangle) {1, 0, 0, image->height};

    // Find out how many characters there are.
    int numCharacters = 0;
    for (int i = 0; i < image->width; i++) {
        if (pntr_image_get_color(image, i, 0).value == seperator.value) {
            numCharacters++;
        }
    }

    // Build the font.
    pntr_font* font = _pntr_new_font(numCharacters, charactersSize, image);
    if (font == NULL) {
        return NULL;
    }

    // Set up the data structures.
    // TODO: Allow loading BMFont characters vertically
    int currentCharacter = 0;
    for (int i = 1; i < image->width; i++) {
        if (pntr_image_get_color(image, i, 0).value == seperator.value) {
            font->srcRects[currentCharacter] = currentRectangle;
            font->glyphRects[currentCharacter] = PNTR_CLITERAL(pntr_rectangle) {
                .x = 0,
                .y = 0,
                .width = currentRectangle.width,
                .height = currentRectangle.height,
            };
            currentRectangle.width = 0;
            currentRectangle.x = i + 1;
            currentCharacter++;
        }
        else {
            // Increase the width of the active glyph rectangle.
            currentRectangle.width++;
        }
    }

    PNTR_MEMCPY(font->characters, characters, charactersSize);

    return font;
}

/**
 * Loads a TTY Font from the file system.
 *
 * @param fileName The name of the image file to load as the font.
 * @param glyphWidth The width of each character on the font atlas.
 * @param glyphHeight The height of each character on the font atlas.
 * @param characters A string of characters that appear in the image.
 *
 * @return The newly loaded TTY font.
 *
 * @see examples/resources/ttyfont-16x16.png
 */
PNTR_API pntr_font* pntr_load_font_tty(const char* fileName, int glyphWidth, int glyphHeight, const char* characters) {
    pntr_image* image = pntr_load_image(fileName);
    if (image == NULL) {
        return NULL;
    }

    pntr_font* output = pntr_load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
    if (output == NULL) {
        pntr_unload_image(image);
    }

    return output;
}

PNTR_API pntr_font* pntr_load_font_tty_from_memory(const unsigned char* fileData, unsigned int dataSize, int glyphWidth, int glyphHeight, const char* characters) {
    if (fileData == NULL || dataSize == 0 || characters == NULL || glyphWidth <= 0 || glyphHeight <= 0) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* image = pntr_load_image_from_memory(PNTR_IMAGE_TYPE_PNG, fileData, dataSize);
    if (image == NULL) {
        return NULL;
    }

    pntr_font* output = pntr_load_font_tty_from_image(image, glyphWidth, glyphHeight, characters);
    if (output == NULL) {
        pntr_unload_image(image);
    }

    return output;
}

PNTR_API pntr_font* pntr_load_font_tty_from_image(pntr_image* image, int glyphWidth, int glyphHeight, const char* characters) {
    if (image == NULL || characters == NULL || glyphWidth <= 0 || glyphHeight <= 0) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Find out how many characters there are.
    int numCharacters = (int)PNTR_STRLEN(characters);
    size_t charactersSize = PNTR_STRSIZE(characters);

    // Create the font.
    pntr_font* font = _pntr_new_font(numCharacters, charactersSize, image);
    if (font == NULL) {
        return NULL;
    }

    // Set up the font data.
    for (int currentCharIndex = 0; currentCharIndex < numCharacters; currentCharIndex++) {
        // Source rectangle.
        font->srcRects[currentCharIndex] = PNTR_CLITERAL(pntr_rectangle) {
            .x = (currentCharIndex % (image->width / glyphWidth)) * glyphWidth,
            .y = (currentCharIndex / (image->width / glyphWidth)) * glyphHeight,
            .width = glyphWidth,
            .height = glyphHeight
        };

        // Where the glyph will be rendered.
        font->glyphRects[currentCharIndex] = PNTR_CLITERAL(pntr_rectangle) {
            .x = 0,
            .y = 0,
            .width = glyphWidth,
            .height = glyphHeight,
        };
    }

    PNTR_MEMCPY(font->characters, characters, charactersSize);

    return font;
}

/**
 * Unloads the given font from memory.
 *
 * @param font The font to unload from memory.
 */
PNTR_API void pntr_unload_font(pntr_font* font) {
    if (font == NULL) {
        return;
    }

    pntr_unload_image(font->atlas);
    pntr_unload_memory(font->srcRects);
    pntr_unload_memory(font->glyphRects);
    pntr_unload_memory(font->characters);
    PNTR_FREE(font);
}

/**
 * Creates a copy of the given font.
 *
 * @param font The font to copy.
 *
 * @return A new font that is a copy of the given font.
 */
PNTR_API pntr_font* pntr_font_copy(pntr_font* font) {
    if (font == NULL) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    pntr_image* atlas = pntr_image_copy(font->atlas);
    if (atlas == NULL) {
        return NULL;
    }

    size_t charactersSize = PNTR_STRSIZE(font->characters);
    pntr_font* output = _pntr_new_font(font->charactersLen, charactersSize, atlas);
    if (output == NULL) {
        pntr_unload_image(atlas);
        return NULL;
    }

    PNTR_MEMCPY(output->srcRects, font->srcRects, sizeof(pntr_rectangle) * (size_t)output->charactersLen);
    PNTR_MEMCPY(output->glyphRects, font->glyphRects, sizeof(pntr_rectangle) * (size_t)output->charactersLen);
    PNTR_MEMCPY(output->characters, font->characters, charactersSize);

    return output;
}

/**
 * Resize a font by a given scales.
 *
 * @param font The font that you would like to scale.
 * @param scaleX The scale of which to resize the width of the font by.
 * @param scaleY The scale of which to resize the height of the font by.
 * @param filter The filter to apply when resizing the font. PNTR_FILTER_NEARESTNEIGHBOR is good for pixel fonts.
 *
 * @return The new font that has been resized.
 */
PNTR_API pntr_font* pntr_font_scale(pntr_font* font, float scaleX, float scaleY, pntr_filter filter) {
    if (font == NULL || scaleX <= 0.0f || scaleY <= 0.0f) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    // Create the new font.
    pntr_font* output = pntr_font_copy(font);
    if (output == NULL) {
        return NULL;
    }

    // Resize the atlas.
    pntr_image* resizedAtlas = pntr_image_scale(output->atlas, scaleX, scaleY, filter);
    pntr_unload_image(output->atlas);
    output->atlas = resizedAtlas;

    // Resize the rectangles.
    for (int i = 0; i < font->charactersLen; i++) {
        output->srcRects[i].x = (int)((float)output->srcRects[i].x * scaleX);
        output->srcRects[i].y = (int)((float)output->srcRects[i].y * scaleY);
        output->srcRects[i].width = (int)((float)output->srcRects[i].width * scaleX);
        output->srcRects[i].height = (int)((float)output->srcRects[i].height * scaleY);
        output->glyphRects[i].x = (int)((float)output->glyphRects[i].x * scaleX);
        output->glyphRects[i].y = (int)((float)output->glyphRects[i].y * scaleY);
        output->glyphRects[i].width = (int)((float)output->glyphRects[i].width * scaleX);
        output->glyphRects[i].height = (int)((float)output->glyphRects[i].height * scaleY);
    }

    return output;
}

/**
 * Prints text on the given image, provided the length of the string.
 *
 * @param dst The image of which to print the text on.
 * @param font The font to use when rendering the text.
 * @param text The text to write.
 * @param textLength How many characters to draw from the text string. If 0, it will draw until the NULL terminator.
 * @param posX The position to print the text, starting from the top left on the X axis.
 * @param posY The position to print the text, starting from the top left on the Y axis.
 * @param tint What color to tint the font when drawing. Use PNTR_WHITE if you don't want to change the source color.
 *
 * @see pntr_draw_text_wrapped()
 */
PNTR_API void pntr_draw_text_len(pntr_image* dst, pntr_font* font, const char* text, int textLength, int posX, int posY, pntr_color tint) {
    if (dst == NULL || font == NULL || text == NULL) {
        return;
    }

    int x = posX;
    int y = posY;
    int tallestCharacter = 0;

    // Iterate through each character.
    pntr_codepoint_t codepoint;
    int count = 0;
    for (const char* v = PNTR_STRCODEPOINT(text, &codepoint); codepoint; v = PNTR_STRCODEPOINT(v, &codepoint)) {
        // If there is a text length provided, only draw up to that length.
        if (textLength > 0) {
            if (++count > textLength) {
                break;
            }
        }

        // If the character is a newline, move to the next line.
        if (codepoint == '\n') {
            // TODO: pntr_draw_text(): Allow for center/right alignment
            x = posX;
            y += tallestCharacter;
            continue;
        }

        // Find the character in the font's character index.
        char* foundCharacter = PNTR_STRCHR(font->characters, codepoint);
        if (!foundCharacter) {
            continue;
        }

        // Find the index of the character in the string.
        #ifdef PNTR_ENABLE_UTF8
        int i = (int)utf8nlen(font->characters, (size_t)(foundCharacter - font->characters));
        #else
        int i = (int)(foundCharacter - font->characters);
        #endif

        // Draw the character, unless it's a space.
        if (codepoint != ' ')  {
            pntr_draw_image_tint_rec(dst, font->atlas, font->srcRects[i], x + font->glyphRects[i].x, y + font->glyphRects[i].y, tint);
        }

        x += font->glyphRects[i].x + font->glyphRects[i].width;
        if (tallestCharacter < font->glyphRects[i].y + font->glyphRects[i].height) {
            tallestCharacter = font->glyphRects[i].y + font->glyphRects[i].height;
        }
    }
}

/**
 * Prints text on the given image.
 *
 * @param dst The image of which to print the text on.
 * @param font The font to use when rendering the text.
 * @param text The text to write. Must be NULL terminated.
 * @param posX The position to print the text, starting from the top left on the X axis.
 * @param posY The position to print the text, starting from the top left on the Y axis.
 * @param tint What color to tint the font when drawing. Use PNTR_WHITE if you don't want to change the source color.
 *
 * @see pntr_draw_text_wrapped()
 */
PNTR_API void pntr_draw_text(pntr_image* dst, pntr_font* font, const char* text, int posX, int posY, pntr_color tint) {
    pntr_draw_text_len(dst, font, text, 0, posX, posY, tint);
}

/**
 * Draws word-wrapped text on the given image.
 *
 * @param dst The image of which to print the text on.
 * @param font The font to use when rendering the text.
 * @param text The text to write. Must be NULL terminated.
 * @param posX The position to print the text, starting from the top left on the X axis.
 * @param posY The position to print the text, starting from the top left on the Y axis.
 * @param maxWidth The maximum width for each line.
 * @param tint What color to tint the font when drawing. Use PNTR_WHITE if you don't want to change the source color.
 *
 * @see pntr_draw_text()
 */
PNTR_API void pntr_draw_text_wrapped(pntr_image* dst, pntr_font* font, const char* text, int posX, int posY, int maxWidth, pntr_color tint) {
    if (dst == NULL || font == NULL || text == NULL) {
        return;
    }

    pntr_codepoint_t codepoint;
    char* currentChar = (char*)text;
    char* lineStart = currentChar;
    int lineLength = 1;
    char* lastSpace = NULL;
    int currentY = 0;
    pntr_vector textSize = {0, 0};

    // Iterate through each character.
    for (char* nextChar = PNTR_STRCODEPOINT(text, &codepoint); codepoint; nextChar = PNTR_STRCODEPOINT(nextChar, &codepoint)) {
        if (codepoint == ' ' || codepoint == '\n') {
            textSize = pntr_measure_text_ex(font, lineStart, lineLength - 1);
            if (textSize.x > maxWidth) {
                if (lastSpace != NULL) {
                    #ifdef PNTR_ENABLE_UTF8
                        lineLength = (int)utf8nlen(lineStart, (size_t)(lastSpace - lineStart));
                    #else
                        lineLength = (int)(lastSpace - lineStart);
                    #endif
                    pntr_draw_text_len(dst, font, lineStart, lineLength, posX, posY + currentY, tint);
                    currentY += textSize.y;
                    lineStart = lastSpace + 1;
                    #ifdef PNTR_ENABLE_UTF8
                        lineLength = (int)utf8nlen(lineStart, (size_t)(currentChar - lineStart));
                    #else
                        lineLength = (int)(currentChar - lineStart);
                    #endif
                }
                else {
                    // No current space, so draw what's in and move to new line.
                    pntr_draw_text_len(dst, font, lineStart, lineLength, posX, posY + currentY, tint);
                    currentY += textSize.y;
                    lineStart = nextChar;
                    lineLength = 0;
                }
            }
            else if (codepoint == '\n') {
                #ifdef PNTR_ENABLE_UTF8
                    lineLength = (int)utf8nlen(lineStart, (size_t)(currentChar - lineStart));
                #else
                    lineLength = (int)(currentChar - lineStart);
                #endif
                pntr_draw_text_len(dst, font, lineStart, lineLength, posX, posY + currentY, tint);
                currentY += textSize.y;
                lineStart = nextChar;
                lineLength = 0;
                lastSpace = NULL;
            }
            else {
                lastSpace = currentChar;
            }
        }

        currentChar = nextChar;
        lineLength++;
    }

    // Check if the last line is too long, and split it by the last space.
    if (pntr_measure_text(font, lineStart) > maxWidth && lastSpace != NULL) {
        #ifdef PNTR_ENABLE_UTF8
            lineLength = (int)utf8nlen(lineStart, (size_t)(lastSpace - lineStart));
        #else
            lineLength = (int)(lastSpace - lineStart);
        #endif
        pntr_draw_text_len(dst, font, lineStart, lineLength, posX, posY + currentY, tint);
        currentY += textSize.y;
        lineStart = lastSpace + 1;
    }

    pntr_draw_text(dst, font, lineStart, posX, posY + currentY, tint);
}

#ifdef PNTR_ENABLE_VARGS
/**
 * Prints text on the given image, with the provided format.
 *
 * @param dst The image of which to print the text on.
 * @param font The font to use when rendering the text.
 * @param posX The position to print the text, starting from the top left on the X axis.
 * @param posY The position to print the text, starting from the top left on the Y axis.
 * @param tint What color to tint the font when drawing. Use PNTR_WHITE if you don't want to change the source color.
 * @param text The text to write. Must be NULL terminated.
 * @param ... The arguments to pass for the format.
 *
 * @see printf
 * @see PNTR_ENABLE_VARGS
 *
 * @note Requires \c PNTR_ENABLE_VARGS to be used.
 */
PNTR_API void pntr_draw_text_ex(pntr_image* dst, pntr_font* font, int posX, int posY, pntr_color tint, const char* text, ...) {
    #ifndef PNTR_DRAW_TEXT_EX_STRING_LENGTH
    #define PNTR_DRAW_TEXT_EX_STRING_LENGTH 256
    #endif
    char output[PNTR_DRAW_TEXT_EX_STRING_LENGTH];

    va_list arg_ptr;
    va_start(arg_ptr, text);
    vsnprintf(output, PNTR_DRAW_TEXT_EX_STRING_LENGTH, text, arg_ptr);
    va_end(arg_ptr);

    pntr_draw_text(dst, font, output, posX, posY, tint);
}
#endif

/**
 * Measures the horizontal length of the text when rendered with the given font.
 *
 * @param font The font to use when rendering the text.
 * @param text The text to measure the length of.
 *
 * @return The amount of pixels the text is when rendered with the font.
 */
PNTR_API int pntr_measure_text(pntr_font* font, const char* text) {
    return pntr_measure_text_ex(font, text, 0).x;
}

/**
 * Measures the width and height of the given text when rendered with the font.
 *
 * @param font The font to use when rendering the text.
 * @param text The text to measure the length of.
 * @param textLength (Optional) How long the string to measure is from text. Provide 0 to determine the string length with a null character.
 *
 * @return A vector containing the width and height of the text when rendered by the font.
 */
PNTR_API pntr_vector pntr_measure_text_ex(pntr_font* font, const char* text, int textLength) {
    if (font == NULL || text == NULL) {
        return PNTR_CLITERAL(pntr_vector){0, 0};
    }

    pntr_vector output = PNTR_CLITERAL(pntr_vector) { .x = 0, .y = 0 };
    int currentX = 0;
    int currentY = 0;
    int index = 0;

    pntr_codepoint_t codepoint;
    for (const char* v = PNTR_STRCODEPOINT(text, &codepoint); codepoint; v = PNTR_STRCODEPOINT(v, &codepoint)) {
        // Stop drawing if we're only counting a certain amount of characters.
        if (textLength > 0 && index++ >= textLength) {
            break;
        }

        // Consider any newlines
        if (codepoint == '\n') {
            output.y += currentY;
            currentX = 0;
            continue;
        }

        // Find the index of the character in the font atlas.
        char* foundCharacter = PNTR_STRCHR(font->characters, codepoint);
        if (foundCharacter != NULL) {
            // Find the index of the character in the string.
            #ifdef PNTR_ENABLE_UTF8
            int i = (int)utf8nlen(font->characters, (size_t)(foundCharacter - font->characters));
            #else
            int i = (int)(foundCharacter - font->characters);
            #endif

            currentX += font->glyphRects[i].x + font->glyphRects[i].width;
            if (currentX > output.x) {
                output.x = currentX;
            }

            // Find the tallest character
            if (currentY < font->glyphRects[i].y + font->glyphRects[i].height) {
                currentY = font->glyphRects[i].y + font->glyphRects[i].height;
            }
        }
    }

    // Has at least one line.
    output.y += currentY;

    return output;
}

/**
 * Generate an image with rendered text on it.
 *
 * @param font The font to use when rendering the text.
 * @param text The text to render.
 * @param tint The color to tint the text by. Use PNTR_WHITE if you don't want to change the color.
 * @param backgroundColor The color of the background to use. Use PNTR_BLANK for a transparent background.
 *
 * @return A new image with text on it, using the given font.
 */
PNTR_API pntr_image* pntr_gen_image_text(pntr_font* font, const char* text, pntr_color tint, pntr_color backgroundColor) {
    pntr_vector size = pntr_measure_text_ex(font, text, 0);
    if (size.x <= 0 || size.y <= 0) {
        return NULL;
    }

    pntr_image* output = pntr_gen_image_color(size.x, size.y, backgroundColor);
    if (output == NULL) {
        return NULL;
    }

    pntr_draw_text(output, font, text, 0, 0, tint);
    return output;
}

/**
 * Load the default font.
 *
 * This must be unloaded manually afterwards with pntr_unload_font().
 *
 * Define `PNTR_ENABLE_DEFAULT_FONT` to allow using the default 8x8 font.
 *
 * You can change this by defining your own PNTR_DEFAULT_FONT. It must match the definition of pntr_load_font_default()
 * @code
 * #define PNTR_DEFAULT_FONT load_my_font
 * @endcode
 *
 * @return The default font, which must be unloaded when finished using.
 *
 * @see pntr_unload_font()
 * @see PNTR_ENABLE_DEFAULT_FONT
 * @see PNTR_DEFAULT_FONT
 */
PNTR_API pntr_font* pntr_load_font_default(void) {
    #ifdef PNTR_DEFAULT_FONT
        return PNTR_DEFAULT_FONT();
    #elif defined(PNTR_ENABLE_DEFAULT_FONT)
        // Load font8x8 character atlas.
        // https://github.com/dhepper/font8x8
        #include "external/font8x8_basic.h"

        // Default parameters for font8x8.
        #define PNTR_DEFAULT_FONT_NAME font8x8_basic
        #define PNTR_DEFAULT_FONT_GLYPH_WIDTH 8
        #define PNTR_DEFAULT_FONT_GLYPH_HEIGHT 8
        #define PNTR_DEFAULT_FONT_CHARACTERS_LEN 95

        // Build the atlas.
        pntr_image* atlas = pntr_gen_image_color(
            PNTR_DEFAULT_FONT_GLYPH_WIDTH * PNTR_DEFAULT_FONT_CHARACTERS_LEN,
            PNTR_DEFAULT_FONT_GLYPH_HEIGHT,
            PNTR_BLANK);
        if (atlas == NULL) {
            return NULL;
        }

        // Iterate through all the characters and draw them manually.
        for (int i = 0; i < PNTR_DEFAULT_FONT_CHARACTERS_LEN; i++) {
            const unsigned char* bitmap = PNTR_DEFAULT_FONT_NAME[i];
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if (bitmap[y] & 1 << x) {
                        pntr_draw_point(atlas, PNTR_DEFAULT_FONT_GLYPH_WIDTH * i + x, y, PNTR_WHITE);
                    }
                }
            }
        }

        // Build the character set with a null character at the end.
        char characters[PNTR_DEFAULT_FONT_CHARACTERS_LEN + 1];
        for (int i = 0; i < PNTR_DEFAULT_FONT_CHARACTERS_LEN; i++) {
            characters[i] = (char)(i + 32); // ASCII
        }
        characters[PNTR_DEFAULT_FONT_CHARACTERS_LEN] = '\0';

        // Use TTY to build the remaining font parameters.
        pntr_font* font = pntr_load_font_tty_from_image(atlas, PNTR_DEFAULT_FONT_GLYPH_WIDTH, PNTR_DEFAULT_FONT_GLYPH_HEIGHT, characters);
        if (font == NULL) {
            pntr_unload_image(atlas);
            return NULL;
        }

        return font;
    #else
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    #endif
}

/**
 * Loads a truetype font from the file system.
 *
 * This needs to be compiled with `PNTR_ENABLE_TTF` to be supported.
 *
 * @param fileName The name of the .ttf file.
 * @param fontSize The size of the font, in pixels.
 *
 * @return The newly loaded truetype font.
 *
 * @see examples/resources/tuffy.ttf
 *
 * @see PNTR_ENABLE_TTF
 */
PNTR_API pntr_font* pntr_load_font_ttf(const char* fileName, int fontSize) {
    if (fileName == NULL || fontSize <= 0) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    #ifndef PNTR_ENABLE_TTF
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    #else
        unsigned int bytesRead;
        unsigned char* fileData = pntr_load_file(fileName, &bytesRead);
        if (fileData == NULL) {
            return NULL;
        }

        pntr_font* output = pntr_load_font_ttf_from_memory(fileData, bytesRead, fontSize);
        pntr_unload_file(fileData);

        return output;
    #endif
}

/**
 * Load a truetype font from memory.
 *
 * This needs to be compiled with `PNTR_ENABLE_TTF` to be supported.
 *
 * @param fileData The data of the TTF file.
 * @param dataSize The size of the data in memory.
 * @param fontSize The desired size of the font, in pixels.
 *
 * @return The newly loaded truetype font.
 *
 * @see examples/resources/tuffy.ttf
 *
 * @see PNTR_ENABLE_TTF
 */
PNTR_API pntr_font* pntr_load_font_ttf_from_memory(const unsigned char* fileData, unsigned int dataSize, int fontSize) {
    if (fileData == NULL || dataSize == 0 || fontSize <= 0) {
        return (pntr_font*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    #ifndef PNTR_ENABLE_TTF
        return (pntr_font*)pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    #else
        // Which ASCII character to start rendering into the atlas
        #define PNTR_FONT_TTF_GLYPH_START 32

        // Find out how many glyhs we should prepare
        #ifndef PNTR_FONT_TTF_GLYPH_NUM
            #ifdef PNTR_ENABLE_UTF8
                // Up to the Cyrillic Supplement, minus the first 32 ascii characters
                // https://www.w3schools.com/charsets/ref_html_utf8.asp
                #define PNTR_FONT_TTF_GLYPH_NUM 1295
            #else
                // ASCII characater set
                #define PNTR_FONT_TTF_GLYPH_NUM 95
            #endif
        #endif

        // Create the bitmap data with ample space based on the font size
        int columns = 32;
        int rows = PNTR_FONT_TTF_GLYPH_NUM / columns;
        int width = fontSize * columns;
        int height = fontSize * rows;
        unsigned char* bitmap = (unsigned char*)PNTR_MALLOC((size_t)(width * height));
        if (bitmap == NULL) {
            return (pntr_font*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
        }

        // Bake the font into the bitmap
        stbtt_bakedchar characterData[PNTR_FONT_TTF_GLYPH_NUM];
        int result = stbtt_BakeFontBitmap(fileData, 0, (float)fontSize, bitmap, width, height, PNTR_FONT_TTF_GLYPH_START, PNTR_FONT_TTF_GLYPH_NUM, characterData);

        // Check to make sure the font was baked correctly
        if (result == 0) {
            PNTR_FREE(bitmap);
            return (pntr_font*)pntr_set_error(PNTR_ERROR_UNKNOWN);
        }

        // Port the bitmap to a pntr_image as the font atlas
        pntr_image* atlas = pntr_image_from_pixelformat((const void*)bitmap, width, height, PNTR_PIXELFORMAT_GRAYSCALE);
        PNTR_FREE(bitmap);
        if (atlas == NULL) {
            return NULL;
        }

        // Clear up the unused atlas space from memory, from the top left
        pntr_rectangle crop = pntr_image_alpha_border(atlas, 0.0f);
        pntr_image_crop(atlas, 0, 0, crop.x + crop.width, crop.y + crop.height);

        // Create the font data, with a null terminator at the end.
        size_t charactersSize = sizeof(pntr_codepoint_t) * (size_t)PNTR_FONT_TTF_GLYPH_NUM + 1;
        pntr_font* font = _pntr_new_font(PNTR_FONT_TTF_GLYPH_NUM, charactersSize, atlas);
        if (font == NULL) {
            pntr_unload_image(atlas);
            return NULL;
        }

        // Capture each glyph data
        #ifdef PNTR_ENABLE_UTF8
        char* destination = font->characters; // Where to write the new character.
        #endif

        // Build each character
        for (int i = 0; i < PNTR_FONT_TTF_GLYPH_NUM; i++) {
            // Calculate the source rectangles
            font->srcRects[i] = PNTR_CLITERAL(pntr_rectangle) {
                .x = characterData[i].x0,
                .y = characterData[i].y0,
                .width = characterData[i].x1 - characterData[i].x0,
                .height = characterData[i].y1 - characterData[i].y0
            };

            // Find where the glyphs will be rendered
            font->glyphRects[i] = PNTR_CLITERAL(pntr_rectangle) {
                .x = (int)characterData[i].xoff,
                .y = (int)(characterData[i].yoff + ((float)fontSize / 1.5f)), // TODO: Determine correct y glyph value
                .width = (int)characterData[i].xadvance,
                .height = (int)((float)fontSize / 3.0f) // TODO: Determine the correct glyph height
            };

            // Set up the active character
            #ifndef PNTR_ENABLE_UTF8
                font->characters[i] = (char)(PNTR_FONT_TTF_GLYPH_START + i);
            #else
                // Append the character to the destination, considering the remaining memory
                destination = utf8catcodepoint(destination, (pntr_codepoint_t)(PNTR_FONT_TTF_GLYPH_START + i), charactersSize - (size_t)(destination - font->characters));
            #endif
        }

        #ifdef PNTR_ENABLE_UTF8
        // Stick a null terminator at the end of the character string.
        destination[0] = '\0';

        // Resize the character string to the correct size.
        size_t newSize = PNTR_STRSIZE(font->characters);
        char* newCharacters = (char*)PNTR_MALLOC(newSize);
        if (newCharacters != NULL) {
            PNTR_MEMCPY(newCharacters, font->characters, newSize);
            PNTR_FREE(font->characters);
            font->characters = newCharacters;
        }
        #else
        font->characters[PNTR_FONT_TTF_GLYPH_NUM] = '\0';
        #endif

        return font;
    #endif
}

/**
 * Inverts the given color.
 *
 * @param color The color to invert.
 *
 * @return The new inverted color.
 *
 * @see pntr_image_color_invert()
 */
PNTR_API pntr_color pntr_color_invert(pntr_color color) {
    return PNTR_NEW_COLOR(
        (unsigned char)(255 - color.rgba.r),
        (unsigned char)(255 - color.rgba.g),
        (unsigned char)(255 - color.rgba.b),
        color.rgba.a
    );
}

/**
 * Inverts the given image.
 *
 * @param image The image to invert.
 *
 * @see pntr_color_invert()
 */
PNTR_API void pntr_image_color_invert(pntr_image* image) {
    if (image == NULL) {
        return;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, image->clip.x, y);
        for (int x = 0; x < image->clip.width; x++) {
            *pixel = pntr_color_invert(*pixel);
            pixel++;
        }
    }
}

/**
 * Changes the brightness of the given image by a factor.
 *
 * @param image The image to change brightness of.
 * @param factor The factor in which to affect the brightness from -1.0f to 1.0f.
 *
 * @see pntr_color_brightness()
 */
PNTR_API void pntr_image_color_brightness(pntr_image* image, float factor) {
    if (image == NULL) {
        return;
    }

    if (factor < -1.0f) {
        factor = -1.0f;
    }
    else if (factor > 1.0f) {
        factor = 1.0f;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, image->clip.x, y);
        for (int x = 0; x < image->clip.width; x++) {
            *pixel = pntr_color_brightness(*pixel, factor);
            pixel++;
        }
    }
}

#ifndef PNTR_LOAD_FILE
    #ifdef PNTR_NO_STDIO
        #define PNTR_LOAD_FILE(fileName, bytesRead) NULL
    #else
        #include <stdio.h> // FILE, fopen, fread
    #endif
#endif  // PNTR_LOAD_FILE

/**
 * Loads a file from the file system.
 *
 * This data must be cleared with pntr_unload_file() when finished.
 *
 * You can define your own callback for this by defining PNTR_LOAD_FILE.
 *
 * @param fileName The name of the file to load.
 * @param bytesRead Where to stick the amount of bytes that were read. Use NULL if you don't need the file size.
 *
 * @return A pointer to the file data in memory.
 *
 * @see pntr_unload_file()
 * @see PNTR_LOAD_FILE
 */
PNTR_API unsigned char* pntr_load_file(const char* fileName, unsigned int* bytesRead) {
    if (fileName == NULL) {
        return (unsigned char*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    #ifdef PNTR_LOAD_FILE
        return PNTR_LOAD_FILE(fileName, bytesRead);
    #else
        FILE* file = fopen(fileName, "rb");
        if (file == NULL) {
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return (unsigned char*)pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
        }

        fseek(file, 0, SEEK_END);
        size_t size = (size_t)ftell(file);
        fseek(file, 0, SEEK_SET);

        if (size <= 0) {
            fclose(file);
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return (unsigned char*)pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
        }

        unsigned char* data = (unsigned char*)PNTR_MALLOC(size * sizeof(unsigned char));
        if (data == NULL) {
            fclose(file);
            if (bytesRead != NULL) {
                *bytesRead = 0;
            }
            return (unsigned char*)pntr_set_error(PNTR_ERROR_NO_MEMORY);
        }

        // Read the file
        unsigned int bytes = (unsigned int)fread(data, sizeof(unsigned char), size, file);
        fclose(file);
        if (bytesRead != NULL) {
            *bytesRead = bytes;
        }

        return data;
    #endif
}

/**
 * Load text from a file. Must be cleared with pntr_unload_file().
 *
 * @param fileName The file to load.
 *
 * @see pntr_load_file()
 * @see pntr_unload_file_text()
 */
PNTR_API const char* pntr_load_file_text(const char *fileName) {
    unsigned int bytesRead;
    unsigned char* data = pntr_load_file(fileName, &bytesRead);

    if (data == NULL) {
        return NULL;
    }

    // While we have the loaded data, we'll need to null terminate it.
    char* output = (char*)PNTR_MALLOC(bytesRead + 1);
    if (output == NULL) {
        PNTR_FREE(data);
        return NULL;
    }

    PNTR_MEMCPY(output, data, bytesRead);
    output[bytesRead] = '\0';
    PNTR_FREE(data);
    return (const char*)output;
}

/**
 * Unload the file text data from memory.
 *
 * @param text The text to unload.
 *
 * @see pntr_load_file_text()
 */
PNTR_API void pntr_unload_file_text(const char* text) {
    pntr_unload_memory((void*)text);
}

#ifndef PNTR_SAVE_FILE
    #ifdef PNTR_NO_STDIO
        #define PNTR_SAVE_FILE(fileName, data, bytesToWrite) NULL
    #else
        #include <stdio.h> // FILE, fopen, fwrite
    #endif
#endif  // PNTR_SAVE_FILE

/**
 * Saves a file to the file system.
 *
 * You can define your own callback for this by defining PNTR_SAVE_FILE.
 *
 * @param fileName The name of the file to save.
 * @param data A pointer to the memory data in memory.
 * @param bytesToWrite The size of the data in memory.
 *
 * @return True if the file saved properly, false otherwise.
 *
 * @see PNTR_SAVE_FILE
 */
PNTR_API bool pntr_save_file(const char *fileName, const void *data, unsigned int bytesToWrite) {
    if (fileName == NULL || data == NULL) {
        return pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    #ifdef PNTR_SAVE_FILE
        return PNTR_SAVE_FILE(fileName, data, bytesToWrite);
    #else
        FILE *file = fopen(fileName, "wb");
        if (file == NULL) {
            return pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
        }

        size_t count = fwrite(data, sizeof(unsigned char), bytesToWrite, file);

        if (count <= 0) {
            fclose(file);
            return pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
        }

        if (count != (size_t)bytesToWrite) {
            fclose(file);
            return pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
        }

        return fclose(file) == 0;
    #endif
}

/**
 * Retrieve the size of the image data in memory in bytes, depending on the given pixel format.
 *
 * @param width The width of the image data.
 * @param height The height of the image data.
 * @param pixelFormat The pixel format of the image data.
 *
 * @return The size of the image data, in bytes.
 */
PNTR_API int pntr_get_pixel_data_size(int width, int height, pntr_pixelformat pixelFormat) {
    if (width <= 0 || height <= 0 || pixelFormat < 0) {
        return 0;
    }

    int bitsPerPixel = 0;
    int bitsPerByte = 8;
    switch (pixelFormat) {
        case PNTR_PIXELFORMAT_RGBA8888:
        case PNTR_PIXELFORMAT_ARGB8888:
            bitsPerPixel = (int)sizeof(pntr_color) * bitsPerByte;
            break;
        case PNTR_PIXELFORMAT_GRAYSCALE:
            bitsPerPixel = (int)sizeof(unsigned char) * bitsPerByte;
            break;
        default:
            bitsPerPixel = (int)sizeof(pntr_color) * bitsPerByte;
            pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
            break;
    }

    return bitsPerPixel * width * height / bitsPerByte; // Bytes
}

/**
 * Convert the given image to a new image using the provided pixel format.
 *
 * @param image The image to convert.
 * @param dataSize Where to put the resulting size of the image data. Use NULL if you have no need for the resulting data size.
 * @param pixelFormat The desired pixel format of the resulting image.
 *
 * @return A pointer to the resulting image data in memory.
 */
PNTR_API void* pntr_image_to_pixelformat(pntr_image* image, unsigned int* dataSize, pntr_pixelformat pixelFormat) {
    if (image == NULL) {
        return pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    int imageSize = pntr_get_pixel_data_size(image->width, image->height, pixelFormat);
    if (imageSize <= 0) {
        return pntr_set_error(PNTR_ERROR_UNKNOWN);
    }

    void* data = PNTR_MALLOC((size_t)imageSize);
    if (data == NULL) {
        return pntr_set_error(PNTR_ERROR_NO_MEMORY);
    }

    int pixelSize = pntr_get_pixel_data_size(1, 1, pixelFormat);

    int i = 0;
    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            pntr_set_pixel_color(
                ((unsigned char*)data) + (i++ * pixelSize),
                pixelFormat,
                PNTR_PIXEL(image, x, y)
            );
        }
    }

    // Output the data size
    if (dataSize != NULL) {
        *dataSize = (unsigned int)imageSize;
    }

    return data;
}

/**
 * Gets a PNG representation of the given image in memory.
 *
 * @note This method can be overloaded by defining \c PNTR_SAVE_IMAGE_TO_MEMORY .
 *
 * @param image The image to save to memory.
 * @param type The type of the image. Use PNTR_IMAGE_TYPE_UNKNOWN if unknown. PNTR_IMAGE_TYPE_PNG, PNTR_IMAGE_TYPE_JPG, etc.
 * @param dataSize Where to put the resulting size of the image. Use NULL if you do not care about getting the file size.
 *
 * @return The image data in memory. This data must be freed when finished using. NULL on failure.
 *
 * @see PNTR_SAVE_IMAGE_TO_MEMORY
 * @see PNTR_IMAGE_TYPE_PNG
 * @see PNTR_IMAGE_TYPE_JPG
 * @see PNTR_IMAGE_TYPE_UNKNOWN
 */
PNTR_API unsigned char* pntr_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize) {
    if (image == NULL) {
        return (unsigned char*)pntr_set_error(PNTR_ERROR_INVALID_ARGS);
    }

    return PNTR_SAVE_IMAGE_TO_MEMORY(image, type, dataSize);
}

/**
 * Saves an image to the file system.
 *
 * @param image The image to save to the file system.
 * @param fileName The name of the file to save.
 *
 * @return True when the file was saved successfully, false otherwise.
 *
 * @see pntr_save_image_to_memory()
 * @see pntr_save_file()
 */
PNTR_API bool pntr_save_image(pntr_image* image, const char* fileName) {
    unsigned int dataSize;
    pntr_image_type type = pntr_get_file_image_type(fileName);
    unsigned char* data = pntr_save_image_to_memory(image, type, &dataSize);
    if (data == NULL) {
        return false;
    }

    bool result = pntr_save_file(fileName, data, dataSize);
    PNTR_FREE(data);

    return result;
}

/**
 * Unloads the given file data.
 *
 * @param fileData The data of the file to unload from memory.
 *
 * @see pntr_load_file()
 */
PNTR_API void pntr_unload_file(unsigned char* fileData) {
    pntr_unload_memory((void*)fileData);
}

/**
 * Calculates a rectangle representing the available alpha border.
 *
 * @param image The image to calculate the alpha border on.
 * @param threshold A threshold factor from 0.0f to 1.0f to consider alpha.
 *
 * @return The rectangle representing the alpha border of the image.
 */
PNTR_API pntr_rectangle pntr_image_alpha_border(pntr_image* image, float threshold) {
    if (image == NULL) {
        return PNTR_CLITERAL(pntr_rectangle) {0, 0, 0, 0};
    }

    unsigned char alphaThreshold = (unsigned char)(threshold * 255.0f);
    int xMin = 9999999;
    int xMax = 0;
    int yMin = 9999999;
    int yMax = 0;

    for (int y = 0; y < image->height; y++) {
        for (int x = 0; x < image->width; x++) {
            if (image->data[y * (image->pitch >> 2) + x].rgba.a > alphaThreshold) {
                if (x < xMin) {
                    xMin = x;
                }
                if (x > xMax) {
                    xMax = x;
                }
                if (y < yMin) {
                    yMin = y;
                }
                if (y > yMax) {
                    yMax = y;
                }
            }
        }
    }

    // Check for empty blank image
    if ((xMin != 9999999) && (xMax != 9999999)) {
        return PNTR_CLITERAL(pntr_rectangle) {
            .x = xMin,
            .y = yMin,
            .width = xMax + 1 - xMin,
            .height = yMax + 1 - yMin
        };
    }

    return PNTR_CLITERAL(pntr_rectangle) {0, 0, 0, 0};
}

/**
 * Crops an image by the given coordinates.
 *
 * @param image The image to crop.
 * @param x The x coordinate to crop from.
 * @param y The y coordinate to crop from.
 * @param width The width of the desired crop.
 * @param height The height of the desired crop.
 *
 * @see pntr_image_from_image()
 */
PNTR_API bool pntr_image_crop(pntr_image* image, int x, int y, int width, int height) {
    if (image == NULL) {
        return false;
    }

    pntr_image* newImage = pntr_image_from_image(image, x, y, width, height);
    if (newImage == NULL) {
        return false;
    }

    // Clear the data if it isn't owned by another image.
    if (!image->subimage) {
        PNTR_FREE(image->data);
    }

    image->data = newImage->data;
    image->width = newImage->width;
    image->height = newImage->height;
    image->pitch = newImage->pitch;
    image->subimage = false;
    pntr_image_reset_clip(image);

    PNTR_FREE(newImage);

    return true;
}

/**
 * Crop an image based on the alpha border.
 *
 * @param image The image to crop.
 * @param threshold The alpha threshold to crop by, from 0.0f to 1.0f.
 *
 * @see pntr_image_alpha_border()
 * @see pntr_image_crop()
 */
PNTR_API void pntr_image_alpha_crop(pntr_image* image, float threshold) {
    if (image == NULL) {
        return;
    }

    pntr_rectangle crop = pntr_image_alpha_border(image, threshold);

    if (crop.width > 0 && crop.height > 0) {
        pntr_image_crop(image, crop.x, crop.y, crop.width, crop.height);
    }
}

/**
 * Apply contrast to the given color.
 *
 * @param color The color to apply constrast to.
 * @param contrast The amount of constrast to apply, from -1.0f to 1.0f.
 *
 * @return The new color with the contrast applied.
 */
PNTR_API pntr_color pntr_color_contrast(pntr_color color, float contrast) {
    if (contrast < -1.0f) {
        contrast = -1.0f;
    }
    else if (contrast > 1.0f) {
        contrast = 1.0f;
    }

    contrast = (1.0f + contrast) * contrast;

    float pR = (float)color.rgba.r / 255.0f - 0.5f;
    pR *= contrast;
    pR += 0.5f;
    pR *= 255;
    if (pR < 0) {
        pR = 0;
    }
    else if (pR > 255) {
        pR = 255;
    }

    float pG = (float)color.rgba.g / 255.0f - 0.5f;
    pG *= contrast;
    pG += 0.5f;
    pG *= 255;
    if (pG < 0) {
        pG = 0;
    }
    else if (pG > 255) {
        pG = 255;
    }

    float pB = (float)color.rgba.b / 255.0f - 0.5f;
    pB *= contrast;
    pB += 0.5f;
    pB *= 255;
    if (pB < 0) {
        pB = 0;
    }
    else if (pB > 255) {
        pB = 255;
    }

    return PNTR_NEW_COLOR((unsigned char)pR, (unsigned char)pG, (unsigned char)pB, color.rgba.a);
}

/**
 * Apply contrast to the given image.
 *
 * @param image The image you would like to apply contrast to.
 * @param contrast The factor of contrast to apply, from -1.0f to 1.0f.
 *
 * @see pntr_color_contrast()
 */
PNTR_API void pntr_image_color_contrast(pntr_image* image, float contrast) {
    if (image == NULL) {
        return;
    }

    if (contrast < -1.0f) {
        contrast = -1.0f;
    }
    else if (contrast > 1.0f) {
        contrast = 1.0f;
    }

    for (int y = image->clip.y; y < image->clip.y + image->clip.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, image->clip.x, y);
        for (int x = 0; x < image->clip.width; x++) {
            *pixel = pntr_color_contrast(*pixel, contrast);
            pixel++;
        }
    }
}

/**
 * Apply an alpha mask to an image.
 *
 * @param image The image to apply the alpha mask to.
 * @param alphaMask An image that has the alphaMask data.
 * @param posX Where to position the alpha mask on the image.
 * @param posY Where to position the alpha mask on the image.
 *
 * @todo // TODO: Add a pntr_draw_image_alpha_mask function.
 */
PNTR_API void pntr_image_alpha_mask(pntr_image* image, pntr_image* alphaMask, int posX, int posY) {
    if (image == NULL || alphaMask == NULL) {
        return;
    }

    pntr_rectangle srcRect = PNTR_CLITERAL(pntr_rectangle) { 0, 0, alphaMask->width, alphaMask->height };
    pntr_rectangle dstRect = PNTR_CLITERAL(pntr_rectangle) { posX, posY, alphaMask->width, alphaMask->height };

    // Update the source coordinates based on the destination
    if (dstRect.x < 0) {
        srcRect.x -= dstRect.x;
        srcRect.width += dstRect.x;
    }
    if (dstRect.y < 0) {
        srcRect.y -= dstRect.y;
        srcRect.height += dstRect.y;
    }

    if (!_pntr_rectangle_intersect(dstRect.x, dstRect.y,
            PNTR_MIN(dstRect.width, srcRect.width),
            PNTR_MIN(dstRect.height, srcRect.height),
            image->clip.x, image->clip.y,
            image->clip.width, image->clip.height, &dstRect)) {
        return;
    }

    for (int y = 0; y < dstRect.height; y++) {
        pntr_color* pixel = &PNTR_PIXEL(image, dstRect.x, dstRect.y + y);
        for (int x = 0; x < dstRect.width; x++) {
            if (pixel->rgba.a > 0) {
                pixel->rgba.a = PNTR_PIXEL(alphaMask, x, y).rgba.a;
            }
            pixel++;
        }
    }
}

/**
 * Resize the canvas of the given image.
 *
 * @param image The image you would like to resize.
 * @param newWidth The desired width of the new canvas.
 * @param newHeight The desired height of the new canvas.
 * @param offsetX How to offset the image once its canvas is resized. Use 0 if you like to keep the original image on the left.
 * @param offsetY How to offset the image once its canvas is resized. Use 0 if you like to keep the original image at the top.
 * @param fill The color to use for the background of the new image.
 *
 * @return True or false depending on if the image was resized correctly.
 */
PNTR_API bool pntr_image_resize_canvas(pntr_image* image, int newWidth, int newHeight, int offsetX, int offsetY, pntr_color fill) {
    if (image == NULL) {
        pntr_set_error(PNTR_ERROR_INVALID_ARGS);
        return false;
    }

    pntr_image* newImage = pntr_gen_image_color(newWidth, newHeight, fill);
    if (newImage == NULL) {
        return false;
    }

    pntr_draw_image(newImage, image, offsetX, offsetY);

    // Clear the image if it's not a subimage
    if (!image->subimage) {
        PNTR_FREE(image->data);
    }

    image->data = newImage->data;
    image->width = newImage->width;
    image->height = newImage->height;
    image->pitch = newImage->pitch;

    // TODO: pntr_image_resize_canvas - Adust the new image clip with the original one.
    pntr_image_reset_clip(image);
    image->subimage = false;

    PNTR_FREE(newImage);
    return true;
}

PNTR_API void pntr_draw_image_flipped(pntr_image* dst, pntr_image* src, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
    if (dst == NULL || src == NULL) {
        return;
    }

    pntr_draw_image_flipped_rec(dst, src,
        PNTR_CLITERAL(pntr_rectangle) { .x = 0, .y = 0, .width = src->width, .height = src->height },
        posX, posY,
        flipHorizontal,
        flipVertical,
        flipDiagonal
    );
}

PNTR_API void pntr_draw_image_flipped_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRec, int posX, int posY, bool flipHorizontal, bool flipVertical, bool flipDiagonal) {
    // If we are not flipping at all, use the simpler draw function.
    if (!flipHorizontal && !flipVertical && !flipDiagonal) {
        pntr_draw_image_tint_rec(dst, src, srcRec, posX, posY, PNTR_WHITE);
        return;
    }

    if (dst == NULL || src == NULL) {
        return;
    }

    if (!_pntr_rectangle_intersect(srcRec.x, srcRec.y, srcRec.width, srcRec.height, 0, 0, src->width, src->height, &srcRec)) {
        return;
    }

    int dstX, dstY;
    for (int y = 0; y < srcRec.height; y++) {
        for (int x = 0; x < srcRec.width; x++) {
            // Determine the destination pixels based on flip parameters
            if (flipDiagonal) {
                dstX = flipHorizontal ? srcRec.height - y - 1 : y;
                dstY = flipVertical ? srcRec.width - x - 1 : x;
            }
            else {
                dstY = flipVertical ? srcRec.height - y - 1 : y;
                dstX = flipHorizontal ? srcRec.width - x - 1 : x;
            }

            pntr_draw_point(dst, posX + dstX, posY + dstY,
                pntr_image_get_color(src, x, y)
            );
        }
    }
}

/**
 * Draw a scaled image.
 *
 * @param dst Pointer to the destination image where the output will be stored.
 * @param src Pointer to the source image that will be drawn onto the destination image.
 * @param posX Where to draw the scaled image, at the X coordinate.
 * @param posY Where to draw the scaled image, at the Y coordinate.
 * @param scaleX The scale of which to apply to the width of the image.
 * @param scaleY The scale of which to apply to the height of the image.
 * @param offsetX How much to offset the X drawing of the image, relative from its original source size.
 * @param offsetX How much to offset the Y drawing of the image, relative from its original source size.
 * @param filter Filter to be applied during the rotation.
 */
PNTR_API void pntr_draw_image_scaled(pntr_image* dst, pntr_image* src, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
    if (dst == NULL || src == NULL) {
        return;
    }

    pntr_draw_image_scaled_rec(dst, src,
        PNTR_CLITERAL(pntr_rectangle) { .x = 0, .y = 0, .width = src->width, .height = src->height },
        posX, posY,
        scaleX, scaleY,
        offsetX, offsetY,
        filter);
}

PNTR_API void pntr_draw_image_scaled_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, float scaleX, float scaleY, float offsetX, float offsetY, pntr_filter filter) {
    if (dst == NULL || src == NULL || scaleX <= 0.0f || scaleY <= 0.0f) {
        return;
    }

    if (!_pntr_rectangle_intersect(srcRect.x, srcRect.y, srcRect.width, srcRect.height, 0, 0, src->width, src->height, &srcRect)) {
        return;
    }

    int newWidth = (int)((float)srcRect.width * scaleX);
    int newHeight = (int)((float)srcRect.height * scaleY);
    int offsetXRatio = (int)(offsetX / (float)srcRect.width * (float)newWidth);
    int offsetYRatio = (int)(offsetY / (float)srcRect.height * (float)newHeight);

    switch (filter) {
        case PNTR_FILTER_BILINEAR: {
            float xRatio = (float)srcRect.width / (float)newWidth;
            float yRatio = (float)srcRect.height / (float)newHeight;

            for (int y = 0; y < newHeight; y++) {
                int yPosition = posY + y - offsetYRatio;
                if (yPosition < dst->clip.y || yPosition >= dst->clip.y + dst->clip.height) {
                    continue;
                }
                float srcY = (float)y * yRatio;
                int srcYPixel = srcRect.y + (int)srcY;
                int srcYPixelPlusOne = y == newHeight - 1 ? (int)srcYPixel : (int)srcYPixel + 1;
                for (int x = 0; x < newWidth; x++) {
                    int xPosition = posX + x - offsetXRatio;
                    if (xPosition < dst->clip.x || xPosition >= dst->clip.x + dst->clip.width) {
                        continue;
                    }
                    float srcX = (float)x * xRatio;
                    int srcXPixel = srcRect.y + (int)srcX;
                    int srcXPixelPlusOne = x == newWidth - 1 ? (int)srcXPixel : (int)srcXPixel + 1;
                    pntr_draw_point_unsafe(dst, xPosition, yPosition, pntr_color_bilinear_interpolate(
                        src->data[srcYPixel * (src->pitch >> 2) + srcXPixel],
                        src->data[srcYPixelPlusOne * (src->pitch >> 2) + srcXPixel],
                        src->data[srcYPixel * (src->pitch >> 2) + srcXPixelPlusOne],
                        src->data[srcYPixelPlusOne * (src->pitch >> 2) + srcXPixelPlusOne],
                        srcX - PNTR_FLOORF(srcX),
                        srcY - PNTR_FLOORF(srcY)
                    ));
                }
            }
        }
        break;
        case PNTR_FILTER_NEARESTNEIGHBOR:
        default: {
            int xRatio = (srcRect.width << 16) / newWidth + 1;
            int yRatio = (srcRect.height << 16) / newHeight + 1;

            for (int y = 0; y < newHeight; y++) {
                int yPosition = posY + y - offsetYRatio;
                if (yPosition < dst->clip.y || yPosition >= dst->clip.y + dst->clip.height) {
                    continue;
                }
                int y2 = (y * yRatio) >> 16;
                for (int x = 0; x < newWidth; x++) {
                    int xPosition = posX + x - offsetXRatio;
                    if (xPosition < dst->clip.x || xPosition >= dst->clip.x + dst->clip.width) {
                        continue;
                    }
                    int x2 = (x * xRatio) >> 16;
                    pntr_draw_point_unsafe(dst,
                        xPosition,
                        yPosition,
                        PNTR_PIXEL(src, srcRect.x + x2, srcRect.y + y2)
                    );
                }
            }
        }
        break;
    }
}

/**
 * Normalizes a degree of rotation between 0 and 360 degrees.
 *
 * @param degrees The angle to normalize.
 *
 * @return The new degrees represented between 0 and 360.
 *
 * @internal
 */
float _pntr_normalize_degrees(float degrees) {
    if (degrees < 0) {
        return 360.0f - PNTR_FMODF(-degrees, 360.0f);
    }

    return PNTR_FMODF(degrees, 360.0f);
}

/**
 * Creates a new image based off the given image, that's rotated by the given degrees.
 *
 * @param image The image to rotate.
 * @param degrees The desired amount to rotate the image in degrees.
 *
 * @return The new rotated image.
 *
 * @see pntr_draw_image_rotated()
 * @see pntr_draw_image_rotated_rec()
 */
PNTR_API pntr_image* pntr_image_rotate(pntr_image* image, float degrees, pntr_filter filter) {
    if (image == NULL) {
        return NULL;
    }

    degrees = _pntr_normalize_degrees(degrees);

    if (degrees == 0.0f) {
        return pntr_image_copy(image);
    }

    if (degrees == 90.0f || degrees == 180.0f || degrees == 270.0f) {
        pntr_image* output;
        if (degrees == 180.0f) {
            output = pntr_gen_image_color(image->width, image->height, PNTR_BLANK);
        }
        else {
            output = pntr_gen_image_color(image->height, image->width, PNTR_BLANK);
        }
        if (output == NULL) {
            return NULL;
        }

        pntr_draw_image_rotated(output, image, 0, 0, degrees, 0.0f, 0.0f, filter);

        return output;
    }

    float radians = degrees * PNTR_DEG2RAD;
    float cosTheta = PNTR_COSF(radians);
    float sinTheta = PNTR_SINF(radians);

    int newWidth = (int)PNTR_CEILF(PNTR_FABSF((float)image->width * cosTheta) + PNTR_FABSF((float)image->height * sinTheta));
    int newHeight = (int)PNTR_CEILF(PNTR_FABSF((float)image->width * sinTheta) + PNTR_FABSF((float)image->height * cosTheta));

    pntr_image* rotatedImage = pntr_gen_image_color(newWidth, newHeight, PNTR_BLANK);
    if (rotatedImage == NULL) {
        return NULL;
    }

    pntr_draw_image_rotated(rotatedImage, image, 0, 0, degrees, 0.0f, 0.0f, filter);

    return rotatedImage;
}

/**
 * Bilinear interpolate the given colors, in the sequence below, based on their given 0-1 coordinates.
 *
 * The colors appear in the following order:
 *
 *     00 10
 *     01 11
 *
 * @param color00 The top left color.
 * @param color01 The bottom left color.
 * @param color10 The top right color.
 * @param color11 The bottom right color.
 * @param coordinateX A 0.0f to 1.0f fraction between color00 and color 10.
 * @param coordinateY A 0.0f to 1.0f fraction between color00 and color 01.
 *
 * @return The bilinear interpolated color.
 */
PNTR_API pntr_color pntr_color_bilinear_interpolate(pntr_color color00, pntr_color color01, pntr_color color10, pntr_color color11, float coordinateX, float coordinateY) {
    return PNTR_NEW_COLOR(
        (uint8_t)(color00.rgba.r * (1 - coordinateX) * (1 - coordinateY) + color01.rgba.r * (1 - coordinateX) * coordinateY + color10.rgba.r * coordinateX * (1 - coordinateY) + color11.rgba.r * coordinateX * coordinateY),
        (uint8_t)(color00.rgba.g * (1 - coordinateX) * (1 - coordinateY) + color01.rgba.g * (1 - coordinateX) * coordinateY + color10.rgba.g * coordinateX * (1 - coordinateY) + color11.rgba.g * coordinateX * coordinateY),
        (uint8_t)(color00.rgba.b * (1 - coordinateX) * (1 - coordinateY) + color01.rgba.b * (1 - coordinateX) * coordinateY + color10.rgba.b * coordinateX * (1 - coordinateY) + color11.rgba.b * coordinateX * coordinateY),
        (uint8_t)(color00.rgba.a * (1 - coordinateX) * (1 - coordinateY) + color01.rgba.a * (1 - coordinateX) * coordinateY + color10.rgba.a * coordinateX * (1 - coordinateY) + color11.rgba.a * coordinateX * coordinateY)
    );
}

/**
 * Draw a rotated image onto another image.
 *
 * @param dst Pointer to the destination image where the output will be stored.
 * @param src Pointer to the source image that will be drawn onto the destination image.
 * @param posX Where to draw the rotated image, at the X coordinate.
 * @param posY Where to draw the rotated image, at the Y coordinate.
 * @param degrees The degrees of rotation.
 * @param offsetX Offset in the X direction after rotation.
 * @param offsetY Offset in the Y direction after rotation.
 * @param filter Filter to be applied during the rotation. PNTR_FILTER_BILINEAR and PNTR_FILTER_NEARESTNEIGHBOR are supported.
 *
 * @see pntr_draw_image_rec_rotated()
 * @see pntr_image_rotate()
 */
PNTR_API void pntr_draw_image_rotated(pntr_image* dst, pntr_image* src, int posX, int posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
    if (dst == NULL || src == NULL) {
        return;
    }

    pntr_draw_image_rotated_rec(dst, src,
        PNTR_CLITERAL(pntr_rectangle) { .x = 0, .y = 0, .width = src->width, .height = src->height },
        posX, posY,
        degrees,
        offsetX, offsetY,
        filter);
}

/**
 * Draw a rotated portion of an image onto another image.
 *
 * @param dst Pointer to the destination image where the output will be stored.
 * @param src Pointer to the source image that will be drawn onto the destination image.
 * @param srcRect The portion of the source image to draw.
 * @param posX Where to draw the rotated image, at the X coordinate.
 * @param posY Where to draw the rotated image, at the Y coordinate.
 * @param degrees The degrees of rotation.
 * @param offsetX Offset in the X direction after rotation.
 * @param offsetY Offset in the Y direction after rotation.
 * @param filter Filter to be applied during the rotation. PNTR_FILTER_BILINEAR and PNTR_FILTER_NEARESTNEIGHBOR are supported.
 *
 * @see pntr_draw_image_rotated()
 */
PNTR_API void pntr_draw_image_rotated_rec(pntr_image* dst, pntr_image* src, pntr_rectangle srcRect, int posX, int posY, float degrees, float offsetX, float offsetY, pntr_filter filter) {
    if (dst == NULL || src == NULL) {
        return;
    }

    degrees = _pntr_normalize_degrees(degrees);

    // Draw the image normally if not rotated.
    if (degrees == 0.0f) {
        pntr_draw_image_rec(dst, src, srcRect, posX - (int)offsetX, posY - (int)offsetY);
        return;
    }

    // Clean up the source rectangle.
    if (srcRect.x < 0) {
        srcRect.x = 0;
    }
    if (srcRect.y < 0) {
        srcRect.y = 0;
    }
    if (srcRect.width <= 0 || srcRect.width > src->width) {
        srcRect.width = src->width - srcRect.x;
    }
    if (srcRect.height <= 0 || srcRect.height > src->height) {
        srcRect.height = src->height - srcRect.y;
    }

    // Simple rotation by 90 degrees can be fast.
    if (degrees == 90.0f || degrees == 180.0f || degrees == 270.0f) {
        // Build the destination coordinates of the image.
        pntr_rectangle dstRect = PNTR_CLITERAL(pntr_rectangle) { .x = posX, .y = posY, .width = srcRect.width, .height = srcRect.height };
        if (degrees == 90.0f || degrees == 270.0f) {
            dstRect.width = srcRect.height;
            dstRect.height = srcRect.width;
            dstRect.x -= (int)offsetY;
            dstRect.y -= (int)offsetX;
        }
        else {
            dstRect.x -= (int)offsetX;
            dstRect.y -= (int)offsetY;
        }

        // Exit if it's not even on the screen.
        if (dstRect.x + dstRect.width < dst->clip.x || dstRect.y + dstRect.height < dst->clip.y || dstRect.x >= dst->clip.x + dst->clip.width || dstRect.y >= dst->clip.y + dst->clip.height) {
            return;
        }

        // Draw the source portion on the destination.
        for (int y = 0; y < srcRect.height; y++) {
            for (int x = 0; x < srcRect.width; x++) {
                if (degrees == 90.0f) {
                    pntr_draw_point(dst,
                        dstRect.x + y,
                        dstRect.y + srcRect.width - x,
                        PNTR_PIXEL(src, srcRect.x + x, srcRect.y + y)
                    );
                } else if (degrees == 180.0f) {
                    pntr_draw_point(dst,
                        dstRect.x + srcRect.width - x,
                        dstRect.y + srcRect.height - y,
                        PNTR_PIXEL(src, srcRect.x + x, srcRect.y + y)
                    );
                }
                else {
                    pntr_draw_point(dst,
                        dstRect.x + srcRect.height - y,
                        dstRect.y + x,
                        PNTR_PIXEL(src, srcRect.x + x, srcRect.y + y)
                    );
                }
            }
        }

        return;
    }

    float radians = degrees * PNTR_DEG2RAD;
    float cosTheta = PNTR_COSF(radians);
    float sinTheta = PNTR_SINF(radians);

    int newWidth = (int)PNTR_CEILF(PNTR_FABSF((float)srcRect.width * cosTheta) + PNTR_FABSF((float)srcRect.height * sinTheta));
    int newHeight = (int)PNTR_CEILF(PNTR_FABSF((float)srcRect.width * sinTheta) + PNTR_FABSF((float)srcRect.height * cosTheta));

    int offsetXRatio = (int)(offsetX / (float)srcRect.width * (float)newWidth);
    int offsetYRatio = (int)(offsetY / (float)srcRect.height * (float)newHeight);

    // Make sure we're actually drawing on the screen.
    if (posX - offsetXRatio + newWidth < dst->clip.x || posX - offsetXRatio >= dst->clip.x + dst->clip.width || posY - offsetYRatio + newHeight < dst->clip.y || posY - offsetYRatio >= dst->clip.y + dst->clip.height) {
        return;
    }

    float centerX = (float)srcRect.width / 2.0f;
    float centerY = (float)srcRect.height / 2.0f;
    int srcXint, srcYint;
    float srcX, srcY;

    for (int y = 0; y < newHeight; y++) {
        // Only draw onto the screen.
        int destY = posY + y - offsetYRatio;
        if (destY < dst->clip.y || destY >= dst->clip.y + dst->clip.height) {
            continue;
        }

        for (int x = 0; x < newWidth; x++) {
            // Make sure we're actually drawing onto the screen.
            int destX = posX + x - offsetXRatio;
            if (destX < dst->clip.x || destX >= dst->clip.x + dst->clip.width ) {
                continue;
            }

            srcX = (float)(x - newWidth / 2) * cosTheta - (float)(y - newHeight / 2) * sinTheta + centerX;
            srcY = (float)(x - newWidth / 2) * sinTheta + (float)(y - newHeight / 2) * cosTheta + centerY;

            // Only draw from the source rectangle.
            if (srcX < 0 || srcX >= srcRect.width || srcY < 0 || srcY >= srcRect.height) {
                continue;
            }

            srcXint = (int)srcX + srcRect.x;
            srcYint = (int)srcY + srcRect.y;

            if (filter == PNTR_FILTER_NEARESTNEIGHBOR) {
                pntr_draw_point_unsafe(dst,
                    destX,
                    destY,
                    PNTR_PIXEL(src, srcXint, srcYint)
                );
            }
            else {
                // For bilinear, don't overscan.
                if (srcX >= srcRect.width - 1 || srcY >= srcRect.height - 1) {
                    continue;
                }

                pntr_draw_point_unsafe(dst,
                    destX,
                    destY,
                    pntr_color_bilinear_interpolate(
                        PNTR_PIXEL(src, srcXint, srcYint),
                        PNTR_PIXEL(src, srcXint, srcYint + 1),
                        PNTR_PIXEL(src, srcXint + 1, srcYint),
                        PNTR_PIXEL(src, srcXint + 1, srcYint + 1),
                        srcX - PNTR_FLOORF(srcX),
                        srcY - PNTR_FLOORF(srcY)
                    )
                );
            }
        }
    }
}

/**
 * Generate image: vertical and horizontal gradient.
 *
 * @param width The width of the new image.
 * @param height The height of the new image.
 * @param topLeft The color at the top left of the image.
 * @param topRight The color at the top right of the image.
 * @param bottomLeft The color at the bottom left of the image.
 * @param bottomRight The color at the bottom right of the image.
 *
 * @return A pointer to the new image.
 */
PNTR_API pntr_image* pntr_gen_image_gradient(int width, int height, pntr_color topLeft, pntr_color topRight, pntr_color bottomLeft, pntr_color bottomRight) {
    pntr_image* image = pntr_gen_image_color(width, height, PNTR_BLANK);
    if (image == NULL) {
        return NULL;
    }

    pntr_draw_rectangle_gradient(image, 0, 0, width, height, topLeft, topRight, bottomLeft, bottomRight);

    return image;
}

/**
 * Get the clip rectangle from the given image. Anything outside of the clip cannot be changed.
 *
 * @param image The image of which to get the clip rectangle for.
 *
 * @return The clip rectangle associated with the given image.
 */
PNTR_API pntr_rectangle pntr_image_get_clip(pntr_image* image) {
    if (image == NULL) {
        return PNTR_CLITERAL(pntr_rectangle) {
            .x = 0,
            .y = 0,
            .width = 0,
            .height = 0
        };
    }

    return image->clip;
}

/**
 * Set the clipping rectangle for the given image to restrict drawing within.
 *
 * @param image The image to set the clipping rectangle.
 * @param x The X coordinate for the clipping rectangle.
 * @param y The Y coordinate for the clipping rectangle.
 * @param width The width of the desired clipping rectangle.
 * @param height The height of the desired clipping rectangle.
 *
 * @see pntr_image_set_clip_rec()
 * @see pntr_image_reset_clip()
 */
PNTR_API void pntr_image_set_clip(pntr_image* image, int x, int y, int width, int height) {
    if (image == NULL) {
        return;
    }

    pntr_rectangle clip;
    if (_pntr_rectangle_intersect(x, y, width, height, 0, 0, image->width, image->height, &clip)) {
        image->clip = clip;
    }
}

/**
 * Set the clipping rectangle for the given image to restrict drawing within, using a rectangle.
 *
 * @param image The image to set the clipping rectangle.
 * @param clip The rectangle to set the new clip boundries.
 *
 * @see pntr_image_set_clip()
 * @see pntr_image_reset_clip()
 */
PNTR_API void pntr_image_set_clip_rec(pntr_image* image, pntr_rectangle clip) {
    pntr_image_set_clip(image, clip.x, clip.y, clip.width, clip.height);
}

/**
 * Reset the clipping rectangle for the given image.
 *
 * @param image The image to reset the clipping image for.
 *
 * @see pntr_image_set_clip()
 */
PNTR_API void pntr_image_reset_clip(pntr_image* image) {
    if (image == NULL) {
        return;
    }

    image->clip.x = 0;
    image->clip.y = 0;
    image->clip.width = image->width;
    image->clip.height = image->height;
}

/**
 * Allocates the given amount of bytes in size.
 *
 * @param size The amount of bytes to allocate to memory.
 *
 * @return A pointer to the new memory address.
 *
 * @see PNTR_MALLOC
 */
PNTR_API void* pntr_load_memory(size_t size) {
    return PNTR_MALLOC(size);
}

/**
 * Unloads the given memory.
 *
 * @param pointer A pointer to the memory of which to unload.
 *
 * @see PNTR_FREE
 */
PNTR_API void pntr_unload_memory(void* pointer) {
    if (pointer != NULL) {
        PNTR_FREE(pointer);
    }
}

/**
 * Copy a memory address from the source to the destination.
 *
 * @param destination Where to copy the memory to.
 * @param source The source data.
 * @param size The size of the data to copy.
 *
 * @return The destination.
 *
 * @see PNTR_MEMCPY
 */
PNTR_API void* pntr_memory_copy(void* destination, void* source, size_t size) {
    return PNTR_MEMCPY(destination, source, size);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // PNTR_IMPLEMENTATION_ONCE
#endif  // PNTR_IMPLEMENTATION
