void pntr_examples_resize() {
    float size = 0.5f;
    pntr_image* originalImage = pntr_load_image("resources/logo-128x128.png");

    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);

    pntr_draw_image(canvas, originalImage, 10, 10);

    pntr_draw_image_scaled(canvas, originalImage,
        canvas->width / 4 - originalImage->width * size / 2.0f,
        canvas->height / 2 - originalImage->height * size / 2.0f,
        size, size, 0.0f, 0.0f, PNTR_FILTER_NEARESTNEIGHBOR);

    pntr_draw_image_scaled(canvas, originalImage,
        canvas->width / 2 + canvas->width / 4 - originalImage->width * size / 2.0f,
        canvas->height / 2 - originalImage->height * size / 2.0f,
        size, size, 0.0f, 0.0f, PNTR_FILTER_BILINEAR);

    pntr_draw_image_scaled(canvas, originalImage,
        canvas->width / 2  - originalImage->width * 0.75f / 2.0f,
        canvas->height / 2 - originalImage->height * 0.75f / 2.0f,
        0.75f, 0.75, 0.0f, 0.0f, PNTR_FILTER_NEARESTNEIGHBOR);

    pntr_save_image(canvas, "pntr_examples_resize.png");

    pntr_unload_image(originalImage);
    pntr_unload_image(canvas);
}
