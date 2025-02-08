/**
 * @page Examples Examples
 *
 * @brief These are a few examples of pntr in use.
 *
 * ## Alpha Mask
 * @include pntr_examples_alphamask.h
 * @image html pntr_examples_alphamask.png
 *
 * ## Fonts
 * @include pntr_examples_fonts.h
 * @image html pntr_examples_fonts.png
 *
 * ## Image
 * @include pntr_examples_image.h
 * @image html pntr_examples_image.png
 *
 * ## Resize
 * @include pntr_examples_resize.h
 * @image html pntr_examples_resize.png
 *
 * ## Rotate
 * @include pntr_examples_rotate.h
 * @image html pntr_examples_rotate.png
 *
 * ## Shapes
 * @include pntr_examples_shapes.h
 * @image html pntr_examples_shapes.png
 *
 * ## Sprite
 * @include pntr_examples_sprite.h
 * @image html pntr_examples_sprite.png
 *
 * ## Thick
 * @include pntr_examples_thick.h
 * @image html pntr_examples_thick.png
 */

#ifndef _DOXYGEN_

#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_ENABLE_TTF
#define PNTR_ENABLE_UTF8
#define PNTR_ENABLE_VARGS

// Math: Link the m library to use math.h
//#define PNTR_ENABLE_MATH

#define PNTR_IMPLEMENTATION
#include "../pntr.h"

#include "pntr_examples_alphamask.h"
#include "pntr_examples_fonts.h"
#include "pntr_examples_image.h"
#include "pntr_examples_resize.h"
#include "pntr_examples_rotate.h"
#include "pntr_examples_shapes.h"
#include "pntr_examples_sprite.h"
#include "pntr_examples_thick.h"

int main(int argc, char* argv[]) {
    pntr_examples_alphamask();
    pntr_examples_fonts();
    pntr_examples_image();
    pntr_examples_resize();
    pntr_examples_rotate();
    pntr_examples_shapes();
    pntr_examples_sprite();
    pntr_examples_thick();

    return 0;
}

#endif
