#include "../include/E_2DShapes.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawCircle(float localCX, float localCY, float radius, float tx, float ty, float scale, float angle, int choice_color)
{
	glBegin(GL_POLYGON);

	switch (choice_color)
	{
	case 1:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case 2:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	default:
		glColor3f(1.0f, 0.0f, 0.0f);
	}

	float radAngle = angle * (3.1415926535f / 180.0f);
	float c = cosf(radAngle);
	float s = sinf(radAngle);

	for (int i = 0; i <= 360; i++)
	{
		float rad = i * (3.1415926535f / 180.0f);

		float localX = localCX + radius * cosf(rad);
		float localY = localCY + radius * sinf(rad);

		float sx = localX * scale;
		float sy = localY * scale;

		glVertex3f((sx * c - sy * s) + tx, (sx * s + sy * c) + ty, 0.0f);
	}

	glEnd();
}

void drawLegSegment(float localX1, float localY1, float localX2, float localY2, float tx, float ty, float scale, float angle, float width)
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	float radAngle = angle * (3.1415926535f / 180.0f);
	float c = cosf(radAngle);
	float s = sinf(radAngle);

	float sx1 = localX1 * scale;
	float sy1 = localY1 * scale;
	glVertex2f((sx1 * c - sy1 * s) + tx, (sx1 * s + sy1 * c) + ty);

	float sx2 = localX2 * scale;
	float sy2 = localY2 * scale;
	glVertex2f((sx2 * c - sy2 * s) + tx, (sx2 * s + sy2 * c) + ty);

	glEnd();
	glLineWidth(1.0f);
}

void getPivotedPoint(float x, float y, float baseX, float baseY, float swingAngle, float* outX, float* outY)
{
	float rad = swingAngle * (3.1415926535f / 180.0f);
	float c = cosf(rad);
	float s = sinf(rad);

	*outX = (x - baseX) * c - (y - baseY) * s + baseX;
	*outY = (x - baseX) * s + (y - baseY) * c + baseY;
}

Quad createQuad(float x, float y, float length, float breadth, float scale, int colorVal)
{
	Quad q;
	q.x = x;
	q.y = y;
	q.length = length;
	q.breadth = breadth;
	q.scale = scale;
	q.colorVal = colorVal;
	return q;
}

void drawQuadObj(const Quad& q)
{
	float halfL = q.length / 2.0f;
	float halfB = q.breadth / 2.0f;

	float x1 = -halfL, y1 = -halfB;
	float x2 = halfL, y2 = -halfB;
	float x3 = halfL, y3 = halfB;
	float x4 = -halfL, y4 = halfB;

	glBegin(GL_QUADS);

	switch (q.colorVal)
	{
	case 1:  glColor3f(0.016f, 0.816f, 1.0f);  break;
	case 2:  glColor3f(0.0f, 0.608f, 0.749f); break;
	case 3:  glColor3f(0.31f, 0.329f, 0.329f); break;
	case 4:  glColor3f(1.0f, 0.584f, 0.184f); break;
	case 5:  glColor3f(0.871f, 0.42f, 0.016f); break;
	case 6:  glColor3f(0.871f, 0.42f, 0.016f); break;
	case 7:  glColor3f(1.0f, 0.686f, 0.404f); break;
	case 8:  glColor3f(1.0f, 0.741f, 0.51f);  break;
	case 10: glColor3f(0.25f, 0.35f, 0.20f); break;
	case 11: glColor3f(0.18f, 0.26f, 0.15f); break;
	case 12: glColor3f(0.12f, 0.14f, 0.12f); break;
	case 13: glColor3f(0.40f, 0.42f, 0.38f); break;
	case 14: glColor3f(0.76f, 0.69f, 0.50f); break;
	default: glColor3f(1.0f, 0.0f, 0.0f);  break;
	}

	glVertex2f((x1 * q.scale) + q.x, (y1 * q.scale) + q.y);
	glVertex2f((x2 * q.scale) + q.x, (y2 * q.scale) + q.y);
	glVertex2f((x3 * q.scale) + q.x, (y3 * q.scale) + q.y);
	glVertex2f((x4 * q.scale) + q.x, (y4 * q.scale) + q.y);

	glEnd();
}

