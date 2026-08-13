#include<GL/freeglut.h>
#include <core/Utils.h>
#include "math.h"
#include <core/Rugved/RSD_BINE/Headers/shapes.h>
#include <core/Rugved/RSD_BINE/Headers/objects.h>

#define pi 3.14159265358979323846

void drawCholaTemple(float centerX, float centerY, float scaleX, float scaleY)
{

	background(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);

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

	windowTexture(0.01f, 0.1f, -0.6f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.6f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.7f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	windowTexture(0.01f, 0.1f, -0.4f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.4f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.5f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	windowTexture(0.01f, 0.1f, -0.2f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.2f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.3f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	nandiTexture(0.03f, 0.02f, -0.18f, -0.15f, 1.0f, 0.8f, 0.4f, 0.2f);
	nandiTexture(0.03f, 0.02f, -0.08f, -0.15f, 1.0f, 0.8f, 0.4f, 0.2f);

	nandiTexture(0.03f, 0.02f, -0.01f, -0.28f, 1.0f, 0.8f, 0.4f, 0.2f);
	nandiTexture(0.03f, 0.02f,  0.08f, -0.28f, 1.0f, 0.8f, 0.4f, 0.2f);
}

// updating to push