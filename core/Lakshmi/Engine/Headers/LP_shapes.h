#ifndef CORE_LAKSHMI_ENGINE_HEADERS_NG_SHAPES_H
#define CORE_LAKSHMI_ENGINE_HEADERS_NG_SHAPES_H

void draw_horizontal_stripes(float x_start, float x_end, float y_bottom, float y_top, float spacing,
                             float r, float g, float b, float cx, float cy, float sx, float sy);

void draw_pixel_roof_tier(float base_w, float top_w, float bottom_y, float top_y, int steps,
                          float r, float g, float b, float cx, float cy, float sx, float sy);

#endif // CORE_LAKSHMI_ENGINE_HEADERS_NG_SHAPES_H
