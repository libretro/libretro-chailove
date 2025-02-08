void pntr_examples_image() {
    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);
    pntr_image* image;
    pntr_image* resized;

    // Load an image
    image = pntr_load_image("resources/logo-128x128.png");

    // Resize the image
    resized = pntr_image_resize(image, image->width / 2, image->height / 2, PNTR_FILTER_NEARESTNEIGHBOR);

    // Draw an image on the canvas
    pntr_draw_image(canvas, image, 30, 30);

    // Draw a section of an image
    pntr_rectangle rect;
    rect.x = 25;
    rect.y = 16;
    rect.width = 65;
    rect.height = 58;
    pntr_draw_image_rec(canvas, image, rect, 170, 30);

    // Draw the resized image
    pntr_draw_image(canvas, resized, 170, 100);

    // Draw the resized image
    pntr_draw_image_flipped(canvas, image, 240, 30, true, false, true);

    pntr_save_image(canvas, "pntr_examples_image.png");

    pntr_unload_image(image);
    pntr_unload_image(resized);
    pntr_unload_image(canvas);
}
