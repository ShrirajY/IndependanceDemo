#include <GL/glut.h>
#include "../Headers/LP_shapes.h"

void draw_horizontal_stripes(float x_start, float x_end, float y_bottom, float y_top, float spacing,
                             float r, float g, float b, float cx, float cy, float sx, float sy) {
    glColor3f(r, g, b);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (float y = y_bottom; y <= y_top; y += spacing) {
        glVertex2f(cx + x_start * sx, cy + y * sy);
        glVertex2f(cx + x_end * sx,   cy + y * sy);
    }
    glEnd();
}

void draw_pixel_roof_tier(float base_w, float top_w, float bottom_y, float top_y, int steps,
                          float r, float g, float b, float cx, float cy, float sx, float sy) {
    float h = (top_y - bottom_y) / steps;
    for (int i = 0; i < steps; i++) {
        float y1 = bottom_y + (i * h);
        float y2 = y1 + h;
        float t1 = (float)i / steps;
        float t2 = (float)(i + 1) / steps;
        float w1 = base_w - (base_w - top_w) * t1;
        float w2 = base_w - (base_w - top_w) * t2;

        glColor3f(r, g, b);
        glBegin(GL_QUADS);
            glVertex2f(cx - w1 * sx, cy + y1 * sy);
            glVertex2f(cx + w1 * sx, cy + y1 * sy);
            glVertex2f(cx + w2 * sx, cy + y2 * sy);
            glVertex2f(cx - w2 * sx, cy + y2 * sy);
        glEnd();

        glColor3f(r * 0.75f, g * 0.7f, b * 0.75f);
        glBegin(GL_LINES);
            glVertex2f(cx - w1 * sx, cy + y1 * sy);
            glVertex2f(cx + w1 * sx, cy + y1 * sy);
        glEnd();
    }
}
