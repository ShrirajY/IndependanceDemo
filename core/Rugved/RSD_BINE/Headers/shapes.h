#include "core/Utils.h"

void drawQuad		  (float x, float y, float tx, float ty, float r, float g, float b);
void drawTestOC		  (float x, float y, float angle, float tx, float ty, float r, float g, float b);
void drawRotatingQuad (float x, float y, float theta, float tx, float ty, float r, float g, float b);
void drawQuadOC		  (float x, float y, float tx, float ty, float r, float g, float b);
void drawRectangle	  (float w, float h, float tx, float ty, float theta, float r, float g, float b);
void drawCircle		  (float rad, float tx, float ty, float r, float g, float b);
void drawEllipse	  (float rx, float ry, float rad, float tx, float ty, float r, float g, float b);
void drawTriangle	  (float x, float y, float tx, float ty, float scale, float r, float g, float b);
void drawLines		  (float x, float y, float tx, float ty, float scale, float r, float g, float b);
void drawCircleBorder (float rad, float tx, float ty, float r, float g, float b);
void drawMovingQuad   (float x, float y, float tx, float ty, float r, float g, float b);
void drawShirt		  (float x, float y, float tx, float ty, float r, float g, float b);
void drawCloud		  (float rx, float ry, float rad, float tx, float ty, float scale, float r, float g, float b);

void draw2DTVTree	  (float x, float y);
void drawMiddleWall	  (float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b);
void drawSideWall	  (float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b);
void drawShikhar	  (float tlx, float tly, float trx, float trY, float brx, float bry, float blx, float bly, float scale, float r, float g, float b);

//void drawTank(float x, float y, float Angle, float tx, float ty, float r, float g, float b);

struct RD_GE_VEC3
{
	float x;
	float y;
	float z;
};

struct RD_GE_COLOR3
{
	float r;
	float g;
	float b;
};

struct RD_GE_TRANSFORM
{
	RD_GE_VEC3 translation;
	RD_GE_VEC3 roatation;
	RD_GE_VEC3 scale;
};

struct RD_GE_RECTANGLE
{
	RD_GE_TRANSFORM transform;
	RD_GE_COLOR3 color;
};