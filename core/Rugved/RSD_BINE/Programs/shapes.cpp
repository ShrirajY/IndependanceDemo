#include <GL/freeglut.h>
#include "core/Utils.h"
#include <math.h>
#include <cstdlib>
#include <ctime> 

#define pi 3.14159265358979323846

void drawQuadOC(float x, float y, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);
	glVertex3f(-x/2 + tx,  y/2 + ty, 0.0f);		// top left
	glVertex3f(-x/2 + tx, -y/2 + ty, 0.0f);		// bottom left
	glVertex3f( x/2 + tx,  y/2 + ty, 0.0f);		// top right
	glVertex3f( x/2 + tx, -y/2 + ty, 0.0f);		// bottom right
	glEnd();
}

void drawTestOC(float x, float y, float angle, float tx, float ty, float r, float g, float b)
{
	float sinA, cosA;
	sinA = sin(angle * (pi/180));
	cosA = cos(angle * (pi/180));
	float dx[4] = { -x, x, x, -x };
	float dy[4] = { y, y, -y, -y };

	glBegin(GL_QUADS);
	{
		glColor3f(r, g, b);
		for (int i = 0; i <= 4; i++)
		{
			float radX = 0;
			float radY = 0;
			radX = ((dx[i] * cosA) - (dy[i] * sinA)) + tx;
			radY = ((dx[i] * sinA) + (dy[i] * cosA)) + ty;

			glVertex3f(radX, radY, 0.0f);
		}
	}
	glEnd();
	

	//glBegin(GL_TRIANGLE_STRIP);
	//glColor3f(r, g, b);
	//glVertex3f(-x/2 + tx,  y/2 + ty, 0.0f);		// top left
	//glVertex3f(-x/2 + tx, -y/2 + ty, 0.0f);		// bottom left
	//glVertex3f( x/2 + tx,  y/2 + ty, 0.0f);		// top right
	//glVertex3f( x/2 + tx, -y/2 + ty, 0.0f);		// bottom right
	//glEnd();
}

void drawRotatingQuad(float x, float y, float theta, float tx, float ty, float r, float g, float b)
{

	// xnew = (x-tx)cos(x) - (y-ty)sin(x) + tx

	float x1, y1;

	x1 = (x - tx) * cos(theta) - (y - ty) * sin(theta) + tx;
	y1 = (x - tx) * sin(theta) + (y - ty) * cos(theta) + ty;

	//float radX = theta * pi/180; 
	//float radY = theta * pi/180;

	//float rotX = x * cos(radX) - y * sin(radX);
	//float rotY = y * cos(radY) + x * sin(radY);

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);
	glVertex3f(x1, y1, 0.0f);		// top left
	glVertex3f(x1, -y1, 0.0f);		// bottom left
	glVertex3f(x1  + 0.3f, y, 0.0f);		// top right
	glVertex3f(x1  + 0.3f, -y, 0.0f);		// bottom right
	glEnd();
}


void drawQuad(float x, float y, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);
	glVertex3f(-x + tx,  y + ty, 0.0f);		// top left
	glVertex3f(-x + tx, -y + ty, 0.0f);		// bottom left
	glVertex3f( x + tx,  y + ty, 0.0f);		// top right
	glVertex3f( x + tx, -y + ty, 0.0f);		// bottom right
	glEnd();
}

void drawCircle(float rad, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex3f(0.0f + tx, 0.0f + ty, 0.0f);

	for (int theta = 0; theta < 361; theta++)
	{
		glVertex3f(rad * cos(theta) + tx, rad * sin(theta) + ty, 0.0f);
	}
	glEnd();
}

void drawEllipse(float rx, float ry, float rad, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(r, g, b);
	glVertex3f(0.0f + tx, 0.0f + ty, 0.0f);

	for (int theta = 0; theta <= 360; theta++)
	{
		glVertex3f(rx + rad * cos(theta) + tx, ry + rad * sin(theta) + ty, 0.0f);
	}
	glEnd();
}

void drawTriangle(float x, float y, float tx, float ty, float scale, float r, float g, float b)
{
	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	glVertex3f( x * 0.0f + tx,  y + ty, scale);
	glVertex3f(-x        + tx, -y + ty, scale);
	glVertex3f( x        + tx, -y + ty, scale);
	glEnd();
}
void drawRATriangle(float x, float y, float tx, float ty, float scale, float r, float g, float b)
{
	glBegin(GL_TRIANGLES);
	glColor3f(r, g, b);
	glVertex3f( x + 0.001f + tx,  y + ty, scale);
	glVertex3f(-x          + tx, -y + ty, scale);
	glVertex3f( x          + tx, -y + ty, scale);
	glEnd();
}