void drawQuadOutline(const Quad& q)
{
	float halfL = q.length / 2.0f;
	float halfB = q.breadth / 2.0f;

	float x1 = -halfL, y1 = -halfB;
	float x2 = halfL, y2 = -halfB;
	float x3 = halfL, y3 = halfB;
	float x4 = -halfL, y4 = halfB;

	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);

	switch (q.colorVal)
	{
	case 1:  glColor3f(0.016f, 0.816f, 1.0f);  break;
	case 2:  glColor3f(0.0f, 0.608f, 0.749f); break;
	case 3:  glColor3f(0.31f, 0.329f, 0.329f); break;
	case 4:  glColor3f(1.0f, 0.584f, 0.184f); break;
	case 5:  glColor3f(0.871f, 0.42f, 0.016f); break;
	case 6:  glColor3f(0.871f, 0.42f, 0.016f); break;
	case 7:  glColor3f(1.0f, 0.686f, 0.404f); break;
	case 8:  glColor3f(1.0f, 0.741f, 0.51f);  break;
	case 10: glColor3f(0.25f, 0.35f, 0.20f); break;
	case 11: glColor3f(0.18f, 0.26f, 0.15f); break;
	case 12: glColor3f(0.12f, 0.14f, 0.12f); break;
	case 13: glColor3f(0.40f, 0.42f, 0.38f); break;
	case 14: glColor3f(0.76f, 0.69f, 0.50f); break;
	default: glColor3f(1.0f, 0.0f, 0.0f);  break;
	}

	glVertex2f((x1 * q.scale) + q.x, (y1 * q.scale) + q.y);
	glVertex2f((x2 * q.scale) + q.x, (y2 * q.scale) + q.y);
	glVertex2f((x3 * q.scale) + q.x, (y3 * q.scale) + q.y);
	glVertex2f((x4 * q.scale) + q.x, (y4 * q.scale) + q.y);

	glEnd();
}

void drawLeg(
	float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3,
	float x4, float y4,
	float tx, float ty, float scale, float worldAngle, float swingAngle,
	float w1, float w2, float w3, float w4
)
{
	float px1, py1, px2, py2, px3, py3, px4, py4;

	getPivotedPoint(x1, y1, x0, y0, swingAngle, &px1, &py1);
	getPivotedPoint(x2, y2, x0, y0, swingAngle, &px2, &py2);
	getPivotedPoint(x3, y3, x0, y0, swingAngle, &px3, &py3);
	getPivotedPoint(x4, y4, x0, y0, swingAngle, &px4, &py4);

	drawLegSegment(x0, y0, px1, py1, tx, ty, scale, worldAngle, w1);
	drawLegSegment(px1, py1, px2, py2, tx, ty, scale, worldAngle, w2);
	drawLegSegment(px2, py2, px3, py3, tx, ty, scale, worldAngle, w3);
	drawLegSegment(px3, py3, px4, py4, tx, ty, scale, worldAngle, w4);
}

void drawPointedArch(float x0, float y0, float width,
	float rectHeight, float archHeight,
	int segments, bool isFilled
)
{
	GLenum mode = isFilled ? GL_POLYGON : GL_LINE_LOOP;
	float halfW = width / 2.0f;

	glBegin(mode);

	// 1. Bottom-Left Corner
	glVertex2f(x0 - halfW, y0);

	// 2. Bottom-Right Corner
	glVertex2f(x0 + halfW, y0);

	// 3. Right Arc
	for (int i = 0; i <= segments; ++i) {
		float t = (float)i / segments;
		float angle = t * (M_PI / 2.0f);
		float x = x0 + halfW * std::cos(angle);
		float y = y0 + rectHeight + archHeight * std::sin(angle);
		glVertex2f(x, y);
	}

	// 4. Left Arc
	for (int i = 1; i <= segments; ++i) {
		float t = 1.0f - ((float)i / segments);
		float angle = t * (M_PI / 2.0f);
		float x = x0 - halfW * std::cos(angle);
		float y = y0 + rectHeight + archHeight * std::sin(angle);
		glVertex2f(x, y);
	}

	glEnd();
}

void drawQuad(float x, float y, float length, float width, float r, float g, float b)
{
	// Calculate half extents from the center point
	float halfL = length / 2.0f;
	float halfW = width / 2.0f;

	// Bind the color state directly
	glColor3f(r, g, b);

	// Plot the primitive
	glBegin(GL_QUADS);
	glVertex2f(x - halfL, y - halfW); // Bottom-Left
	glVertex2f(x + halfL, y - halfW); // Bottom-Right
	glVertex2f(x + halfL, y + halfW); // Top-Right
	glVertex2f(x - halfL, y + halfW); // Top-Left
	glEnd();
}