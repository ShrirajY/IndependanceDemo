#include<GL/freeglut.h>
#include <core/Utils.h>
#include "math.h"
#include <core/Rugved/RSD_BINE/Headers/shapes.h>

#define pi 3.14159265358979323846

void drawCholaTemple(float centerX, float centerY, float scaleX, float scaleY)
{
	drawQuad(2.0f, 2.0f, 0.0f, 0.0f, 0.3f, 0.1f, 0.0f);

	//bottom-most part
	drawQuad(0.8f, 0.08f, 0.10f, -0.97f, 0.2f, 0.1f, 0.0f);
	
	// bottom base
	drawQuad(0.4f, 0.3f, -0.28f, -0.60f, 0.4f, 0.2f, 0.1f);
	drawQuad(0.1f, 0.35f, -0.12f, -0.52f, 0.4f, 0.2f, 0.1f);

	// dome
	drawEllipse(0.0f, -0.2f, 0.08f, -0.425f, 0.80f, 0.8f, 0.4f, 0.1f);

	//shikhar
	drawShikhar(-0.5f, 0.6f, -0.35f, 0.6f, -0.2f, -0.3f, -0.68f, -0.3f, 0.3f, 0.5f, 0.2f, 0.1f);

	//side wall
	drawSideWall(0.12f, -0.9f, 0.12f, -0.6f, 0.8f, -0.6f, 0.8f, -0.9f, 0.3f, 0.9f, 0.6f, 0.3f);

	drawQuad(0.08f, 0.05f, 0.72f, -0.55f, 0.8f, 0.4f, 0.2f);
}