void pntr_examples_rotate() {
    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);

    pntr_image* imageToRotate = pntr_load_image("resources/logo-128x128.png");

    // Draw the image rotated on screen using a nearest neighbor filter.
    pntr_draw_image_rotated(canvas, imageToRotate, 10, canvas->height / 2, 0.0f, 0, imageToRotate->height / 2.0f, PNTR_FILTER_NEARESTNEIGHBOR);

    // Draw the rotated image on the screen with a smooth filter.
    pntr_draw_image_rotated(canvas, imageToRotate, 140, canvas->height / 2, 32.0f, 0, imageToRotate->height / 2.0f, PNTR_FILTER_BILINEAR);

    // Draw the rotated image on the screen with a smooth filter.
    pntr_draw_image_rotated(canvas, imageToRotate, 280, canvas->height / 2, 180.0f, 0, imageToRotate->height / 2.0f, PNTR_FILTER_BILINEAR);

    pntr_save_image(canvas, "pntr_examples_rotate.png");

    pntr_unload_image(imageToRotate);
    pntr_unload_image(canvas);
}
