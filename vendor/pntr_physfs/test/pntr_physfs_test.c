#include <stdio.h>
#include <assert.h>

#include "physfs.h"

#define PNTR_PHYSFS_IMPLEMENTATION
#include "../pntr_physfs.h"

#define PNTR_IMPLEMENTATION
#include "pntr.h"

int main() {
    // Initialize PhysFS
    assert(PHYSFS_init(0) != 0);

    // Set the write directory.
    assert(PHYSFS_setWriteDir("resources") != 0);

    // Mount the resources directory as "res"
    assert(PHYSFS_mount("resources", "res", 1) != 0);

    // Load the image from the "res" mountpoint in PhysFS.
    pntr_image* image = pntr_load_image("res/image.png");
    assert(image != NULL);

    // Manipulate the image
    pntr_draw_circle_fill(image, image->width / 2, image->height / 2, 50, PNTR_BLUE);

    // Save the image, expecting it to write to resources/output.png
    assert(pntr_save_image(image, "output.png"));

    // Unload the image.
    pntr_unload_image(image);

    // Make sure the file was written correctly.
    FILE* file = fopen("resources/output.png", "r");
    assert(file != NULL);
    fclose(file);

    assert(PHYSFS_deinit() != 0);

    return 0;
}
