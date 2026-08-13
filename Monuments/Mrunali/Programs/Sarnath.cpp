// Sarnath

#include <GL/glut.h>
#include "../../../core/Mrunali/Engine/Headers/E_2Dshapes.h"

void DrawFlower(float tx, float ty, float scale)
{
	for(float i = 0.0f; i < 1.3f; i = i + 0.1f)
	{
		E_DrawTriangleWH(0.02, 0.05, 
						scale, tx, ty,
						00.0f + (5.0f * i), 
						0.95f, 0.94f, 0.85f);
	}

	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawCircle(0.009f * scale, tx, ty);
}

void SarnathTempleShikhar(float tx, float ty, float scale)
{

	//======================= TOP =================================
	// topmost small triangle
	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawTriangleFourCoord(-0.02f , 0.9f,
							 0.00f , 0.97f, 
							 0.02f , 0.9f,
							 scale, tx, ty);
	// small rect						 
	glColor3f(0.41f, 0.33f, 0.22f);
	E_DrawRectangleFourCoord(-0.02f, 0.9f,
							 0.02f , 0.9f, 
							 0.02f , 0.87f, 
							 -0.02f, 0.87f,
							 scale, tx, ty);	
	
	// small rect - hori
	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawRectangleFourCoord(-0.03f, 0.87f,
							 0.03f , 0.87f, 
							 0.03f , 0.85f, 
							 -0.03f, 0.85f,
							 scale, tx, ty);	

	// small rect - verti
	glColor3f(0.41f, 0.33f, 0.22f);
	E_DrawRectangleFourCoord(-0.04f, 0.85f,
							 0.04f , 0.85f, 
							 0.04f , 0.83f, 
							 -0.04f, 0.83f,
							 scale, tx, ty);
	
	// =============================== MIDDLE =================================						 
	// middle big rectangle - shikhar
	glColor3f(0.72f, 0.68f, 0.62f);
	E_DrawRectangleFourCoord(-0.05f, 0.83f,
							 0.05f , 0.83f, 
							 0.25f , 0.2f, 
							 -0.25f, 0.2f,
							 scale, tx, ty);	
			 

	for(float i = 0.0f; i < 0.6f; i = i + 0.1f)
	{
		// zig zag rect - from top to bottom of shikhar

		glColor3f(0.54f, 0.48f, 0.42f);
		E_DrawRectangleFourCoord(-0.07f - (0.32f * i) , 0.8f - i,
								0.07f   + (0.32f * i) , 0.8f - i, 
								0.07f   + (0.32f * i) , 0.76f - i, 
								-0.07f  - (0.32f * i) , 0.76f - i,
								scale, tx, ty);

		// rect - but like shading shading like						
		glColor3f(0.31f, 0.31f, 0.23f);
		E_DrawRectangleFourCoord(-0.07f - (0.3f * i) , 0.8f - i,
								 0.07f   - (0.3f * i) , 0.8f - i, 
								 0.07f   + (0.3f * i) , 0.78f - i, 
								 -0.07f  + (0.3f * i) , 0.78f - i,
								 scale, tx, ty);	
		
		// STRAIGHT LINES from top to bottom of shikhar						
		glColor3f(0.07f, 0.08f, 0.08f);				
		E_DrawStraightLines2Coor(-0.09f - (0.3f * i) , 0.7f - i,
								 0.09f  + (0.3f * i) , 0.7f - i,
								 scale, tx, ty);

		glColor3f(0.31f, 0.31f, 0.23f);
		E_DrawStraightLines2Coor(-0.099f - (0.3f * i) , 0.69f - i,
								 0.09f  + (0.3f * i) , 0.69f - i,
								 scale, tx, ty);		
								 
		glColor3f(0.54f, 0.54f, 0.37f);
		E_DrawStraightLines2Coor(-0.099f - (0.3f * i) , 0.68f - i,
								 0.09f  + (0.3f * i) , 0.68f - i,
								 scale, tx, ty);							 
	}	


}

void FancyDoorOnShikharTop(float tx, float ty, float scale)
{	
	// door like
	glColor3f(0.73f, 0.68f, 0.61f);
	E_DrawRectangleFourCoord(-0.12f, 0.13f,
							 0.12f , 0.13f, 
							 0.12f , -0.1f, 
							 -0.12f, -0.1f,
							 scale, tx, ty);
	// small black door
	glColor3f(0.27f, 0.18f, 0.16f);	
	E_DrawRectangleFourCoord(-0.05f, 0.05f,
							 0.05f , 0.05f, 
							 0.05f , -0.1f, 
							 -0.05f, -0.1f,
							 scale, tx, ty);			 

}

