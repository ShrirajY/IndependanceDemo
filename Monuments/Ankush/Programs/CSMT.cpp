#include <GL/freeglut.h>
#include "math.h"
#include "../../../core/Timer.h"
#include "../../../core/Ankush/Engine/Headers/Ng_shapes.h"


#define PI 3.14159265359f

// void glTranslateVertex(float x, float y, float scalefactor, float translateX, float translateY)
// {
//     float new_X = x * scalefactor + translateX;
//     float new_Y = y * scalefactor + translateY;

//     glVertex3f(new_X, new_Y, 0.0f);
// }



/* ========= PILLAR ============ */

void drawPillar(float x, float y, float width, float height, float scaleFactor, float translateX, float translateY)
{
        
    /* Main pillar */
    glColor3f(0.45f, 0.28f, 0.16f);

    drawRectangle(x          , y          , 
                  x + width  , y          ,
                  x + width  , y + height ,
                  x          , y + height , scaleFactor, translateX, translateY);

    /* Highlight */
    glColor3f(0.70f, 0.48f, 0.30f);

    drawRectangle(x + width * 0.25f , y          , 
                  x + width * 0.45f , y          ,
                  x + width * 0.45f , y + height ,
                  x + width * 0.25f , y + height , scaleFactor, translateX, translateY);

    /* Top */
    glColor3f(0.30f, 0.18f, 0.12f);

    drawRectangle(x - 0.01f         , y + height          ,
                  x + width + 0.01f , y + height          ,
                  x + width + 0.01f , y + height + 0.025f ,
                  x - 0.01f         , y + height + 0.025f , scaleFactor, translateX, translateY);
     
    
}


/* ================  SMALL WINDOW  =========== */

void drawWindow(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY)
{
    /* Window */
    glColor3f(0.78f, 0.72f, 0.55f);

    drawArch(cx , bottom , width, height, scaleFactor, translateX, translateY);

    /* Outline */
    glColor3f(0.15f, 0.12f, 0.10f);

    glLineWidth(2.0f);

    drawArchOutline(cx , bottom , width, height, scaleFactor, translateX, translateY);

    /* Vertical divider */
    drawLine(cx , bottom,
             cx , bottom + height * 0.65f, scaleFactor, translateX, translateY );
}


/* ============== GOTHIC WINDOW =================== */

void drawGothicWindow(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY)
{
   

    glColor3f(1.20f, 1.10f, 1.68f);   // White color

    drawArch(cx , bottom, width, height, scaleFactor, translateX, translateY);

    glColor3f(0.15f, 0.12f, 0.10f);

    glLineWidth(2.0f);

    drawArchOutline(cx , bottom , width, height, scaleFactor, translateX, translateY);

    /* Central vertical line */
    drawLine(cx , bottom ,
             cx , bottom + height * 0.75f, scaleFactor, translateX, translateY );

    /* Left diagonal */
    drawLine(cx - width * 0.38f ,bottom + height * 0.55f , 
             cx , bottom + height, scaleFactor, translateX, translateY );

    /* Right diagonal */
    drawLine(cx , bottom + height , 
             cx + width * 0.38f , bottom + height * 0.55f, scaleFactor, translateX, translateY );
}


/* ================= CIRCULAR WINDOW =================== */

void drawCircularWindow(float centerX, float centerY, float radius, float scaleFactor, float translateX, float translateY)
{
    /* Outer circle */
    // glColor3f(0.82f, 0.76f, 0.58f);

    drawCircle(centerX , centerY , radius, scaleFactor, translateX, translateY);

    /* Outline */
    glColor3f(0.15f, 0.12f, 0.10f);

    glLineWidth(2.0f);

    drawCircleOutline(centerX , centerY , radius, scaleFactor, translateX, translateY);

    /* Vertical divider */
    drawLine(centerX - radius ,  centerY ,
             centerX + radius ,  centerY , scaleFactor, translateX, translateY);

    /* Horizontal divider */
    drawLine(centerX , centerY - radius ,
             centerX , centerY + radius , scaleFactor, translateX, translateY);
}


/* ============  ROOF ============= */

void drawRoof(float x1, float y1, float x2, float y2, float peakX, float peakY, float scaleFactor, float translateX, float translateY)
{
    glColor3f(0.40f, 0.23f, 0.15f);

    drawTriangle(x1    ,    y1 , 
                 x2    ,    y2 , 
                 peakX , peakY , scaleFactor, translateX, translateY);

    glColor3f(0.12f, 0.10f, 0.08f);

    glLineWidth(2.0f);

    drawLine(x1   , y1    , 
             peakX, peakY , scaleFactor, translateX, translateY);

    drawLine(peakX , peakY , 
             x2    , y2    , scaleFactor, translateX, translateY);
}