void drawLines(float x, float y, float tx, float ty, float scale, float r, float g, float b)
{
	scale = scale / 10.0f;
	glBegin(GL_LINES);
	glColor3f(r, g, b);
	glVertex2f(x * scale + tx,  y + ty);
	glVertex2f(x * scale + tx, -y + ty);
	glEnd();
}

void drawCircleBorder(float rad, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_LINES);
	glColor3f(r, g, b);

	for (int theta = 0; theta < 361; theta++)
	{
		glVertex3f(rad * cos(theta) + tx, rad * sin(theta) + ty, 0.0f);
	}
	glEnd();
}

void drawMovingQuad(float x, float y, float tx, float ty, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);
	glVertex3f(-x / 2 + tx, y / 2 + ty, 0.0f);		// top left
	glVertex3f(-x / 2 + tx, -y / 2 + ty, 0.0f);		// bottom left
	glVertex3f( x / 2 + tx, y / 2 + ty, 0.0f);		// top right
	glVertex3f( x / 2 + tx, -y / 2 + ty, 0.0f);		// bottom right
	glEnd();
}

void drawCloud(float rx, float ry, float rad, float tx, float ty, float scale, float r, float g, float b)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.14 * float(i) / 100.0f;
		float factor = float(i) / 100.0f;
		glColor3f(r, g, b);
		glVertex3f(tx + (rx + rad * cosf(theta)) * scale, ty + (ry + rad * sinf(theta)) * scale, 0.0f);
	}
	glEnd();
}

void drawRectangle(float w, float h, float tx, float ty, float theta, float r, float g, float b)
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);

	float x0, y0, x1, y1;

	x0 = -w / 2, y0 = h / 2;
	x1 = 0.0f, y1 = 0.0f;

	x1 = x0 * cos(theta) - y0 * sin(theta);
	y1 = y0 * cos(theta) + x0 * sin(theta);
	glVertex3f(x1 + tx, y1 + ty, 0.0f);
	
	
	x0 = -w / 2, y0 = -h / 2;
	x1 = 0.0f, y1 = 0.0f;

	x1 = x0 * cos(theta) - y0 * sin(theta);
	y1 = y0 * cos(theta) + x0 * sin(theta);
	glVertex3f(x1 + tx, y1 + ty, 0.0f);
	
	
	x0 = w / 2, y0 = h / 2;
	x1 = 0.0f, y1 = 0.0f;

	x1 = x0 * cos(theta) - y0 * sin(theta);
	y1 = y0 * cos(theta) + x0 * sin(theta);
	glVertex3f(x1 + tx, y1 + ty, 0.0f);
	
	
	x0 = -w / 2, y0 = h / 2;
	x1 = 0.0f, y1 = 0.0f;

	x1 = x0 * cos(theta) - y0 * sin(theta);
	y1 = y0 * cos(theta) + x0 * sin(theta);
	glVertex3f(x1 + tx, y1 + ty, 0.0f);

	glEnd();
}

void draw2DTVTree(float x, float y)
{
	drawCircle(0.05f, x +  0.0f  , y + 0.0f , 0.08f, 0.21f, 0.02f);
	drawCircle(0.05f, x +  0.055f, y + 0.0f , 0.08f, 0.21f, 0.02f);
	drawCircle(0.05f, x -  0.055f, y + 0.0f , 0.08f, 0.21f, 0.02f);
	drawCircle(0.05f, x +  0.0f  , y + 0.05f, 0.08f, 0.21f, 0.02f);
	drawCircle(0.05f, x +  0.0f  , y - 0.05f, 0.08f, 0.21f, 0.02f);
}

void drawSideWall(float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(tlx, tly, scale);
	glVertex3f(trx, trY, scale);
	glVertex3f(brx, bry, scale);
	glVertex3f(blx, bly, scale);
	glEnd();
}
void drawMiddleWall(float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(tlx, tly, scale);
	glVertex3f(trx, trY, scale);
	glVertex3f(brx, bry, scale);
	glVertex3f(blx, bly, scale);
	glEnd();
}

void drawShikhar(float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(tlx, tly, scale);
	glVertex3f(trx, trY, scale);
	glVertex3f(brx, bry, scale);
	glVertex3f(blx, bly, scale);
	glEnd();
}


// updating to push