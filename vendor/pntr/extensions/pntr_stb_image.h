#ifndef PNTR_STB_IMAGE_H__
#define PNTR_STB_IMAGE_H__

/**
 * @defgroup pntr_stb_image pntr_stb_image
 * @{
 *
 * @brief [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) integration with pntr for loading images. This is the default behavior.
 *
 * To use *stb_image* for loading images, define `PNTR_STB_IMAGE` prior to including `pntr.h`. This is provided by default.
 *
 * @code
 * #define PNTR_STB_IMAGE
 * #define PNTR_IMPLEMENTATION
 * #include "pntr.h"
 * @endcode
 *
 * Image loading can be completely disabled with `PNTR_NO_LOAD_IMAGE`.
 *
 * @see https://github.com/nothings/stb/blob/master/stb_image.h
 * @see PNTR_STB_IMAGE
 * @see PNTR_LOAD_IMAGE_FROM_MEMORY
 * @see PNTR_NO_LOAD_IMAGE
 */

/**
 * Load an image using stb_image.
 */
pntr_image* pntr_stb_image_load_image_from_memory(pntr_image_type type, const unsigned char *fileData, unsigned int dataSize);

/**
 * @}
 */

#endif  // PNTR_STB_IMAGE_H__

#ifdef PNTR_IMPLEMENTATION
#ifndef PNTR_STB_IMAGE_IMPLEMENTATION
#define PNTR_STB_IMAGE_IMPLEMENTATION

#ifndef PNTR_NO_STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
    #define STBI_MALLOC PNTR_MALLOC
    #define STBI_REALLOC PNTR_REALLOC
    #define STBI_FREE PNTR_FREE
    #define STBI_NO_HDR
    #define STBI_NO_FAILURE_STRINGS
    #define STBI_NO_STDIO
    #define STBI_NO_SIMD
    #define STBI_NO_THREAD_LOCALS
    #ifndef PNTR_ENABLE_JPEG
        #define STBI_NO_JPEG // JPG support in stb_image.
    #endif
    //#define STBI_NO_PNG
    #define STBI_NO_BMP
    #define STBI_NO_PSD
    #define STBI_NO_TGA
    #define STBI_NO_GIF
    #define STBI_NO_HDR
    #define STBI_NO_PIC
    #define STBI_NO_PNM
    //#define STBI_SUPPORT_ZLIB
    #define STBI_NO_LINEAR

    #define STBI_ASSERT(x)
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

#ifndef PNTR_STB_IMAGE_H
#define PNTR_STB_IMAGE_H "../external/stb_image.h"
#endif
#include PNTR_STB_IMAGE_H

#ifndef PNTR_NO_STB_IMAGE_IMPLEMENTATION
    #define PNTR_NO_STB_IMAGE_IMPLEMENTATION
#endif
#ifdef STB_IMAGE_IMPLEMENTATION
    #undef STB_IMAGE_IMPLEMENTATION
#endif

#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic pop
#endif // defined(__GNUC__) || defined(__clang__)

pntr_image* pntr_stb_image_load_image_from_memory(pntr_image_type type, const unsigned char *fileData, unsigned int dataSize) {
    // We don't need to use the type, as stb_image will figure that out for us.
    (void)type;

    int x, y, channels_in_file;
    int desired_channels = 4;
    stbi_uc *data = stbi_load_from_memory((stbi_uc const *)fileData, (int)dataSize, &x, &y, &channels_in_file, desired_channels);
    if (data == NULL) {
        return NULL;
    }

    pntr_image* output = pntr_image_from_pixelformat(data, x, y, PNTR_PIXELFORMAT_RGBA8888);
    stbi_image_free(data);

    return output;
}

#ifdef PNTR_LOAD_IMAGE_FROM_MEMORY
#undef PNTR_LOAD_IMAGE_FROM_MEMORY
#endif

#define PNTR_LOAD_IMAGE_FROM_MEMORY pntr_stb_image_load_image_from_memory

#endif  // PNTR_STB_IMAGE_IMPLEMENTATION
#endif  // PNTR_IMPLEMENTATION