/* ===============  TOWER ROOF ==================== */

void drawTowerRoof(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY)
{
    glColor3f(0.42f, 0.25f, 0.16f);

    drawTriangle(cx - width / 2 , bottom          ,
                 cx + width / 2 , bottom          ,
                 cx             , bottom + height , scaleFactor, translateX, translateY);

    glColor3f(0.12f, 0.10f, 0.08f);

    glLineWidth(2.0f);

    drawLine(cx - width / 2 , bottom          ,
             cx             , bottom + height , scaleFactor, translateX, translateY);

    drawLine(cx             , bottom + height ,
             cx + width / 2 , bottom          , scaleFactor, translateX, translateY);
}


/* ---------------------------------------------------------
   CROSS
   --------------------------------------------------------- */

void drawCross(float cx, float cy, float size, float scaleFactor, float translateX, float translateY)
{
    glColor3f(0.12f, 0.10f, 0.08f);

    glLineWidth(2.0f);

    drawLine(cx, cy - size,
             cx, cy + size , scaleFactor, translateX, translateY);

    drawLine(cx - size * 0.45f, cy + size * 0.35f,
             cx + size * 0.45f, cy + size * 0.35f , scaleFactor, translateX, translateY);
}


/* ================= SIDE TOWER ============= */

void drawSideTower(float cx, float scaleFactor, float translateX, float translateY)
{
    /* Tower body */
    glColor3f(0.47f, 0.29f, 0.18f);

    drawRectangle(cx - 0.095f , -0.45f ,
                  cx + 0.095f , -0.45f ,
                  cx + 0.095f ,  0.25f ,
                  cx - 0.095f ,  0.25f , scaleFactor, translateX, translateY);

    /* Tower roof */
    drawTowerRoof(cx  , 0.25f , 0.18f, 0.28f, scaleFactor, translateX, translateY);

    /* Tower window */
    drawGothicWindow(cx        , 0.02f ,  0.04f, 0.12f, scaleFactor, translateX, translateY);
    drawGothicWindow(cx - 0.07 , 0.02f ,  0.04f, 0.12f, scaleFactor, translateX, translateY);
    drawGothicWindow(cx + 0.07 , 0.02f ,  0.04f, 0.12f, scaleFactor, translateX, translateY);

    // Mid Tower Window
    
            drawArch(cx , -0.2f , 0.10f,  0.14f, scaleFactor, translateX, translateY);
    glColor3f(1.0f,1.0f,1.0f); 
    drawGothicWindow(cx , -0.2f , 0.08f, 0.14f, scaleFactor, translateX, translateY); 
    drawArchOutline(cx  , -0.2f , 0.10f, 0.14f, scaleFactor, translateX, translateY);

   
    /* Lower window */

            drawArch(cx , -0.45f , 0.12f,  0.18f, scaleFactor, translateX, translateY);
    glColor3f(1.0f,1.0f,1.0f); 
    drawGothicWindow(cx , -0.45f , 0.10f, 0.16f, scaleFactor, translateX, translateY); 
    drawArchOutline(cx  , -0.45f , 0.12f, 0.16f, scaleFactor, translateX, translateY);

   
    //======================== Cross =========================

    /* Horizontal decorative lines */
    glColor3f(0.15f, 0.12f, 0.10f);

    glLineWidth(2.0f);

    drawLine(cx - 0.085f ,  0.18f , cx + 0.085f ,  0.18f , scaleFactor, translateX, translateY);
    drawLine(cx - 0.085f ,  0.15f , cx + 0.085f ,  0.15f , scaleFactor, translateX, translateY);
    drawLine(cx - 0.085f , -0.24f , cx + 0.085f , -0.24f , scaleFactor, translateX, translateY);
    drawLine(cx - 0.085f , -0.22f , cx + 0.085f , -0.22f , scaleFactor, translateX, translateY);

    /* Cross */
    drawCross(cx, 0.55f, 0.035f, scaleFactor, translateX, translateY);
}


/* =============== MAIN CENTER DOME =================== */

