#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawEllipse(float centerX, float centerY, float rx, float ry, float angleDegree, float scale) {
    float radAngle = angleDegree * M_PI / 180.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center vertex of the fan
    for (int i = 0; i <= 360; i++) {
        float stepRad = i * M_PI / 180.0f;
        
        float localX = cos(stepRad) * rx * scale;
        float localY = sin(stepRad) * ry * scale;

        float rotatedX = localX * cos(radAngle) - localY * sin(radAngle);
        float rotatedY = localX * sin(radAngle) + localY * cos(radAngle);

        glVertex2f(centerX + rotatedX, centerY + rotatedY);
    }
    glEnd();
}

void drawQuarterNote(float cx, float cy, float scale) {
    //glColor3f(1.0f, 1.0f, 1.0f); // White color
    glColor3f(1.0f, 0.75f, 0.15f);
    drawEllipse(cx, cy, 0.08f, 0.05f, 30.0f, scale);

    float stemOffsetX = 0.07f * scale;
    float stemHeight = 0.35f * scale;

    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glEnd();
}

void drawSlantedBeamedNotes(float cx, float cy, float scale) {
    //glColor3f(1.0f, 1.0f, 1.0f); // White color
    glColor3f(1.0f, 0.75f, 0.15f);
    float dx = 0.25f * scale;
    float dy = 0.10f * scale;
    float stemOffsetX = 0.07f * scale;
    float stemHeight = 0.35f * scale;

    drawEllipse(cx, cy, 0.08f, 0.05f, 30.0f, scale);
    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glEnd();

    drawEllipse(cx + dx, cy + dy, 0.08f, 0.05f, 30.0f, scale);
    glBegin(GL_LINES);
    glVertex2f(cx + dx + stemOffsetX, cy + dy);
    glVertex2f(cx + dx + stemOffsetX, cy + dy + stemHeight);
    glEnd();

    glBegin(GL_QUADS);
    float beamThickness = 0.04f * scale;
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glVertex2f(cx + dx + stemOffsetX, cy + dy + stemHeight);
    glVertex2f(cx + dx + stemOffsetX, cy + dy + stemHeight - beamThickness);
    glVertex2f(cx + stemOffsetX, cy + stemHeight - beamThickness);
    glEnd();
}

void drawHalfNote(float cx, float cy, float scale) {
    //glColor3f(1.0f, 1.0f, 1.0f); // White color
    glColor3f(1.0f, 0.75f, 0.15f);

    float rx = 0.08f * scale;
    float ry = 0.05f * scale;
    float stemOffsetX = 0.07f * scale;
    float stemHeight = 0.35f * scale;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        float x = cx + cos(angle) * rx;
        float y = cy + sin(angle) * ry;
        glVertex2f(x, y);
    }
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glEnd();
}

void drawSharpNote(float cx, float cy, float scale) {
    //glColor3f(1.0f, 1.0f, 1.0f); // White color
    glColor3f(1.0f, 0.75f, 0.15f);

    drawEllipse(cx, cy, 0.08f, 0.05f, 30.0f, scale);

    float stemOffsetX = 0.07f * scale;
    float stemHeight = 0.35f * scale;
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glEnd();

    float sharpOffsetX = -0.20f * scale;
    float lineWidth = 0.06f * scale;

    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(cx + sharpOffsetX, cy - 0.08f * scale);
    glVertex2f(cx + sharpOffsetX, cy + 0.12f * scale);
    glVertex2f(cx + sharpOffsetX + lineWidth, cy - 0.08f * scale);
    glVertex2f(cx + sharpOffsetX + lineWidth, cy + 0.12f * scale);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(cx + sharpOffsetX - 0.02f * scale, cy - 0.01f * scale);
    glVertex2f(cx + sharpOffsetX + lineWidth + 0.02f * scale, cy - 0.01f * scale);
    glVertex2f(cx + sharpOffsetX - 0.02f * scale, cy + 0.06f * scale);
    glVertex2f(cx + sharpOffsetX + lineWidth + 0.02f * scale, cy + 0.06f * scale);
    glEnd();
}

void drawBeamedEighthNotes(float cx, float cy, float scale) {
    //glColor3f(1.0f, 1.0f, 1.0f); // White color
    glColor3f(1.0f, 0.75f, 0.15f);

    float dx = 0.2f * scale;
    float stemOffsetX = 0.07f * scale;
    float stemHeight = 0.3f * scale;

    drawEllipse(cx, cy, 0.08f, 0.05f, 30.0f, scale);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glEnd();

    drawEllipse(cx + dx, cy, 0.08f, 0.05f, 30.0f, scale);
    glBegin(GL_LINES);
    glVertex2f(cx + dx + stemOffsetX, cy);
    glVertex2f(cx + dx + stemOffsetX, cy + stemHeight);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(cx + stemOffsetX, cy + stemHeight);
    glVertex2f(cx + dx + stemOffsetX, cy + stemHeight);
    glEnd();
}