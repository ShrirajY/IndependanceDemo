#include<GL/freeglut.h>
#include<math.h>

void E_DrawSquareFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scale, float tx, float ty)
{
    //triangle
	glBegin(GL_QUADS);
	glVertex3f(((0.0f + x1) * scale ) + tx , ((0.0f + y1) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x2) * scale ) + tx , ((0.0f + y2) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x3) * scale ) + tx , ((0.0f + y3) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x4) * scale ) + tx , ((0.0f + y4) * scale ) + ty , 0.0f);
	glEnd();
}

void E_DrawTriangleFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float scale, float tx, float ty)
{
    //triangle
	glBegin(GL_TRIANGLES);
	glVertex3f(((0.0f + x1) * scale ) + tx , ((0.0f + y1) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x2) * scale ) + tx , ((0.0f + y2) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x3) * scale ) + tx , ((0.0f + y3) * scale ) + ty , 0.0f);
	glEnd();
}

void E_DrawRectangleFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scale, float tx, float ty)
{
    //triangle
	glBegin(GL_QUADS);
	glVertex3f(((0.0f + x1) * scale ) + tx , ((0.0f + y1) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x2) * scale ) + tx , ((0.0f + y2) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x3) * scale ) + tx , ((0.0f + y3) * scale ) + ty , 0.0f);
	glVertex3f(((0.0f + x4) * scale ) + tx , ((0.0f + y4) * scale ) + ty , 0.0f);
	glEnd();
}

void E_DrawSemiCircle(float scale, float tx, float ty)
{
	glBegin(GL_TRIANGLE_FAN);
    glVertex2f(tx, ty);
    for(int i = 0; i <= 180; i++)
    {
        glVertex2f((scale * cos(i * 3.14159265f / 180.0f)) + tx, (scale * sin(i * 3.14159265f / 180.0f)) + ty);
    }
    glEnd();
}

void E_DrawCircle(float scale, float tx, float ty)
{
    glBegin(GL_TRIANGLE_FAN);
    for(float i = 0.0f; i <= 360.0f; i++)
    {
        glVertex2f((scale * sin(i)) + tx , (scale * cos(i)) + ty);
    }
    glEnd();
}

void E_DrawStraightLines2Coor(float x1, float y1, float x2, float y2, float scale, float tx, float ty)
{
	glBegin(GL_LINES);
	glVertex2f((x1 * scale ) + tx , (y1 * scale ) + ty);
	glVertex2f((x2 * scale ) + tx , (y2 * scale ) + ty);
	glEnd();
}

//=================================================================================================
void E_DrawRectangleWH(float w, float h, float tx, float ty, float theta, float r, float g, float b)
{
	glBegin (GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);

	//x1 = x0 * cos(theta) - y0 * sin(theta);
	//y1 = y0 * cos(theta) + x0 * sin(theta);

	float x0, y0, x1, y1;

	x0 = -w/2; y0 = -h/2;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex3f(x1 + tx, y1 + ty, 0.0f);
//-----------------------------------------------
	x0 = -w/2; y0 = h/2;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex3f(x1 + tx, y1 + ty, 0.0f);

//-----------------------------------------------
	x0 = w/2; y0 = -h/2;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex3f(x1 + tx, y1 + ty, 0.0f);

//-----------------------------------------------
	x0 = w/2; y0 = h/2;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex3f(x1 + tx, y1 + ty, 0.0f);

	glEnd();

}

//===================================================================================================
void E_DrawTriangleWH(float w, float h, float scale, float tx, float ty, float theta, float r, float g, float b)
{
	glBegin (GL_TRIANGLE_STRIP);
	glColor3f(r, g, b);

	//x1 = x0 * cos(theta) - y0 * sin(theta);
	//y1 = y0 * cos(theta) + x0 * sin(theta);

	float x0, y0, x1, y1;

	x0 = -w/2; y0 = 0;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex2f((x1 * scale ) + tx , (y1 * scale ) + ty);
//================================================
	x0 = 0; y0 = h;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex2f((x1 * scale ) + tx , (y1 * scale ) + ty);

//================================================
	x0 = w/2; y0 = 0;
	x1 = 0.0f; y1 = 0.0f;

	x1 = x0 * cosf(theta) - y0 * sinf(theta);
	y1 = y0 * cosf(theta) + x0 * sinf(theta);

	glVertex2f((x1 * scale ) + tx , (y1 * scale ) + ty);

	glEnd();

}

