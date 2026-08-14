#include<GL/freeglut.h>
#include "math.h"
#include "../../../core/Rugved/RSD_BINE/Headers/shapes.h"
#include "../../../core/Rugved/RSD_BINE/Headers/objects.h"

#define pi 3.14159265358979323846

void drawCholaTemple(float centerX, float centerY, float scaleX, float scaleY)
{
	//bottom-most part
	drawQuad_RD(0.8f, 0.08f, 0.10f, -0.98f, 0.2f, 0.1f, 0.0f);
	
	// bottom base
	drawQuad_RD(0.4f, 0.3f, -0.28f, -0.60f, 0.4f, 0.2f, 0.1f);
	drawQuad_RD(0.1f, 0.35f, -0.12f, -0.52f, 0.4f, 0.2f, 0.1f);
		
	// dome
	drawEllipse(0.0f, -0.2f, 0.08f, -0.425f, 0.80f, 0.8f, 0.4f, 0.1f);

	drawRASTriangle(0.02f, 0.03f, -0.35f, 0.55f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.33f, 0.45f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.31f, 0.35f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.29f, 0.25f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.28f, 0.15f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.26f, 0.05f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(0.02f, 0.03f, -0.25f,-0.05f, 1.0f, 0.9f, 0.6f, 0.3f);

	drawRASTriangle(-0.02f, 0.03f, -0.51f, 0.55f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.53f, 0.45f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.55f, 0.35f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.57f, 0.25f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.59f, 0.15f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.61f, 0.05f, 1.0f, 0.9f, 0.6f, 0.3f);
	drawRASTriangle(-0.02f, 0.03f, -0.63f,-0.05f, 1.0f, 0.9f, 0.6f, 0.3f);

	//shikhar
	drawShikhar(-0.5f, 0.6f, -0.35f, 0.6f, -0.2f, -0.3f, -0.68f, -0.3f, 0.3f, 0.4f, 0.2f, 0.1f);

	//side wall
	drawSideWall(0.12f, -0.9f, 0.12f, -0.6f, 0.8f, -0.6f, 0.8f, -0.9f, 0.3f, 0.9f, 0.6f, 0.3f);

	drawQuad_RD(0.08f, 0.05f, 0.72f, -0.55f, 0.8f, 0.4f, 0.2f);
	drawQuad_RD(0.08f, 0.01f, 0.72f, -0.50f, 0.4f, 0.2f, 0.1f);
	drawQuad_RD(0.08f, 0.01f, 0.72f, -0.55f, 0.4f, 0.2f, 0.1f);

	nandiTexture(0.03f, 0.02f, -0.18f, -0.15f, 1.0f, 0.8f, 0.4f, 0.2f);
	nandiTexture(0.03f, 0.02f, -0.08f, -0.15f, 1.0f, 0.8f, 0.4f, 0.2f);

	nandiTexture(0.03f, 0.02f, 0.01f, -0.28f, 1.0f, 0.8f, 0.4f, 0.2f);
	nandiTexture(0.03f, 0.02f, 0.08f, -0.28f, 1.0f, 0.8f, 0.4f, 0.2f);

	windowTexture(0.01f, 0.1f, -0.60f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.60f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.70f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	windowTexture(0.01f, 0.1f, -0.44f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.44f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.54f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	windowTexture(0.01f, 0.1f, -0.28f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.28f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.38f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	
	windowTexture(0.01f, 0.1f, -0.12f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.12f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.22f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	
	windowTexture(0.01f, 0.1f,  0.04f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f,  0.04f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.06f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);

	drawQuad_RD(0.20f, 0.13f, 0.46f, -0.77f, 0.4f, 0.2f, 0.1f);
	drawQuad_RD(0.78f, 0.02f, 0.099f, -0.65f, 0.8f, 0.4f, 0.2f);
	drawQuad_RD(0.38f, 0.02f, 0.47f, -0.61f, 0.4f, 0.2f, 0.1f);

	pillarTexture(0.01f, 0.1f, 0.26f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, 0.36f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, 0.46f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, 0.56f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, 0.76f, -0.8f, 1.0f, 0.9f, 0.6f, 0.3f);
	

	windowTexture(0.01f, 0.1f,  0.04f, -0.53f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f,  0.04f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.06f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	
	windowTexture(0.01f, 0.1f, -0.12f, -0.53f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.12f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.22f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	
	windowTexture(0.01f, 0.1f, -0.28f, -0.53f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.28f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.38f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	
	windowTexture(0.01f, 0.1f, -0.44f, -0.53f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.44f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.54f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);

	windowTexture(0.01f, 0.1f, -0.60f, -0.53f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.60f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);
	pillarTexture(0.01f, 0.1f, -0.70f, -0.52f, 1.0f, 0.9f, 0.6f, 0.3f);

	drawQuad_RD(0.4f, 0.047f, -0.28f, -0.34f, 0.9f, 0.6f, 0.3f);

	drawClubFlower(0.0f, 0.0f, -0.6f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawClubFlower(0.0f, 0.0f, -0.5f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawClubFlower(0.0f, 0.0f, -0.4f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawClubFlower(0.0f, 0.0f, -0.3f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawClubFlower(0.0f, 0.0f, -0.2f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawClubFlower(0.0f, 0.0f, -0.1f, -0.24f, 1.0f, 1.0f, 0.7f, 0.3f);

	drawQuad_RD(0.01f, 0.28f, -0.43f, 0.3f, 0.9f, 0.6f, 0.3f);

	drawShikharTexture(-0.2f, 0.2f, -0.3f + 0.01f, -0.15f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawShikharTexture(-0.2f, 0.2f, -0.4f + 0.01f, -0.15f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawShikharTexture(-0.2f, 0.2f, -0.5f + 0.01f, -0.15f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawShikharTexture(-0.2f, 0.2f, -0.6f + 0.01f, -0.15f, 1.0f, 1.0f, 0.7f, 0.3f);
	
	drawShikharTexture(-0.2f, 0.2f, -0.4f + 0.08f, -0.05f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawShikharTexture(-0.2f, 0.2f, -0.5f + 0.07f, -0.05f, 1.0f, 1.0f, 0.7f, 0.3f);
	drawShikharTexture(-0.2f, 0.2f, -0.6f + 0.06f, -0.05f, 1.0f, 1.0f, 0.7f, 0.3f);

	drawRATriangle(-0.05f, 0.08f,-0.465f, 0.65f, 1.0f, 0.4f, 0.2f, 0.1f);
	drawRATriangle( 0.05f, 0.08f,-0.390f, 0.65f, 1.0f, 0.4f, 0.2f, 0.1f);

	drawQuad_RD(0.31f, 0.01f, -0.35f, -0.18f, 0.9f, 0.6f, 0.3f);

}

// updating to push