void Top(float tx, float ty, float scale)
{
	// -------------- 1 middle big triangle ----------------
	SarnathTempleShikhar(tx, ty, scale);
	// big down rect
	glColor3f(0.54f, 0.48f, 0.42f);
	E_DrawRectangleFourCoord(-0.25f, 0.2f,
							 0.25f , 0.2f, 
							 0.25f , -0.1f, 
							 -0.25f, -0.1f,
							 scale, tx, ty);

	for(float i = 0.0f, j = 0.60f; i < 61.0f, j < 0.74f; i = i + 0.10f, j = j + 0.02f)
	{
    	DrawFlower(tx, ((0.81f - i) * scale) + ty, (j) * scale);
	}

	// door like entrance
	FancyDoorOnShikharTop(tx, ty, scale);

	// ------------- 2 left small triangle  ---------------------------------------
	SarnathTempleShikhar((-0.3f * scale) + tx, (-0.22f * scale) + ty, 0.6f * scale);

	for(float i = 0.0f, j = 0.60f; i < 21.0f, j < 0.74f; i = i + 0.08f, j = j + 0.02f)
	{
    	DrawFlower(tx - 0.3f, ((0.25f - i) * scale) + ty, (j) * scale);
	}

	// --------------  3  right small triangle  -----------------------------------
	SarnathTempleShikhar((0.3f * scale) + tx, (-0.22f * scale) + ty, 0.6f * scale);

	for(float i = 0.0f, j = 0.60f; i < 21.0f, j < 0.74f; i = i + 0.08f, j = j + 0.02f)
	{
		DrawFlower(tx + 0.3f, ((0.25f - i) * scale) + ty, (j) * scale);
	}
}

void MiddleAndBottom(float tx, float ty, float scale)
{
	// 1 - black color small rect
	glColor3f(0.2f, 0.15f, 0.08f);
	E_DrawRectangleFourCoord(-0.48f, -0.1f,
							 0.48f , -0.1f, 
							 0.48f , -0.12f, 
							 -0.48f, -0.12f,
							 scale, tx, ty);
	
	// 2 - darkGray color rect 
	glColor3f(0.54f, 0.48f, 0.42f);	
	E_DrawRectangleFourCoord(-0.45f, -0.12f,
							 0.45f , -0.12f, 
							 0.50f , -0.25f, 
							 -0.50f, -0.25f,
							 scale, tx, ty);		
							 
	// 3 - lightGray color rect
	glColor3f(0.76f, 0.73f, 0.69f);	
	E_DrawRectangleFourCoord(-0.50f, -0.25f,
							 0.50f , -0.25f, 
							 0.55f , -0.6f, 
							 -0.55f, -0.6f,
							 scale, tx, ty);	
		
	// middle slip in bottom part - pink line - small
	glColor3f(0.68f, 0.38f, 0.33f);	
	E_DrawRectangleFourCoord(-0.54f, -0.42,
							 0.54f , -0.42f, 
							 0.54f , -0.47f, 
							 -0.54f, -0.47f,
							 scale, tx, ty);	

	// bottom slip in bottom part - pink line - small
	glColor3f(0.68f, 0.38f, 0.33f);	
	E_DrawRectangleFourCoord(-0.56f, -0.6,
							 0.56f , -0.6f, 
							 0.56f , -0.62f, 
							 -0.56f, -0.62f,
							 scale, tx, ty);	
							 
	// STRAIGHT LINES - left
	for(float i = 0.0f; i < 0.5f; i = i + 0.1f)
	{
		glColor3f(0.07f, 0.08f, 0.08f);				
		E_DrawStraightLines2Coor(-0.47f + (i) , -0.25f,
								 -0.47f + (i) , -0.6f,
								 scale, tx, ty);

		glColor3f(0.31f, 0.31f, 0.23f);
		E_DrawStraightLines2Coor(-0.48f + (i) , -0.25f,
								 -0.48f + (i) , -0.6f,
								 scale, tx, ty);		
								 
		glColor3f(0.54f, 0.54f, 0.37f);
		E_DrawStraightLines2Coor(-0.49f + (i) , -0.25f,
								 -0.49f + (i) , -0.6f,
								 scale, tx, ty);							 
	}	
	// STRAIGHT LINES - right
	for(float i = 0.4f; i > 0.0f; i = i - 0.1f)
	{
		glColor3f(0.07f, 0.08f, 0.08f);				
		E_DrawStraightLines2Coor(0.47f - (i) , -0.25f,
								 0.47f - (i) , -0.6f,
								 scale, tx, ty);

		glColor3f(0.31f, 0.31f, 0.23f);
		E_DrawStraightLines2Coor(0.48f - (i) , -0.25f,
								 0.48f - (i) , -0.6f,
								 scale, tx, ty);		
								 
		glColor3f(0.54f, 0.54f, 0.37f);
		E_DrawStraightLines2Coor(0.49f - (i) , -0.25f,
								 0.49f - (i) , -0.6f,
								 scale, tx, ty);							 
	}		

	// Door at the front - entrance - pink color - strip
	glColor3f(0.68f, 0.38f, 0.33f);				
	E_DrawRectangleFourCoord(-0.12f, -0.23,
							 0.12f , -0.23f, 
							 0.12f , -0.27f, 
							 -0.12f, -0.27f,
							 scale,tx, ty);	

	// Door at the front - entrance - black
	glColor3f(0.27f, 0.18f, 0.16f);				
	E_DrawRectangleFourCoord(-0.1f, -0.27,
							 0.1f , -0.27f, 
							 0.1f , -0.6f, 
							 -0.1f, -0.6f,
							 scale,tx, ty);
	
}

void SarnathTemple(float tx, float ty, float scale)
{
	//-------------Top-----------------
	// 1
	Top(tx, ty, scale);

	//------------ middle -------------
	// 2
	MiddleAndBottom(tx, ty, scale);

}

void DrawSarnathTemple(float tx, float ty, float scaleX, float scaleY)
{
	SarnathTemple( tx, ty, scaleX);
}
