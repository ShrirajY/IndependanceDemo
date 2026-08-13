#include <GL/freeglut.h>
#include <math.h>
#include <cstdlib>
#include <ctime> 
#include "timer.h"

void background(float x, float y, float tx, float ty, float scaleFactor, float r, float g, float b)
{
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(x + tx, y + ty, scaleFactor);
	glVertex3f(x + tx, y + ty, scaleFactor);
	glVertex3f(x + tx, y + ty, scaleFactor);
	glVertex3f(x + tx, y + ty, scaleFactor);
	glEnd();
}

// updating to push

