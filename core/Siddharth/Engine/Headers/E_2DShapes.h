#pragma once

/////////////////
// PRIMITIVES //
////////////////
struct Point_t
{
    float x, y, z;
};
typedef struct Point_t Vertex_t;

struct Scale_t
{
    float scaleX, scaleY, scaleZ;
};
typedef struct Scale_t Scale_t;

struct Rotation_t
{
    float theta;
};
typedef struct Rotation_t Rotation_t;

struct Translation_t
{
    float tx, ty;
};
typedef struct Translation_t Translation_t;

struct Transform_t
{
    Scale_t       scale;
    Rotation_t    rotate;
    Translation_t translate;
};

struct Color_t
{
    float red, green, blue, alpha;
};
typedef struct Color_t Color_t;

//////////////////
// SOLID shapes //
//////////////////

struct Rectangle_t
{
    float width, height;
    Vertex_t v[4];
    Transform_t transform;
    Color_t color;
};
typedef struct Rectangle_t Rectangle_t;

struct Circle_t
{
    float radius;
    Transform_t transform;
    Color_t color;
};
typedef struct Circle_t Circle_t;

struct Line_t
{
    float lineWidth;
    Vertex_t v[2];
    Transform_t transform;
    Color_t color;
};
typedef struct Line_t Line_t;

/////////////////////////////
// render shapes functions //
////////////////////////////
void  renderRectangle(Rectangle_t rect);
void  renderCircle(Circle_t circle);
void  renderLine(Line_t line);

////////////////////////////
// QUAD drawing functions //
////////////////////////////
void  drawQuad(float scaleXInPercent, float scaleYInPercent, float width, float height, float tx, float ty, float theta, float red, float green, float blue, float alpha);
void  drawQuad2(float tx, float ty, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float red, float green, float blue);

////////////////////////////
// LINE drawing functions //
////////////////////////////
void  drawLine(float width, float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha);

//////////////////////////////
// Circle drawing functions //
//////////////////////////////
void  drawCircle(float scaleInPercent, float radius, float tx, float ty, float red, float green, float blue, float alpha);