void drawDome(float scaleFactor, float translateX, float translateY)
{
    float cx = 0.0f;
    float baseY = 0.52f;
    float radiusX = 0.15f;
    float radiusY = 0.23f;

    glColor3f(0.43f, 0.27f, 0.17f);

    glBegin(GL_POLYGON);

        for (float theta = PI; theta >= 0.0f; theta -= 0.02f)
        {
            float x = cx + radiusX * cosf(theta);
            float y = baseY + radiusY * sinf(theta);

            glTranslateVertex(x , y  , scaleFactor, translateX, translateY);
        }

        glTranslateVertex(cx + radiusX , baseY , scaleFactor, translateX, translateY);
        glTranslateVertex(cx - radiusX , baseY , scaleFactor, translateX, translateY);

    glEnd();

    /* Dome outline */
    glColor3f(0.12f, 0.10f, 0.08f);

    glLineWidth(2.0f);

    glBegin(GL_LINE_STRIP);

        for (float theta = PI; theta >= 0.0f; theta -= 0.02f)
        {
            float x = cx + radiusX * cosf(theta);
            float y = baseY + radiusY * sinf(theta);

            glTranslateVertex(x , y , scaleFactor, translateX, translateY);
        }

    glEnd();

    /* Dome vertical ribs */
    for (int i = -3; i <= 3; i++)
    {
        float x = i * 0.045f;
        drawLine(x         , baseY , x         , baseY + 0.1f, scaleFactor, translateX, translateY );
        drawLine(x + 0.02f , baseY , x - 0.02f , baseY       , scaleFactor, translateX, translateY );
    }

    drawLine( 0.01f , 0.74 ,  0.1   , baseY  , scaleFactor, translateX, translateY);
    drawLine( 0.01f , 0.74 ,  0.11  , baseY  , scaleFactor, translateX, translateY);
    drawLine(-0.01f , 0.74 , -0.1   , baseY  , scaleFactor, translateX, translateY);
    drawLine(-0.01f , 0.74 , -0.11  , baseY  , scaleFactor, translateX, translateY);



    /* Small top structure */
    glColor3f(0.75f, 0.60f, 0.40f);

    drawTriangle(-0.025f , 0.74f, 
                  0.025f , 0.74f, 
                  0.0f , 0.85f , scaleFactor, translateX, translateY);

    drawRectangle(-0.018f, 0.74f,
                   0.018f, 0.74f,
                   0.018f, 0.79f,
                  -0.018f, 0.79f, scaleFactor, translateX, translateY);

  
}


/* ===================== CENTER TOWER =============== */

