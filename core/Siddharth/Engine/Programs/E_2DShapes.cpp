#include "../Headers/E_2DShapes.h"
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

void drawQuad(float scaleXInPercent, float scaleYInPercent, float width, float height, float tx, float ty, float theta, float r, float g, float b, float alpha)
{
    float scaleX = scaleXInPercent / 100.0f;
    float scaleY = scaleYInPercent / 100.0f;
    float x0, y0 , x, y;

    x0 = -width / 2.0f, y0 = height / 2.0f;
    x = x0 * cosf(theta) - y0 * sinf(theta);

    glColor4f(r * 0.25f, g * 0.25f, b * 0.25f, alpha);
    glBegin(GL_QUADS);
    {
        x0 = (-width / 2.0f) * scaleX, y0 = (height / 2.0f) * scaleY;
        x = (x0 * cosf(theta) - y0 * sinf(theta)) + tx;
        y = (y0 * cosf(theta) + x0 * sinf(theta)) + ty;
        glVertex3f(x, y, 0.0f);

        x0 = width / 2.0f * scaleX, y0 = (height / 2.0f) * scaleY;
        x = (x0 * cosf(theta) - y0 * sinf(theta)) + tx;
        y = (y0 * cosf(theta) + x0 * sinf(theta)) + ty;
        glVertex3f(x, y, 0.0f);

        glColor4f(r, g, b, alpha); // debug purpose, to understand the "head" of the rectangle

        x0 = (width / 2.0f) * scaleX, y0 = (-height / 2.0f) * scaleY;
        x = (x0 * cosf(theta) - y0 * sinf(theta)) + tx;
        y = (y0 * cosf(theta) + x0 * sinf(theta)) + ty;
        glVertex3f(x, y, 0.0f);

        x0 = (-width / 2.0f) * scaleX, y0 = (-height / 2.0f) * scaleY;
        x = (x0 * cosf(theta) - y0 * sinf(theta)) + tx;
        y = (y0 * cosf(theta) + x0 * sinf(theta)) + ty;
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void  drawQuad2(float tx, float ty, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float red, float green, float blue)
{
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    {
        glVertex3f(x1 + tx, y1 + ty, 0.0f);
        glVertex3f(x2 + tx, y2 + ty, 0.0f);
        glVertex3f(x3 + tx, y3 + ty, 0.0f);
        glVertex3f(x4 + tx, y4 + ty, 0.0f);
    }
    glEnd();
}

void  drawLine(float width, float x1, float y1, float x2, float y2, float red, float green, float blue, float alpha)
{
    glColor4f(red, green, blue, alpha);
    glLineWidth(width);
    glBegin(GL_LINES);
    {
        glVertex3f(x1, y1, 0.0f);
        glVertex3f(x2, y2, 0.0f);
    }

    glLineWidth(1);

    glEnd();
}

void  drawCircle(float scaleInPercent, float radius, float tx, float ty, float red, float green, float blue, float alpha)
{
    glColor4f(red, green, blue, alpha);
    glBegin(GL_POLYGON);
    {
        float t = 0.0f, x, y;
        for(; t <= 2 * M_PI; t = t + 0.01f)
        {
            x = radius * cos(t);
            y = radius * sin(t);
            x = x + tx;
            y = y + ty;
            glVertex3f(x, y, 0.0f);
        }
    }
    glEnd();
}

// rectangle_t functions
void  renderRectangle(Rectangle_t rect)
{
    // variables
    float x, y;
    float width = rect.width;
    float height = rect.height;
    float theta = rect.transform.rotate.theta;
    float scaleX = rect.transform.scale.scaleX;
    float scaleY = rect.transform.scale.scaleY;
    float tx = rect.transform.translate.tx;
    float ty = rect.transform.translate.ty;
    int i;

    // code
    // vertex 1
    rect.v[0].x = (-width / 2.0f) * scaleX;
    rect.v[0].y = (height / 2.0f) * scaleY;
    x = (rect.v[0].x * cosf(theta) - rect.v[0].y * sinf(theta));
    y = (rect.v[0].y * cosf(theta) + rect.v[0].x * sinf(theta));
    rect.v[0].x = x + tx;
    rect.v[0].y = y + ty;

    // vertex 2
    rect.v[1].x = (width / 2.0f) * scaleX;
    rect.v[1].y = (height / 2.0f) * scaleY;
    x = (rect.v[1].x * cosf(theta) - rect.v[1].y * sinf(theta));
    y = (rect.v[1].y * cosf(theta) + rect.v[1].x * sinf(theta));
    rect.v[1].x = x + tx;
    rect.v[1].y = y + ty;

    // vertex 3
    rect.v[2].x = (width / 2.0f) * scaleX;
    rect.v[2].y = (-height / 2.0f) * scaleY;
    x = (rect.v[2].x * cosf(theta) - rect.v[2].y * sinf(theta));
    y = (rect.v[2].y * cosf(theta) + rect.v[2].x * sinf(theta));
    rect.v[2].x = x + tx;
    rect.v[2].y = y + ty;

    // vertex 4
    rect.v[3].x = (-width / 2.0f) * scaleX;
    rect.v[3].y = (-height / 2.0f) * scaleY;
    x = (rect.v[3].x * cosf(theta) - rect.v[3].y * sinf(theta));
    y = (rect.v[3].y * cosf(theta) + rect.v[3].x * sinf(theta));
    rect.v[3].x = x + tx;
    rect.v[3].y = y + ty;

    glColor4f(rect.color.red, rect.color.green, rect.color.blue, rect.color.alpha);
    glBegin(GL_QUADS);
    {
        for(i = 0; i < 4; ++i)
        {
            glVertex3f(rect.v[i].x, rect.v[i].y, 0.0f);
            // printf("TankVertex %d: x = %f \t y = %f\n", i + 1, rect.v[i].x, rect.v[i].y);
        }
    }
    glEnd();
}

// circle_t functions
void renderCircle(Circle_t circle)
{
    float radius = circle.radius;
    float tx = circle.transform.translate.tx;
    float ty = circle.transform.translate.ty;
    
    drawCircle(100.0f, radius, tx, ty, circle.color.red, circle.color.green, circle.color.blue, circle.color.alpha);
}

// line_t functions
void  renderLine(Line_t line)
{
    float tx = line.transform.translate.tx;
    float ty = line.transform.translate.ty;

    drawLine(
        line.lineWidth, 
        line.v[0].x + tx, 
        line.v[0].y + ty, 
        line.v[1].x + tx, 
        line.v[1].y + ty, 
        line.color.red,
        line.color.green, 
        line.color.blue, 
        line.color.alpha
    );
}
