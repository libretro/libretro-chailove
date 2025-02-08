void pntr_examples_thick() {
    pntr_image* canvas = pntr_gen_image_color(400, 225, PNTR_RAYWHITE);

    // Rectangles
    pntr_draw_rectangle_thick(canvas, 10, 120, 50, 50, 5, PNTR_RED);
    pntr_draw_rectangle_thick(canvas, 20, 130, 50, 50, 5, PNTR_GREEN);
    pntr_draw_rectangle_thick(canvas, 30, 140, 50, 50, 5, PNTR_BLUE);

    // Circle
    pntr_draw_circle_thick(canvas, 110, 60, 21, 10, PNTR_RED);

    pntr_draw_ellipse_thick(canvas, 110, 100, 20, 10, 8, PNTR_GREEN);

    // Line
    pntr_draw_line_thick(canvas, 150, 30, 230, 60, 8, PNTR_DARKGREEN);

    // Triangle
    pntr_draw_triangle_thick(canvas,
        250, 50,
        300, 80,
        350, 20, 5, PNTR_PURPLE);

    // Polygon
    pntr_vector points[10];
    points[0] = PNTR_CLITERAL(pntr_vector) {210, 110};
    points[1] = PNTR_CLITERAL(pntr_vector) {215, 130};
    points[2] = PNTR_CLITERAL(pntr_vector) {240, 140};
    points[3] = PNTR_CLITERAL(pntr_vector) {200, 160};
    pntr_draw_polygon_thick(canvas, points, 4, 5, PNTR_BLACK);

    // Arc
    int radius = 80;
    pntr_draw_arc_thick(canvas, 350, 120, radius, 90.0f, 180.0f, radius * 1.5f, 12, PNTR_RED);

    // Polyline
    points[0] = PNTR_CLITERAL(pntr_vector) {240, 80};
    points[1] = PNTR_CLITERAL(pntr_vector) {260, 100};
    points[2] = PNTR_CLITERAL(pntr_vector) {220, 110};
    points[3] = PNTR_CLITERAL(pntr_vector) {240, 130};
    pntr_draw_polyline_thick(canvas, points, 4, 5, PNTR_PURPLE);

    // Line Curve
    pntr_draw_line_curve_thick(canvas, points[0], points[1], points[2], points[3], 40, 5, PNTR_DARKBLUE);

    // Vertical line
    pntr_draw_line_vertical_thick(canvas, 20, 20, 80, 12, PNTR_ORANGE);

    // Horizontal line
    pntr_draw_line_horizontal_thick(canvas, 40, 20, 80, 12, PNTR_DARKBROWN);

    pntr_save_image(canvas, "pntr_examples_thick.png");
    pntr_unload_image(canvas);
}