void drawCenterTower(float scaleFactor, float translateX, float translateY)
{
    /* Main central tower */
    glColor3f(0.48f, 0.30f, 0.18f);

    drawRectangle(-0.15f, -0.45f,
                   0.15f, -0.45f,
                   0.15f, 0.52f,
                  -0.15f, 0.52f , scaleFactor, translateX, translateY);

    /* Dome */
    drawDome(scaleFactor, translateX, translateY);

    
//=======================================================================

    for (int i = -3; i <= 3; i++)
    {
        float baseY = 0.0f;
        float x = i * 0.045f;

        drawLine(x + 0.01f , baseY + 0.05  ,
                 x + 0.01f , baseY + 0.48f , scaleFactor, translateX, translateY); // vetical line        
        for(int j = -3; j<= 3; j++)
        {
            float baseY = 0.0f;
            float x = j * 0.045f;

            drawLine(x + 0.05f , baseY + 0.48 , x - 0.05f , baseY + 0.48f , scaleFactor, translateX, translateY);         // Top border
            drawLine(x + 0.05f , baseY + 0.45f, x - 0.05f , baseY + 0.45f , scaleFactor, translateX, translateY);  
            drawLine(x + 0.05f , baseY + 0.45f, x - 0.05f , baseY + 0.15f , scaleFactor, translateX, translateY); 
            drawLine(x + 0.05f , baseY + 0.1f , x - 0.05f , baseY + 0.1f  , scaleFactor, translateX, translateY); 
            drawLine(x + 0.05f , baseY + 0.08f, x - 0.05f , baseY + 0.08f , scaleFactor, translateX, translateY);
        }
    }
    
    //=================================================================

    for (int i = -3; i <= 3; i++)
    {
        float baseY = 0.0f;
        float x = i * 0.045f;

        drawLine(x + 0.01f , baseY + 0.05 ,
                 x + 0.01f , baseY + 0.22f , scaleFactor, translateX, translateY); // vetical line        
        for(int j = -3; j<= 3; j++)
        {
            float baseY = 0.0f;
            float x = j * 0.045f;

            drawLine(x + 0.05f , baseY + 0.24  ,  x - 0.05f , baseY + 0.24f, scaleFactor, translateX, translateY );         // Top border
            drawLine(x + 0.05f , baseY + 0.22f  , x - 0.05f , baseY + 0.22f, scaleFactor, translateX, translateY );  
        }
    }
        
    drawTowerRoof(0.0f , 0.52f ,  0.3f , 0.09f, scaleFactor, translateX, translateY );
    drawTowerRoof(0.0f ,  0.1f , 0.33f , 0.16f, scaleFactor, translateX, translateY );   // centeral Triangle

    /* Main circular window */
    
    drawCircularWindow(0.0f , 0.16f , 0.055f, scaleFactor, translateX, translateY);    
    drawCircularWindow(0.0f , 0.16f , 0.045f, scaleFactor, translateX, translateY);

    /* Upper gothic window */
    drawGothicWindow( 0.0f  , 0.27f , 0.05f, 0.14f, scaleFactor, translateX, translateY);
    drawGothicWindow(-0.09f , 0.27f , 0.05f, 0.14f, scaleFactor, translateX, translateY);
    drawGothicWindow( 0.09f , 0.27f , 0.05f, 0.14f, scaleFactor, translateX, translateY);

    /* Lower three gothic windows */

    drawGothicWindow(-0.095f , -0.05f, 0.075f, 0.14f, scaleFactor, translateX, translateY);
    drawGothicWindow( 0.0f   , -0.05f, 0.075f, 0.14f, scaleFactor, translateX, translateY);
    drawGothicWindow( 0.095f , -0.05f, 0.075f, 0.14f, scaleFactor, translateX, translateY);

    /* Central entrance */
    // glColor3f(1.25f, 1.15f, 1.10f);

            drawArch( 0.0f , -0.45f , 0.12f,  0.22f, scaleFactor, translateX, translateY);    
    glColor3f(0.0f, 0.0f, 0.0f);        
    drawGothicWindow( 0.0f , -0.45f , 0.075f, 0.22f, scaleFactor, translateX, translateY);

            drawArch(-0.1f , -0.45f , 0.12f,  0.22f, scaleFactor, translateX, translateY);
    glColor3f(0.0f, 0.0f, 0.0f);        
    drawGothicWindow( -0.1f , -0.45f , 0.075f, 0.22f, scaleFactor, translateX, translateY);

            drawArch( 0.1f , -0.45f , 0.12f,  0.22f, scaleFactor, translateX, translateY);
    glColor3f(0.0f, 0.0f, 0.0f);        
    drawGothicWindow( 0.1f , -0.45f , 0.075f, 0.22f, scaleFactor, translateX, translateY);

    // glColor3f(1.12f, 1.10f, 1.08f);

    drawArchOutline( 0.0f , -0.45f , 0.12f, 0.25f, scaleFactor, translateX, translateY);
    drawArchOutline(-0.1f , -0.45f , 0.12f, 0.25f, scaleFactor, translateX, translateY);
    drawArchOutline( 0.1f , -0.45f , 0.12f, 0.25f, scaleFactor, translateX, translateY);

    
// =======================================================================================                    

    /* Side pillars */
    
    drawTowerRoof(-0.17f  ,   0.5f ,  0.06f,  0.08f, scaleFactor, translateX, translateY);    
       drawPillar(-0.185f , -0.45f , 0.035f,  0.95f, scaleFactor, translateX, translateY);

    drawTowerRoof(0.17f ,   0.5f ,  0.06f , 0.08f, scaleFactor, translateX, translateY);
       drawPillar(0.15f ,  -0.45f , 0.035f, 0.95f, scaleFactor, translateX, translateY);


    // main wall pillars 
    drawTowerRoof(-0.43f ,  0.12f , 0.06f  ,  0.08f , scaleFactor, translateX, translateY);    
       drawPillar(-0.45f , -0.45f , 0.035f ,  0.55f , scaleFactor, translateX, translateY);
    drawTowerRoof(0.47f  ,  0.12f ,  0.06f ,  0.08f , scaleFactor, translateX, translateY);
       drawPillar(0.45f  , -0.45f , 0.035f ,  0.55f , scaleFactor, translateX, translateY);

    
    // ==================== Border Lines ===========================                

    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = -3; i <= 3; i++)
    {
        float baseY = 0.0f;
        float x = i * 0.045f;

        drawLine(x + 0.01f , baseY , 
                 x + 0.01f , baseY + 0.22f , scaleFactor, translateX, translateY); // vetical line
        
        for(int j = -3; j<= 3; j++)
        {
            float baseY = 0.0f;
            float x = j * 0.045f;
            
            drawLine(x + 0.05f , baseY + 0.24  , x - 0.05f , baseY + 0.24f , scaleFactor, translateX, translateY);        // Top border
            drawLine(x + 0.05f , baseY + 0.22f , x - 0.05f , baseY + 0.22f , scaleFactor, translateX, translateY);         // Top border
            drawLine(x + 0.2f  , baseY - 0.2   , x - 0.2f  , baseY - 0.2f  , scaleFactor, translateX, translateY);         // mid border       
            drawLine(x + 0.2f  , baseY - 0.21  , x - 0.2f  , baseY - 0.21f , scaleFactor, translateX, translateY);         // mid border    
            drawLine(x - 0.05f , baseY - 0.4f  , x + 0.05f , baseY - 0.4f  , scaleFactor, translateX, translateY);  // bottom border of window
            drawLine(x - 0.05f , baseY - 0.41f , x + 0.05f , baseY - 0.41f , scaleFactor, translateX, translateY);  // bottom border of window
        }
        
    }


}


