#ifndef PNTR_CUTE_PNG_H__
#define PNTR_CUTE_PNG_H__

/**
 * @defgroup pntr_cute_png pntr_cute_png
 * @{
 *
 * @brief [cute_png](https://github.com/RandyGaul/cute_headers/blob/master/cute_png.h) integration with pntr for loading and saving images.
 *
 * To use `cute_png.h` for saving and loading images, define `PNTR_CUTE_PNG` prior to including `pntr.h`:
 *
 * @code
 * #define PNTR_CUTE_PNG
 * #define PNTR_IMPLEMENTATION
 * #include "pntr.h"
 * @endcode
 *
 * @see https://github.com/RandyGaul/cute_headers/blob/master/cute_png.h
 * @see PNTR_CUTE_PNG
 * @see PNTR_LOAD_IMAGE_FROM_MEMORY
 * @see PNTR_SAVE_IMAGE_TO_MEMORY
 * @see PNTR_NO_LOAD_IMAGE
 * @see PNTR_NO_SAVE_IMAGE
 */

/**
 * Load a pntr_image using cute_png.
 */
pntr_image* pntr_cute_png_load_image_from_memory(pntr_image_type type, const unsigned char *fileData, unsigned int dataSize);

/**
 * Save an image to memory using cutr_png.
 */
unsigned char* pntr_cute_png_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize);

/**
 * @}
 */

#endif  // PNTR_CUTE_PNG_H__

#ifdef PNTR_IMPLEMENTATION
#ifndef PNTR_CUTE_PNG_IMPLEMENTATION
#define PNTR_CUTE_PNG_IMPLEMENTATION

#ifndef PNTR_MEMCMP
    #include <string.h>
    #define PNTR_MEMCMP(ptr1, ptr2, num) memcmp(ptr1, ptr2, num)
#endif  // PNTR_MEMCMP

#ifndef PNTR_NO_CUTE_PNG_IMPLEMENTATION
    #define CUTE_PNG_IMPLEMENTATION
    #define CUTE_PNG_ALLOCA PNTR_MALLOC
    #define CUTE_PNG_ALLOC PNTR_MALLOC
    #define CUTE_PNG_FREE PNTR_FREE
    #define CUTE_PNG_CALLOC(num, size) PNTR_MALLOC((num) * (size))
    #define CUTE_PNG_REALLOC PNTR_REALLOC
    #define CUTE_PNG_MEMCMP PNTR_MEMCMP
    #define CUTE_PNG_MEMCPY PNTR_MEMCPY
    #define CUTE_PNG_MEMSET PNTR_MEMSET
    #define CUTE_PNG_FPRINTF (void)
    #define CUTE_PNG_ASSERT(condition) 0 // Skip assertions
    #define CUTE_PNG_SEEK_SET 0
    #define CUTE_PNG_SEEK_END 0
    #define CUTE_PNG_FILE void
    #define CUTE_PNG_FOPEN(filename, mode) (CUTE_PNG_FILE*)filename
    #define CUTE_PNG_FSEEK(stream, offset, origin) offset
    #define CUTE_PNG_FREAD(data, size, num, fp) (void)(data)
    #define CUTE_PNG_FTELL(fp) 0
    #define CUTE_PNG_FWRITE(data, size, num, fp) (void)(data)
    #define CUTE_PNG_FCLOSE (void)
    #define CUTE_PNG_FERROR(fp) 1
    #define CUTE_PNG_ATLAS_MUST_FIT 1
    #define CUTE_PNG_ATLAS_FLIP_Y_AXIS_FOR_UV 0
    #define CUTE_PNG_ATLAS_EMPTY_COLOR 0
#endif  // PNTR_NO_CUTE_PNG_IMPLEMENTATION

#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpragmas"
    #pragma GCC diagnostic ignored "-Wunknown-pragmas"
    #pragma GCC diagnostic ignored "-Wsign-conversion"
    #pragma GCC diagnostic ignored "-Wconversion"
    #pragma GCC diagnostic ignored "-Wunused-function"
    #pragma GCC diagnostic ignored "-Wunused-variable"
    #pragma GCC diagnostic ignored "-Wsign-compare"
    #pragma GCC diagnostic ignored "-Wunused-value"
#endif // defined(__GNUC__) || defined(__clang__)

#ifndef PNTR_CUTE_PNG_H
#define PNTR_CUTE_PNG_H "../external/cute_png.h"
#endif
#include PNTR_CUTE_PNG_H

#define PNTR_NO_CUTE_PNG_IMPLEMENTATION
#ifdef CUTE_PNG_IMPLEMENTATION
    #undef CUTE_PNG_IMPLEMENTATION
#endif

#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif // defined(__GNUC__) || defined(__clang__)

pntr_image* pntr_cute_png_load_image_from_memory(pntr_image_type type, const unsigned char *fileData, unsigned int dataSize) {
    if (!(type == PNTR_IMAGE_TYPE_PNG || type == PNTR_IMAGE_TYPE_UNKNOWN)) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    }

    cp_image_t image = cp_load_png_mem(fileData, (int)dataSize);
    if (image.pix == NULL) {
        return (pntr_image*)pntr_set_error(PNTR_ERROR_FAILED_TO_OPEN);
    }

    pntr_image* output = pntr_image_from_pixelformat((const void*)image.pix, image.w, image.h, PNTR_PIXELFORMAT_RGBA8888);
    cp_free_png(&image);

    return output;
}

#ifndef PNTR_LOAD_IMAGE_FROM_MEMORY
#define PNTR_LOAD_IMAGE_FROM_MEMORY pntr_cute_png_load_image_from_memory
#endif

unsigned char* pntr_cute_png_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize) {
    if (!(type == PNTR_IMAGE_TYPE_UNKNOWN || type == PNTR_IMAGE_TYPE_PNG)) {
        return (unsigned char*)pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
    }

    cp_image_t cpImage = PNTR_CLITERAL(cp_image_t) {
        .w = image->width,
        .h = image->height
    };

    cpImage.pix = (cp_pixel_t*)pntr_image_to_pixelformat(image, NULL, PNTR_PIXELFORMAT_RGBA8888);
    if (cpImage.pix == NULL) {
        return NULL;
    }

    cp_saved_png_t png = cp_save_png_to_memory(&cpImage);
    if (png.data == NULL) {
        cp_free_png(&cpImage);
        return (unsigned char*)pntr_set_error(PNTR_ERROR_FAILED_TO_WRITE);
    }

    // Export the datasize
    if (dataSize != NULL) {
        *dataSize = (unsigned int)png.size;
    }

    // Free up the temporary copy
    cp_free_png(&cpImage);

    return (unsigned char*)png.data;
}

#ifndef PNTR_SAVE_IMAGE_TO_MEMORY
#define PNTR_SAVE_IMAGE_TO_MEMORY pntr_cute_png_save_image_to_memory
#endif

#endif  // PNTR_CUTE_PNG_IMPLEMENTATION
#endif  // PNTR_IMPLEMENTATION
