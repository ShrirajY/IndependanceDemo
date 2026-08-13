#include "../Headers/Ng_shapes.h"
#include <math.h>

#include <vector>
#include <utility> // std::pair
#include <cmath>

void Ng_drawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x2, y2, 0.0f);
    glEnd();
}

void Ng_drawRectangle(float x, float y, float width, float height)
{
    float leftX = x - (width / 2);
    float leftY = y + (height/2);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(leftX, leftY, 0.0f);
    glVertex3f(leftX + width, leftY, 0.0f);
    glVertex3f(leftX, leftY - height, 0.0f);
    glVertex3f(leftX + width, leftY - height, 0.0f);
    glEnd();
}

void Ng_drawCircle(float x, float y, float r)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for(int i = 0; i < 362; i++)
    {
        angle = PI / 180 * i;
        glVertex3f(x + r * cos(angle), y + r * sin(angle), 0.0f);
    }
    glEnd();
}


void Ng_drawEllipse(float x, float y, float a, float b)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for(int i = 0; i < 362; i++)
    {
        angle = 2 * PI / 180 * i;
        glVertex3f(x + a * cos(angle), y + b * sin(angle), 0.0f);
    }
    glEnd();
}

void Ng_drawCircularArc(float x, float y, float angle1, float angle2, float r)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for (int i = angle1; i < angle2; i++)
    {
        angle =  PI / 180 * i;
        glVertex3f(x + r * cos(angle), y + r * sin(angle), 0.0f);
    }
    glEnd();
}

void Ng_drawCircularArcGrad(float x, float y, float angle1, float angle2, float r,
                            float R1, float G1, float B1,
                            float R2, float G2, float B2)
{
    const int steps = (int)(angle2 - angle1);
    const float PI = 3.14159265f;

    float Rsteps = (steps != 0) ? (R2 - R1) / steps : 0.0f;
    float Gsteps = (steps != 0) ? (G2 - G1) / steps : 0.0f;
    float Bsteps = (steps != 0) ? (B2 - B1) / steps : 0.0f;

    float R = R1, G = G1, B = B1;

    glBegin(GL_TRIANGLE_FAN);

    glColor3f((R1 + R2) / 2.0f, (G1 + G2) / 2.0f, (B1 + B2) / 2.0f);          // <-- the missing line: give the center a real color
    glVertex3f(x, y, 0.0f);

    for (int i = 0; i <= steps; i++)   // <= so the last vertex actually reaches R2,G2,B2
    {
        glColor3f(R, G, B);
        float angle = PI / 180.0f * (angle1 + i);
        glVertex3f(x + r * cosf(angle), y + r * sinf(angle), 0.0f);
        R += Rsteps;
        G += Gsteps;
        B += Bsteps;
    }

    glEnd();
}

void Ng_drawEllipseArc(float x, float y, float angle1, float angle2, float a, float b)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for (int i = angle1; i < angle2 + 1; i++)
    {
        angle =  PI / 180 * i;
        glVertex3f(x + a * cos(angle), y + b * sin(angle), 0.0f);
    }
    glEnd();
}

void Ng_drawLineArc(float x, float y, float angle1, float angle2, float r, float PointSize)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glPointSize(PointSize);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = angle1; i < angle2 + 1; i++)
    {
        angle =  PI / 180 * i;
        glVertex3f(x + r * cos(angle), y + r * sin(angle), 0.0f);
    }
    glEnd();
}
void Ng_drawLineArcELlipse(float x, float y, float angle1, float angle2, float a, float b, float PointSize)
{
    const float PI = 3.14;
    float angle = 0.0f;
    glPointSize(PointSize);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = angle1; i < angle2 + 1; i++)
    {
        angle =  PI / 180 * i;
        glVertex3f(x + a * cos(angle), y + b * sin(angle), 0.0f);
    }
    glEnd();
}

void Ng_drawQuadraticBezier(float x0, float y0,
                            float x1, float y1,
                            float x2, float y2,
                            float pointSize)
{
    glEnable(GL_LINE_SMOOTH);


    glPointSize(pointSize);
    glBegin(GL_POINTS);

    for (float t = 0.0f; t <= 1.0f; t += 0.01f)
    {
        float u = 1.0f - t;

        float x = u * u * x0 +
                  2.0f * u * t * x1 +
                  t * t * x2;

        float y = u * u * y0 +
                  2.0f * u * t * y1 +
                  t * t * y2;

        glVertex2f(x, y);
    }

    glEnd();
}



