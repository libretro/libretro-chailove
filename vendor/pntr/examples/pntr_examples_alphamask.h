void pntr_examples_alphamask() {
    // Load the Tuffy font, and find the size of the text output.
    pntr_font* font = pntr_load_font_ttf("resources/tuffy.ttf", 80);
    pntr_vector textSize = pntr_measure_text_ex(font, "Alpha Mask!", 0);

    // Create a background to use as the alphamask.
    pntr_image* output = pntr_gen_image_gradient(textSize.x, textSize.y, PNTR_RED, PNTR_DARKGREEN, PNTR_BLUE, PNTR_PURPLE);

    // Create an alpha mask of text
    pntr_image* imageText = pntr_gen_image_text(font, "Alpha Mask!", PNTR_WHITE, PNTR_BLANK);

    // Apply the alpha mask to the image.
    pntr_image_alpha_mask(output, imageText, 0, 0);

    pntr_save_image(output, "pntr_examples_alphamask.png");

    // Clean up
    pntr_unload_font(font);
    pntr_unload_image(imageText);
    pntr_unload_image(output);
}
