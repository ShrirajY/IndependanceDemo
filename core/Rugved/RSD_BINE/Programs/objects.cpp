#include <GL/freeglut.h>
#include <math.h>
#include <cstdlib>
#include <ctime> 
#include <core/Utils.h>
#include <core/Rugved/RSD_BINE/Headers/shapes.h>

void background(float x, float y, float tx, float ty, float scaleFactor, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(-x + tx * scaleFactor,  y + ty * scaleFactor);
	glVertex2f( x + tx * scaleFactor,  y + ty * scaleFactor);
	glVertex2f( x + tx * scaleFactor, -y + ty * scaleFactor);
	glVertex2f(-x + tx * scaleFactor, -y + ty * scaleFactor);
	glEnd();
}

void windowTexture(float x, float y, float tx, float ty, float scaleFactor, float r, float g, float b)
{
	drawQuad(0.05f, 0.1f,  tx, ty, 0.9f, 0.6f, 0.3f);
	drawQuad(0.02f, 0.05f, tx, ty, 0.2f, 0.1f, 0.0f);
}

void pillarTexture(float x, float y, float tx, float ty, float scaleFactor, float r, float g, float b)
{
	drawQuad(0.01f, 0.12f, tx + 0.05f, ty + 0.01f, 0.1f, 0.1f, 0.0f);
	drawQuad(0.015f, 0.02f, tx + 0.05f, ty + 0.07f, 0.1f, 0.1f, 0.0f);
	drawQuad(0.015f, 0.02f, tx + 0.05f, ty - 0.07f, 0.1f, 0.1f, 0.0f);
	drawTriangle(0.03f, -0.02f, tx + 0.05f, ty + 0.11f, 1.0f, 0.1f, 0.1f, 0.0f);
}

void nandiTexture(float x, float y, float tx, float ty, float scaleFactor, float r, float g, float b)
{
	drawRATriangle(x, y, tx, ty, 1.0f, 0.8f, 0.4f, 0.2f);
	drawEllipse(x - 0.012f, -y + 0.01f, 0.012f, tx, ty + 0.03f, 0.8f, 0.4f, 0.2f);
}

// updating to push

