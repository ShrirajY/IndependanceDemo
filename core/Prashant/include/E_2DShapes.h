#pragma once

#include <GL/freeglut.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef MAX_TEETH
#define MAX_TEETH 16
#endif

typedef struct Quad {
    float x;
    float y;
    float length;
    float breadth;
    float scale;
    int colorVal;
}Quad;


// Drawing Utilities
extern void drawCircle(float localCX, float localCY, float radius, float tx, float ty, float scale, float angle, int choice_color);
extern void drawLegSegment(float localX1, float localY1, float localX2, float localY2, float tx, float ty, float scale, float angle, float width);
extern void getPivotedPoint(float x, float y, float baseX, float baseY, float swingAngle, float* outX, float* outY);
extern void drawLeg(
	float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3,
	float x4, float y4,
	float tx, float ty, float scale, float worldAngle, float swingAngle,
	float w1, float w2, float w3, float w4);
extern void drawQuad(int color_val, float x, float y, float length, float breadth, float scale);
extern Quad createQuad(float x, float y, float length, float breadth, float scale, int colorVal);
extern void drawQuadObj(const Quad& q);

void drawQuad(float x, float y, float length, float width, float r, float g, float b);