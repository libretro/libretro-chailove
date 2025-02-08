void pntr_examples_sprite() {
    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);

    // Load the image
    pntr_image* scarfy = pntr_load_image("resources/scarfy.png");

    pntr_rectangle frameRec;
    frameRec.x = 0;
    frameRec.y = 0;
    frameRec.width = scarfy->width / 6;
    frameRec.height = scarfy->height;

    frameRec.x = 1 * (float)scarfy->width / 6;
    pntr_draw_image_rec(canvas, scarfy, frameRec, 10, canvas->height / 2 - frameRec.height / 2);

    frameRec.x = 3 * (float)scarfy->width / 6;
    pntr_draw_image_rec(canvas, scarfy, frameRec, 120, canvas->height / 2 - frameRec.height / 2);

    frameRec.x = 5 * (float)scarfy->width / 6;
    pntr_draw_image_rec(canvas, scarfy, frameRec, 250, canvas->height / 2 - frameRec.height / 2);

    pntr_save_image(canvas, "pntr_examples_sprite.png");

    pntr_unload_image(scarfy);
    pntr_unload_image(canvas);
}