/* =============== MAIN BUILDING WALL ================== */

void drawMainWall(float scaleFactor, float translateX, float translateY)
{
    /* Large horizontal wall */
    glColor3f(0.48f, 0.30f, 0.19f);

    drawRectangle(-0.70f, -0.45f, 0.70f, -0.45f,
                   0.70f, 0.05f,
                  -0.70f, 0.05f , scaleFactor, translateX, translateY);

    /* Roof */
    glColor3f(0.38f, 0.22f, 0.15f);

    drawRectangle(-0.70f, 0.05f, 
                   0.70f, 0.05f,
                   0.70f, 0.14f,
                  -0.70f, 0.14f , scaleFactor, translateX, translateY);

                  
       /* WALL vertical ribs roof */

    glColor3f(0.0f, 0.0f, 0.0f);

    for (int i = -15; i <= 15; i++)
    {
        float baseY = 0.0f;
        float x = i * 0.045f;

        drawLine(x + 0.01f , baseY         ,
                 x + 0.01f , baseY + 0.14f , scaleFactor, translateX, translateY); // vetical line
        
        for(int j = -12; j<= 12; j++)     // Horizontal line
        {
            float baseY = 0.0f;
            float x = j * 0.045f;
            
            drawLine(x + 0.2f , baseY         , x - 0.2f , baseY         , scaleFactor, translateX, translateY);         // Top border
            drawLine(x + 0.2f , baseY -0.01f  , x - 0.2f , baseY - 0.01f , scaleFactor, translateX, translateY);         // Top border
            drawLine(x + 0.2f , baseY - 0.2   , x - 0.2f , baseY - 0.2f  , scaleFactor, translateX, translateY);         // mid border         
            drawLine(x + 0.2f , baseY - 0.21  , x - 0.2f , baseY - 0.21f , scaleFactor, translateX, translateY);         // mid border  
            drawLine(x - 0.2f , baseY - 0.4f  , x + 0.2f , baseY - 0.4f  , scaleFactor, translateX, translateY);  // bottom border of window
            drawLine(x - 0.2f , baseY - 0.41f , x + 0.2f , baseY - 0.41f , scaleFactor, translateX, translateY);  // bottom border of window
        }
        
    }


    /* Lower arches  ground windows*/

    for (float x = -0.60f; x <= 0.60f; x += 0.20f)
    {
        drawGothicWindow(x , -0.42f , 0.12f, 0.18f, scaleFactor, translateX, translateY);
    }

    /* Upper arches 1st floor windows */

    for (float x = -0.65f; x <= 0.65f; x += 0.12f)
    {
        drawGothicWindow(x , -0.12f , 0.08f, 0.15f, scaleFactor, translateX, translateY);
    }
}


/* ================ BUILDING OUTLINE / DECORATION ============== */

