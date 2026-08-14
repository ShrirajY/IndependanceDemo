#include<GL/freeglut.h>
#include "math.h"


#define PI 3.14159265359f

// ========= Function for Scale, TranslateX and TranslateY so glTranslateVertex will become glTranslateVertex()

void glTranslateVertex(float x, float y, float scalefactor, float translateX, float translateY)
{
    float new_X = x * scalefactor + translateX;
    float new_Y = y * scalefactor + translateY;

    glVertex3f(new_X, new_Y, 0.0f);
}



// =============   BASIC FUNCTIONS  =================

void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scaleFactor, float translateX, float translateY)
{
    

    glBegin(GL_QUADS);

        glTranslateVertex(x1  , y1  , scaleFactor, translateX, translateY);
        glTranslateVertex(x2  , y2  , scaleFactor, translateX, translateY );
        glTranslateVertex(x3  , y3  , scaleFactor, translateX, translateY );
        glTranslateVertex(x4  , y4  , scaleFactor, translateX, translateY );

    glEnd();
}


void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float scaleFactor, float translateX, float translateY)
{
    

    glBegin(GL_TRIANGLES);

        glTranslateVertex(x1  , y1 , scaleFactor, translateX, translateY);
        glTranslateVertex(x2  , y2 , scaleFactor, translateX, translateY);
        glTranslateVertex(x3  , y3 , scaleFactor, translateX, translateY);

    glEnd();
}


void drawLine(float x1, float y1,float x2, float y2, float scaleFactor, float translateX, float translateY)
{


    glBegin(GL_LINES);

        glTranslateVertex(x1  , y1 , scaleFactor, translateX, translateY);
        glTranslateVertex(x2  , y2 , scaleFactor, translateX, translateY);

    glEnd();
}


// ===============   CIRCLE  =================

void drawCircle(float centerX, float centerY, float radius, float scaleFactor, float translateX, float translateY)
{
    

    glBegin(GL_TRIANGLE_FAN);

        glTranslateVertex(centerX  , centerY  , scaleFactor, translateX, translateY);

        for (float theta = 0.0f; theta <= 2.0f * PI; theta += 0.01f)
        {
            float x = centerX + radius * cosf(theta);
            float y = centerY + radius * sinf(theta);

            glTranslateVertex(x  , y  , scaleFactor, translateX, translateY);
        }

    glEnd();
}


// ============   OUTLINE CIRCLE  ===========

void drawCircleOutline(float centerX, float centerY, float radius, float scaleFactor, float translateX, float translateY)
{
    
    glBegin(GL_LINE_LOOP);

        for (float theta = 0.0f; theta <= 2.0f * PI; theta += 0.01f)
        {
            float x = centerX + radius * cosf(theta) ;
            float y = centerY + radius * sinf(theta) ;

            glTranslateVertex(x  , y, scaleFactor, translateX, translateY);
        }

    glEnd();
}


// ===========   ARCH  ====================


void drawArch(float centerX, float archBottomY, float width, float height, float scaleFactor, float translateX, float translateY )
{
    float radius = width / 2.0f;
    float archCurveY = archBottomY + height - radius;
    

    glBegin(GL_POLYGON);

        /* Left vertical side */
        glTranslateVertex(centerX - radius  , archBottomY, scaleFactor, translateX, translateY);
        glTranslateVertex(centerX - radius  , archCurveY , scaleFactor, translateX, translateY);

        /* Semicircle */
        for (float theta = PI; theta >= 0.0f; theta -= 0.03f)
        {
            float x = centerX + radius * cosf(theta);
            float y = archCurveY + radius * sinf(theta);

            glTranslateVertex(x  , y  , scaleFactor, translateX, translateY);
        }

        /* Right vertical side */
        glTranslateVertex(centerX + radius  , archCurveY   , scaleFactor, translateX, translateY);
        glTranslateVertex(centerX + radius  , archBottomY  , scaleFactor, translateX, translateY);

    glEnd();
}



// =====================  ARCH OUTLINE ========================


void drawArchOutline(float centerX, float archBottomY, float width, float height, float scaleFactor, float translateX, float translateY)
{
    float radius = width / 2.0f;
    float archCurveY = archBottomY + height - radius;
     ;

    glBegin(GL_LINE_STRIP);

        glTranslateVertex(centerX - radius  , archBottomY, scaleFactor, translateX, translateY);
        glTranslateVertex(centerX - radius  , archCurveY , scaleFactor, translateX, translateY);

        for (float theta = PI; theta >= 0.0f;theta -= 0.03f)
        {
            float x = centerX + radius * cosf(theta);
            float y = archCurveY + radius * sinf(theta);

            glTranslateVertex(x  , y, scaleFactor, translateX, translateY);
        }

        glTranslateVertex(centerX + radius, archBottomY, scaleFactor, translateX, translateY);

    glEnd();
}
