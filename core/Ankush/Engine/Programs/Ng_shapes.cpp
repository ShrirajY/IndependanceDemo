#include<GL/freeglut.h>
#include "math.h"


#define PI 3.14159265359f

// =============   BASIC FUNCTIONS  =================

void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    

    glBegin(GL_QUADS);

        glVertex3f(x1  , y1  , 0.0f );
        glVertex3f(x2  , y2   , 0.0f );
        glVertex3f(x3  , y3   , 0.0f );
        glVertex3f(x4  , y4   , 0.0f );

    glEnd();
}


void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3 )
{
    

    glBegin(GL_TRIANGLES);

        glVertex3f(x1  , y1  ,0.0f);
        glVertex3f(x2  , y2  ,0.0f);
        glVertex3f(x3  , y3  ,0.0f);

    glEnd();
}


void drawLine(float x1, float y1,float x2, float y2)
{


    glBegin(GL_LINES);

        glVertex3f(x1  , y1  , 0.0f);
        glVertex3f(x2  , y2  , 0.0f);

    glEnd();
}


// ===============   CIRCLE  =================

void drawCircle(float centerX, float centerY, float radius)
{
    

    glBegin(GL_TRIANGLE_FAN);

        glVertex3f(centerX  , centerY  , 0.0f);

        for (float theta = 0.0f; theta <= 2.0f * PI; theta += 0.01f)
        {
            float x = centerX + radius * cosf(theta);
            float y = centerY + radius * sinf(theta);

            glVertex3f(x  , y  ,0.0f);
        }

    glEnd();
}


// ============   OUTLINE CIRCLE  ===========

void drawCircleOutline(float centerX, float centerY, float radius)
{
    
    glBegin(GL_LINE_LOOP);

        for (float theta = 0.0f; theta <= 2.0f * PI; theta += 0.01f)
        {
            float x = centerX + radius * cosf(theta) ;
            float y = centerY + radius * sinf(theta) ;

            glVertex3f(x  , y  , 0.0f);
        }

    glEnd();
}


// ===========   ARCH  ====================


void drawArch(float centerX, float archBottomY, float width, float height )
{
    float radius = width / 2.0f;
    float archCurveY = archBottomY + height - radius;
    

    glBegin(GL_POLYGON);

        /* Left vertical side */
        glVertex3f(centerX - radius  , archBottomY  , 0.0f);
        glVertex3f(centerX - radius  , archCurveY   , 0.0f);

        /* Semicircle */
        for (float theta = PI; theta >= 0.0f; theta -= 0.03f)
        {
            float x = centerX + radius * cosf(theta);
            float y = archCurveY + radius * sinf(theta);

            glVertex3f(x  , y  , 0.0f);
        }

        /* Right vertical side */
        glVertex3f(centerX + radius  , archCurveY   , 0.0f);
        glVertex3f(centerX + radius  , archBottomY  , 0.0f);

    glEnd();
}



// =====================  ARCH OUTLINE ========================


void drawArchOutline(float centerX, float archBottomY, float width, float height)
{
    float radius = width / 2.0f;
    float archCurveY = archBottomY + height - radius;
     ;

    glBegin(GL_LINE_STRIP);

        glVertex3f(centerX - radius  , archBottomY  , 0.0f);
        glVertex3f(centerX - radius  , archCurveY   , 0.0f);

        for (float theta = PI; theta >= 0.0f;theta -= 0.03f)
        {
            float x = centerX + radius * cosf(theta);
            float y = archCurveY + radius * sinf(theta);

            glVertex3f(x  , y  ,0.0f);
        }

        glVertex3f(centerX + radius  , archBottomY  ,0.0f);

    glEnd();
}