void drawDecorations(float scaleFactor, float translateX, float translateY)
{
    glColor3f(0.12f, 0.10f, 0.08f);

    glLineWidth(2.0f);

    /* Horizontal lines */

    // drawLine(-0.70f, -0.30f,
    //          0.70f, -0.30f);

    drawLine(-0.70f , -0.05f , 0.70f , -0.05f, scaleFactor, translateX, translateY);
    drawLine(-0.70f ,  0.05f , 0.70f ,  0.05f, scaleFactor, translateX, translateY);

    /* Small vertical decorative pillars */

    drawTowerRoof(-0.69f  ,  0.26f , 0.05f,   0.08f, scaleFactor, translateX, translateY);
       drawPillar(-0.70f  , -0.45f , 0.025f,  0.70f, scaleFactor, translateX, translateY);                           //drawPillar( x, y, Weight, height);
    drawTowerRoof(0.69f   ,  0.26f , 0.05f,   0.08f, scaleFactor, translateX, translateY);                       
       drawPillar(0.68f   , -0.45f , 0.025f,  0.70f, scaleFactor, translateX, translateY);
    drawTowerRoof(-0.89f  ,  0.26f , 0.05f,   0.08f, scaleFactor, translateX, translateY);
       drawPillar(-0.90f  , -0.45f , 0.025f,  0.70f, scaleFactor, translateX, translateY);                           //drawPillar( x, y, Weight, height);
    drawTowerRoof(0.89f   ,  0.26f , 0.05f,   0.08f, scaleFactor, translateX, translateY);                       
       drawPillar(0.88f   , -0.45f , 0.025f,  0.70f, scaleFactor, translateX, translateY);
}

void drawGround(float scaleFactor, float translateX, float translateY)
{
    glColor3f(0.62f, 0.45f, 0.30f);

    drawRectangle( -0.95f, -0.48f,
                    0.95f, -0.48f,
                    0.95f, -0.44f,
                   -0.95f, -0.44f, scaleFactor, translateX, translateY);
}

void drawRoad(float scaleFactor, float translateX, float translateY)
{   

     glColor3f(0.25f, 0.25f, 0.25f);
    drawRectangle(-1.0f, -0.48f,
                   1.0f, -0.48f,
                   1.0f, -1.0f,
                  -1.0f, -1.0f, scaleFactor, translateX, translateY);

    float baseY = 0.0f;
    float x = 0.0f;

    glColor3f(1.0f, 1.0f, 1.0f);
    drawLine(x - 1.0f , baseY - 0.72f,  x + 1.0f , baseY - 0.72f , scaleFactor, translateX, translateY);  // bottom border of window
    drawLine(x - 1.0f , baseY - 0.74f,  x + 1.0f , baseY - 0.74f , scaleFactor, translateX, translateY);  // bottom border of window

}


/* ================ ENTIRE BUILDING ================== */

void drawBuilding(float scaleFactor, float translateX, float translateY)
{
    drawMainWall(scaleFactor, translateX, translateY);

    drawSideTower(-0.79f, scaleFactor, translateX, translateY  ); //Left Tower
    drawSideTower( 0.79f, scaleFactor, translateX, translateY  );  // Right Tower

    drawCenterTower(scaleFactor, translateX, translateY);

    drawDecorations(scaleFactor, translateX, translateY);

    drawGround(scaleFactor, translateX, translateY);

    drawRoad(scaleFactor, translateX, translateY);
}


/* =================== GROUND ===================== */

// void drawGround(float scaleFactor, float translateX, float translateY)
// {
//     glColor3f(0.62f, 0.45f, 0.30f);

//     drawRectangle( -0.95f, -0.48f,
//                     0.95f, -0.48f,
//                     0.95f, -0.44f,
//                    -0.95f, -0.44f, scaleFactor, translateX, translateY);
// }


// void drawRoad(float scaleFactor, float translateX, float translateY)
// {   

//      glColor3f(0.25f, 0.25f, 0.25f);
//     drawRectangle(-1.0f, -0.48f,
//                    1.0f, -0.48f,
//                    1.0f, -1.0f,
//                   -1.0f, -1.0f, scaleFactor, translateX, translateY);

//     float baseY = 0.0f;
//     float x = 0.0f;

//     glColor3f(1.0f, 1.0f, 1.0f);
//     drawLine(x - 1.0f , baseY - 0.72f,  x + 1.0f , baseY - 0.72f , scaleFactor, translateX, translateY);  // bottom border of window
//     drawLine(x - 1.0f , baseY - 0.74f,  x + 1.0f , baseY - 0.74f , scaleFactor, translateX, translateY);  // bottom border of window
// }


/* =============== BACKGROUND =============== */

void drawBackground(float scaleFactor, float translateX, float translateY)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    drawRectangle(-1.0f , -1.0f,
                   1.0f , -1.0f,
                   1.0f , 1.0f,
                  -1.0f , 1.0f, scaleFactor, translateX, translateY);
}
