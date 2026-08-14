#include <GL/freeglut.h>
#include <iostream>
void Ng_drawRectangle(float x, float y, float width, float height);

void Ng_drawCircle(float x, float y, float r);

void Ng_drawEllipse(float x, float y, float a, float b);

void Ng_drawCircularArc(float x, float y, float angle1, float angle2, float r);

void Ng_drawEllipseArc(float x, float y, float angle1, float angle2, float a, float b);

void Ng_drawLine(float x1, float y1, float x2, float y2, float lineWidth);

void Ng_drawLineArc(float x, float y, float angle1, float angle2, float r, float pointSize);

void Ng_drawQuadraticBezier(float x0, float y0,
                            float x1, float y1,
                            float x2, float y2,
                            float pointSize);

void Ng_drawCircularArcGrad(float x, float y, float angle1, float angle2, float r, float R1, float G1, float B1, float R2, float G2, float B2);

void Ng_drawEquationLine(float slope, float c, float lineWidth);

void Ng_drawEquationLineClipped(float slope, float c, float lineWidth, float xMin, float xMax);

void Ng_drawRotatedRectangle(float x, float y, float width, float height, float angle);

void Ng_rotatePoint(float x, float y, float angle, float refX, float refY, float* x1, float* y1);

typedef struct Ng_Rectangle{
    float x;
    float y;
    float angle;
    float tx;
    float ty;
    float sx;
    float sy;
    float width;
    float height;
}Ng_Rectangle;

void Ng_DrawTransformedRectangle(Ng_Rectangle* rect);

void Ng_drawLineArcELlipse(float x, float y, float angle1, float angle2, float a, float b, float PointSize);