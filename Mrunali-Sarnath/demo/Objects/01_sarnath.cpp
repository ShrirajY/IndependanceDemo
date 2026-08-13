#include<GL/freeglut.h>
#include<math.h>

#include "..\..\core\include\E_2Dshapes.h"
#include "..\..\core\include\E_utils.h"

#define PI 3.14159265358979323846

bool bIsFullScreen = false;
int main(int argc, char* argv[])
{
	// function declarations
	void initialize(void);
	void uninitialize(void);
	//void resize(int, int);
	void Resize(int width, int height); 		//kept it for ResolutionMultiplier

	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);

	// code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sarnath");

	initialize();

	//glutReshapeFunc(resize);
	glutReshapeFunc(Resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	// flow should not come here
	return (0);
}

void initialize(void)
{
	// code
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// void resize(int width, int height)
// {
// 	// code
// 	if (height <= 0)
// 		height = 1;
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();

// 	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
// }

// Resolution multiplier
float CurrentWidth = 0.0f;
float CurrentHeight = 0.0f;
float ResolutionMultiplier = 0.0f;
void Resize(int width, int height)
{
    if(height <= 0)
        height = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	CurrentWidth = glutGet(GLUT_WINDOW_WIDTH);
	CurrentHeight = glutGet(GLUT_WINDOW_HEIGHT);
	ResolutionMultiplier = CurrentWidth/CurrentHeight;

	// Fix stretching: multiply the left/right viewing boundaries by the aspect ratio
    glOrtho(-1.0f * ResolutionMultiplier, 1.0f * ResolutionMultiplier, -1.0f, 1.0f, -1.0f, 1.0f);

    // Always reset matrix mode back to Modelview for safety
    glMatrixMode(GL_MODELVIEW);

}

void DrawFlower(float scale, float tx, float ty)
{
	for(float i = 0.0f; i < 1.3f; i = i + 0.1f)
	{
		E_DrawTriangleWH(0.02, 0.05, 
						1.0f * scale, tx, ty,
						00.0f + (5.0f * i), 
						0.95f, 0.94f, 0.85f);
	}

	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawCircle(0.009f * scale, 0.0f + tx, 0.0f + ty);
}

void SarnathTempleShikhar(float scale, float tx, float ty)
{

	//======================= TOP =================================
	// topmost small triangle
	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawTriangleFourCoord(-0.02f , 0.9f,
							 0.00f , 0.97f, 
							 0.02f , 0.9f,
							 1.0f * scale, tx, ty);
	// small rect						 
	glColor3f(0.41f, 0.33f, 0.22f);
	E_DrawRectangleFourCoord(-0.02f, 0.9f,
							 0.02f , 0.9f, 
							 0.02f , 0.87f, 
							 -0.02f, 0.87f,
							 1.0f * scale, tx, ty);	
	
	// small rect - hori
	glColor3f(0.24f, 0.19f, 0.11f);
	E_DrawRectangleFourCoord(-0.03f, 0.87f,
							 0.03f , 0.87f, 
							 0.03f , 0.85f, 
							 -0.03f, 0.85f,
							 1.0f * scale, tx, ty);	

	// small rect - verti
	glColor3f(0.41f, 0.33f, 0.22f);
	E_DrawRectangleFourCoord(-0.04f, 0.85f,
							 0.04f , 0.85f, 
							 0.04f , 0.83f, 
							 -0.04f, 0.83f,
							 1.0f * scale, tx, ty);
	
	// =============================== MIDDLE =================================						 
	// middle big rectangle - shikhar
	glColor3f(0.72f, 0.68f, 0.62f);
	E_DrawRectangleFourCoord(-0.05f, 0.83f,
							 0.05f , 0.83f, 
							 0.25f , 0.2f, 
							 -0.25f, 0.2f,
							 1.0f * scale, tx, ty);	
			 

	for(float i = 0.0f; i < 0.6f; i = i + 0.1f)
	{
		// zig zag rect - from top to bottom of shikhar

		glColor3f(0.54f, 0.48f, 0.42f);
		E_DrawRectangleFourCoord(-0.07f - (0.32f * i) , 0.8f - i,
								0.07f   + (0.32f * i) , 0.8f - i, 
								0.07f   + (0.32f * i) , 0.76f - i, 
								-0.07f  - (0.32f * i) , 0.76f - i,
								1.0f * scale, tx, ty);

		// rect - but like shading shading like						
		glColor3f(0.31f, 0.31f, 0.23f);
		E_DrawRectangleFourCoord(-0.07f - (0.3f * i) , 0.8f - i,
								0.07f   - (0.3f * i) , 0.8f - i, 
								0.07f   + (0.3f * i) , 0.78f - i, 
								-0.07f  + (0.3f * i) , 0.78f - i,
								1.0f * scale, tx, ty);	
		
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

void FancyDoorOnShikharTop(float scale, float tx, float ty)
{	
	// door like
	glColor3f(0.73f, 0.68f, 0.61f);
	E_DrawRectangleFourCoord(-0.12f, 0.13f,
							 0.12f , 0.13f, 
							 0.12f , -0.1f, 
							 -0.12f, -0.1f,
							 1.0f * scale,tx, ty);
	// small black door
	glColor3f(0.27f, 0.18f, 0.16f);	
	E_DrawRectangleFourCoord(-0.05f, 0.05f,
							 0.05f , 0.05f, 
							 0.05f , -0.1f, 
							 -0.05f, -0.1f,
							 1.0f * scale,tx, ty);			 

}

void Top(float scale, float tx, float ty)
{
	// -------------- 1 middle big triangle ----------------
	SarnathTempleShikhar(1.0f * scale, 0.0f + tx, 0.0f + ty);
	// big down rect
	glColor3f(0.54f, 0.48f, 0.42f);
	E_DrawRectangleFourCoord(-0.25f, 0.2f,
							 0.25f , 0.2f, 
							 0.25f , -0.1f, 
							 -0.25f, -0.1f,
							 1.0f * scale, tx, ty);
							 
    DrawFlower(0.60f * scale, tx, ((0.81f + 0.00f) * scale) + ty);
    DrawFlower(0.62f * scale, tx, ((0.81f - 0.10f) * scale) + ty);
    DrawFlower(0.64f * scale, tx, ((0.81f - 0.20f) * scale) + ty);
    DrawFlower(0.66f * scale, tx, ((0.81f - 0.30f) * scale) + ty);
    DrawFlower(0.68f * scale, tx, ((0.81f - 0.40f) * scale) + ty);
    DrawFlower(0.70f * scale, tx, ((0.81f - 0.50f) * scale) + ty);
    DrawFlower(0.73f * scale, tx, ((0.81f - 0.60f) * scale) + ty);

							
	// for(float i = 0.1f; i < 0.7f; i = i + 0.1f)
	// {
	// 	DrawFlower((1.0f + i )* scale, (0.0f) + tx, ((0.0f - i) * scale ) + ty);
	// }

	// door like entrance
	FancyDoorOnShikharTop(1.0f * scale, 0.0f + tx, 0.0f + ty);



	// ------------- 2 left small triangle  -----------------
	SarnathTempleShikhar(0.6f * scale, (-0.3f * scale) + tx, (-0.22f * scale) + ty);
	// for(float i = 0.4f + ty; i < 0.7f + ty; i += 0.1f)
    // {
    //     DrawFlower(0.6f * scale, (-0.3f * scale) + tx, (-0.22f - i) * scale + ty);
    // }




	// --------------  3  right small triangle  -------------- 
	SarnathTempleShikhar(0.6f * scale, (0.3f * scale) + tx, (-0.22f * scale) + ty);
    DrawFlower(0.6f * scale, (0.3f * scale) + tx, (-0.22f ) * scale + ty);

	// for(float i = 0.4f; i < 0.7f; i += 0.1f)
    // {
    //     DrawFlower(0.6f * scale, (0.3f * scale) + tx, (-0.22f - i) * scale + ty);
    // }

}

void MiddleAndBottom(float scale, float tx, float ty)
{
	// 1 - black color small rect
	glColor3f(0.2f, 0.15f, 0.08f);
	E_DrawRectangleFourCoord(-0.48f, -0.1f,
							 0.48f , -0.1f, 
							 0.48f , -0.12f, 
							 -0.48f, -0.12f,
							 1.0f * scale, tx, ty);
	
	// 2 - darkGray color rect 
	glColor3f(0.54f, 0.48f, 0.42f);	
	E_DrawRectangleFourCoord(-0.45f, -0.12f,
							 0.45f , -0.12f, 
							 0.50f , -0.25f, 
							 -0.50f, -0.25f,
							 1.0f * scale, tx, ty);		
							 
	// 3 - lightGray color rect
	glColor3f(0.76f, 0.73f, 0.69f);	
	E_DrawRectangleFourCoord(-0.50f, -0.25f,
							 0.50f , -0.25f, 
							 0.55f , -0.6f, 
							 -0.55f, -0.6f,
							 1.0f * scale, tx, ty);	
		
	// middle slip in bottom part - pink line - small
	glColor3f(0.68f, 0.38f, 0.33f);	
	E_DrawRectangleFourCoord(-0.54f, -0.42,
							 0.54f , -0.42f, 
							 0.54f , -0.47f, 
							 -0.54f, -0.47f,
							 1.0f * scale, tx, ty);	

	// bottom slip in bottom part - pink line - small
	glColor3f(0.68f, 0.38f, 0.33f);	
	E_DrawRectangleFourCoord(-0.56f, -0.6,
							 0.56f , -0.6f, 
							 0.56f , -0.62f, 
							 -0.56f, -0.62f,
							 1.0f * scale, tx, ty);	
							 
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
							 1.0f * scale,tx, ty);	

	// Door at the front - entrance - black
	glColor3f(0.27f, 0.18f, 0.16f);				
	E_DrawRectangleFourCoord(-0.1f, -0.27,
							 0.1f , -0.27f, 
							 0.1f , -0.6f, 
							 -0.1f, -0.6f,
							 1.0f * scale,tx, ty);
	
}

void SarnathTemple(float scale, float tx, float ty)
{
	//-------------Top-----------------
	// 1
	Top(1.0f * scale, 0.0f + tx, 0.0f + ty);

	//------------ middle -------------
	MiddleAndBottom(1.0f * scale, 0.0f + tx, 0.0f + ty);

}

void DrawSarnathTemple()
{
	// temple
	SarnathTemple(1.0f, 0.0f, 0.0f);
}

void display(void)
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//func call
	DrawSarnathTemple();

	//for animation this func is added
	glutPostRedisplay();


	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)
{
	// code
	switch (key)
	{
		case 27: 
			glutLeaveMainLoop();
			break;
		case 'F':
		case 'f':
			if (bIsFullScreen == false)
			{
				glutFullScreen();
				bIsFullScreen = true;
			}
			else
			{
				glutLeaveFullScreen();
				bIsFullScreen = false;
			}
			break;

		default:
			break;
		
	}
}

void mouse(int button, int state, int x, int y)
{
	// code
	switch (button)
	{
		case GLUT_RIGHT_BUTTON: 
			glutLeaveMainLoop();
			break;
		default:
			break;
	}
}

void uninitialize(void)
{
	// code

}