void Ng_drawEquationLine(float slope, float c, float lineWidth)
{
    // Get the current viewport (for aspect ratio)
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float width  = (float)viewport[2];
    float height = (float)viewport[3];
    if (height <= 0) height = 1;
    float aspect = width / height;

    // Recompute the same bounds resize() used
    float xMin, xMax, yMin, yMax;
    if (aspect >= 1.0f)
    {
        xMin = -aspect; xMax = aspect;
        yMin = -1.0f;   yMax = 1.0f;
    }
    else
    {
        xMin = -1.0f; xMax = 1.0f;
        yMin = -1.0f / aspect; yMax = 1.0f / aspect;
    }

    // --- clip line to box ---
    float pts[4][2];
    int n = 0;

    float yAtXMin = slope * xMin + c;
    if (yAtXMin >= yMin && yAtXMin <= yMax) { pts[n][0] = xMin; pts[n][1] = yAtXMin; n++; }

    float yAtXMax = slope * xMax + c;
    if (yAtXMax >= yMin && yAtXMax <= yMax) { pts[n][0] = xMax; pts[n][1] = yAtXMax; n++; }

    if (slope != 0.0f)
    {
        float xAtYMin = (yMin - c) / slope;
        if (xAtYMin >= xMin && xAtYMin <= xMax) { pts[n][0] = xAtYMin; pts[n][1] = yMin; n++; }

        float xAtYMax = (yMax - c) / slope;
        if (xAtYMax >= xMin && xAtYMax <= xMax) { pts[n][0] = xAtYMax; pts[n][1] = yMax; n++; }
    }

    if (n < 2)
        return; // line doesn't cross the visible box at all

    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex3f(pts[0][0], pts[0][1], 0.0f);
    glVertex3f(pts[1][0], pts[1][1], 0.0f);
    glEnd();
}

void Ng_drawEquationLineClipped(float slope, float c, float lineWidth, float xMin, float xMax)
{
    // Get current viewport to derive aspect ratio -> yMin/yMax
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float width  = (float)viewport[2];
    float height = (float)viewport[3];
    if (height <= 0) height = 1;
    float aspect = width / height;

    float yMin, yMax;
    if (aspect >= 1.0f)
    {
        yMin = -1.0f;
        yMax = 1.0f;
    }
    else
    {
        yMin = -1.0f / aspect;
        yMax = 1.0f / aspect;
    }

    // --- clip line to box [xMin,xMax] x [yMin,yMax] ---
    float pts[4][2];
    int n = 0;

    float yAtXMin = slope * xMin + c;
    if (yAtXMin >= yMin && yAtXMin <= yMax) { pts[n][0] = xMin; pts[n][1] = yAtXMin; n++; }

    float yAtXMax = slope * xMax + c;
    if (yAtXMax >= yMin && yAtXMax <= yMax) { pts[n][0] = xMax; pts[n][1] = yAtXMax; n++; }

    if (slope != 0.0f)
    {
        float xAtYMin = (yMin - c) / slope;
        if (xAtYMin >= xMin && xAtYMin <= xMax) { pts[n][0] = xAtYMin; pts[n][1] = yMin; n++; }

        float xAtYMax = (yMax - c) / slope;
        if (xAtYMax >= xMin && xAtYMax <= xMax) { pts[n][0] = xAtYMax; pts[n][1] = yMax; n++; }
    }

    if (n < 2)
        return; // line doesn't cross the visible box at all

    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    glVertex3f(pts[0][0], pts[0][1], 0.0f);
    glVertex3f(pts[1][0], pts[1][1], 0.0f);
    glEnd();
}

void Ng_rotatePoint(float x, float y, float angle, float refX, float refY, float* x1, float* y1)
{
    angle = 3.14 / 180.0 * angle;


    x -= refX;
    y -= refY;

    *x1 = x * cos(angle) - y * sin(angle);
    *y1 = y * cos(angle) + x * sin(angle);

    *x1 += refX;
    *y1 += refY;
}


void Ng_drawRotatedRectangle(float x, float y, float width, float height, float angle)
{
    float cornersX[4] = { -width / 2,  width / 2,  width / 2, -width / 2 };
    float cornersY[4] = {  height / 2, height / 2, -height / 2, -height / 2 };

    float rx[4], ry[4];
    for (int i = 0; i < 4; i++)
        Ng_rotatePoint(x + cornersX[i], y + cornersY[i], angle, x, y, &rx[i], &ry[i]);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(rx[0], ry[0], 0.0f);
    glVertex3f(rx[1], ry[1], 0.0f);
    glVertex3f(rx[3], ry[3], 0.0f);
    glVertex3f(rx[2], ry[2], 0.0f);
    glEnd();
}

void Ng_DrawTransformedRectangle(Ng_Rectangle* rect)
{
    float x[4];
    float y[4];

    x[0] = rect->x - rect->width / 2;
    y[0] = rect->y + rect->height / 2;

    x[1] = rect->x + rect->width / 2;
    y[1] = rect->y + rect->height / 2;

    x[2] = rect->x + rect->width / 2;
    y[2] = rect->y - rect->height / 2;

    x[3] = rect->x - rect->width / 2;
    y[3] = rect->y - rect->height / 2;

    for(int i=0; i < 4; i++)
    {
        Ng_rotatePoint(x[i], y[i], rect->angle, rect->x, rect->y, &x[i], &y[i]);
    }

    for(int i = 0; i < 4; i++)
    {
        x[i] *= rect->sx;
        y[i] *= rect->sy;
    }

    for(int i=0; i < 4; i++)
    {
        x[i] += rect->tx;
        y[i] += rect->ty;
    }

    glBegin(GL_QUADS);
    for(int i=0; i < 4; i++)
    {
        glVertex3f(x[i], y[i], 0.0f);
    }
    glEnd();
}
