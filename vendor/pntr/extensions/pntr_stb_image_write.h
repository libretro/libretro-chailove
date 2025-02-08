#ifndef PNTR_STB_IMAGE_WRITE_H__
#define PNTR_STB_IMAGE_WRITE_H__

/**
 * @defgroup pntr_stb_image_write pntr_stb_image_write
 * @{
 *
 * @brief [stb_image_write](https://github.com/nothings/stb/blob/master/stb_image_write.h) integration with pntr for saving images.
 *
 * To use *stb_image_write* for saving images, define `PNTR_STB_IMAGE` prior to including `pntr.h`. This is provided by default.
 *
 * @code
 * #define PNTR_STB_IMAGE
 * #define PNTR_IMPLEMENTATION
 * #include "pntr.h"
 * @endcode
 *
 * Image saving can be completely disabled with `PNTR_NO_SAVE_IMAGE`.
 *
 * @see https://github.com/nothings/stb/blob/master/stb_image_write.h
 * @see PNTR_STB_IMAGE
 * @see PNTR_SAVE_IMAGE_TO_MEMORY
 * @see PNTR_NO_SAVE_IMAGE
 */

/**
 * Save an image using stb_image.
 */
unsigned char* pntr_stb_image_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize);

/**
 * @}
 */

#endif  // PNTR_STB_IMAGE_WRITE_H__

#ifdef PNTR_IMPLEMENTATION
#ifndef PNTR_STB_IMAGE_WRITE_IMPLEMENTATION
#define PNTR_STB_IMAGE_WRITE_IMPLEMENTATION

#ifndef PNTR_MEMMOVE
    #include <string.h>
    /**
     * Copies the values of num bytes from the location pointed by source to the memory block pointed by destination.
     *
     * @note If not defined, will use `memmove()`.
     *
     * @param destination Pointer to the destination array where the content is to be copied, type-casted to a pointer of type `void*`.
     * @param source Pointer to the source of data to be copied, type-casted to a pointer of type `const void*`.
     * @param num Number of bytes to copy.
     */
    #define PNTR_MEMMOVE(destination, source, num) memmove((destination), (source), (num))
#endif  // PNTR_MEMMOVE

#ifndef PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #define STBIW_MALLOC PNTR_MALLOC
    #define STBIW_REALLOC PNTR_REALLOC
    #define STBIW_FREE PNTR_FREE
    #define STBIW_MEMMOVE PNTR_MEMMOVE
    #define STBI_WRITE_NO_STDIO
    #define STBIW_ASSERT(x)
#endif  // PNTR_NO_STB_IMAGE_IMPLEMENTATION

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

#ifndef PNTR_STB_IMAGE_WRITE_H
#define PNTR_STB_IMAGE_WRITE_H "../external/stb_image_write.h"
#endif
#include PNTR_STB_IMAGE_WRITE_H

#ifndef PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
    #define PNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#ifdef STB_IMAGE_WRITE_IMPLEMENTATION
    #undef STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif // defined(__GNUC__) || defined(__clang__)

typedef struct pntr_stb_image_context {
    unsigned int dataSize;
    void* data;
} pntr_stb_image_context;

void pntr_stb_image_write_func(void *context, void *data, int size) {
    pntr_stb_image_context* ctx = (pntr_stb_image_context*)context;
    ctx->dataSize = (unsigned int)size;
    if (size == 0) {
        ctx->data = NULL;
    }
    else {
        // Copy the stb_image data, because stb_image will free() it afterwards.
        ctx->data = pntr_load_memory((size_t)size);
        pntr_memory_copy(ctx->data, data, (size_t)size);
    }
}

unsigned char* pntr_stb_image_save_image_to_memory(pntr_image* image, pntr_image_type type, unsigned int* dataSize) {
    const unsigned char* pixels = (const unsigned char*)pntr_image_to_pixelformat(image, NULL, PNTR_PIXELFORMAT_RGBA8888);
    if (pixels == NULL) {
        return NULL;
    }

    pntr_stb_image_context context;
    context.data = NULL;
    context.dataSize = 0;

    switch (type) {
        case PNTR_IMAGE_TYPE_UNKNOWN:
        case PNTR_IMAGE_TYPE_PNG: {
            int stride_bytes = pntr_get_pixel_data_size(image->width, 1, PNTR_PIXELFORMAT_RGBA8888);
            stbi_write_png_to_func(pntr_stb_image_write_func, &context, image->width, image->height, 4, pixels, stride_bytes);
        }
        break;
        case PNTR_IMAGE_TYPE_JPG: {
            stbi_write_jpg_to_func(pntr_stb_image_write_func, &context, image->width, image->height, 4, pixels, 100);
        }
        break;
        case PNTR_IMAGE_TYPE_BMP: {
            stbi_write_bmp_to_func(pntr_stb_image_write_func, &context, image->width, image->height, 4, pixels);
        }
        break;
        default:
            pntr_set_error(PNTR_ERROR_NOT_SUPPORTED);
        break;
    }

    pntr_unload_memory((void*)pixels);

    if (dataSize != NULL) {
        *dataSize = (unsigned int)context.dataSize;
    }

    return (unsigned char*)context.data;
}

#ifndef PNTR_SAVE_IMAGE_TO_MEMORY
#define PNTR_SAVE_IMAGE_TO_MEMORY pntr_stb_image_save_image_to_memory
#endif

#endif  // PNTR_STB_IMAGE_WRITE_IMPLEMENTATION
#endif  // PNTR_IMPLEMENTATION
