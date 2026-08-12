#include <GL/glut.h>
#include "../../../core/Lakshmi/Engine/Headers/Ng_shapes.h"

void drawKonark(float centerX, float centerY, float scaleX, float scaleY) {
    // Structural color palette definitions
    float stoneBase[]  = {0.45f, 0.42f, 0.48f}; 
    float stoneLight[] = {0.62f, 0.55f, 0.58f}; 
    float stoneDark[]  = {0.28f, 0.25f, 0.32f}; 

    // ==========================================
    // PYRAMID ROOF
    // ==========================================
    draw_pixel_roof_tier(0.48f, 0.34f, 0.12f, 0.32f, 3, stoneBase[0], stoneBase[1], stoneBase[2], centerX, centerY, scaleX, scaleY);
    draw_pixel_roof_tier(0.32f, 0.20f, 0.32f, 0.50f, 3, stoneLight[0], stoneLight[1], stoneLight[2], centerX, centerY, scaleX, scaleY);
    draw_pixel_roof_tier(0.18f, 0.08f, 0.50f, 0.65f, 2, stoneBase[0], stoneBase[1], stoneBase[2], centerX, centerY, scaleX, scaleY);

    // Crowning cap (Amalaka dome)
    glColor3f(stoneDark[0], stoneDark[1], stoneDark[2]);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.10f * scaleX, centerY + 0.65f * scaleY); 
        glVertex2f(centerX + 0.10f * scaleX, centerY + 0.65f * scaleY);
        glVertex2f(centerX + 0.08f * scaleX, centerY + 0.74f * scaleY);  
        glVertex2f(centerX - 0.08f * scaleX, centerY + 0.74f * scaleY);
    glEnd();

    // ==========================================
    // MINI-PILLARS
    // ==========================================
    glColor3f(stoneDark[0], stoneDark[1], stoneDark[2]);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.38f * scaleX, centerY + 0.04f * scaleY); 
        glVertex2f(centerX + 0.38f * scaleX, centerY + 0.04f * scaleY);
        glVertex2f(centerX + 0.38f * scaleX, centerY + 0.12f * scaleY);  
        glVertex2f(centerX - 0.38f * scaleX, centerY + 0.12f * scaleY);
    glEnd();

    glColor3f(stoneLight[0], stoneLight[1], stoneLight[2]);
    for (float x = -0.36f; x <= 0.36f; x += 0.04f) {
        glBegin(GL_QUADS);
            glVertex2f(centerX + (x - 0.01f) * scaleX, centerY + 0.05f * scaleY); 
            glVertex2f(centerX + (x + 0.01f) * scaleX, centerY + 0.05f * scaleY);
            glVertex2f(centerX + (x + 0.01f) * scaleX, centerY + 0.11f * scaleY); 
            glVertex2f(centerX + (x - 0.01f) * scaleX, centerY + 0.11f * scaleY);
        glEnd();
    }

    // ==========================================
    // VERTICAL WALL FACADE
    // ==========================================
    glColor3f(stoneBase[0], stoneBase[1], stoneBase[2]);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.44f * scaleX, centerY - 0.40f * scaleY); 
        glVertex2f(centerX + 0.44f * scaleX, centerY - 0.40f * scaleY);
        glVertex2f(centerX + 0.44f * scaleX, centerY + 0.04f * scaleY);  
        glVertex2f(centerX - 0.44f * scaleX, centerY + 0.04f * scaleY);
    glEnd();

    // Symmetrical flanking architectural pillars
    float frontPillars[] = {-0.38f, -0.28f, -0.20f, 0.20f, 0.28f, 0.38f};
    for (int p = 0; p < 6; p++) {
        glColor3f(stoneLight[0], stoneLight[1], stoneLight[2]);
        glBegin(GL_QUADS);
            glVertex2f(centerX + (frontPillars[p] - 0.02f) * scaleX, centerY - 0.40f * scaleY);
            glVertex2f(centerX + (frontPillars[p] + 0.02f) * scaleX, centerY - 0.40f * scaleY);
            glVertex2f(centerX + (frontPillars[p] + 0.02f) * scaleX, centerY + 0.04f * scaleY);
            glVertex2f(centerX + (frontPillars[p] - 0.02f) * scaleX, centerY + 0.04f * scaleY);
        glEnd();

        glColor3f(stoneDark[0], stoneDark[1], stoneDark[2]);
        glBegin(GL_QUADS);
            glVertex2f(centerX + (frontPillars[p] - 0.005f) * scaleX, centerY - 0.35f * scaleY);
            glVertex2f(centerX + (frontPillars[p] + 0.005f) * scaleX, centerY - 0.35f * scaleY);
            glVertex2f(centerX + (frontPillars[p] + 0.005f) * scaleX, centerY + 0.01f * scaleY);
            glVertex2f(centerX + (frontPillars[p] - 0.005f) * scaleX, centerY + 0.01f * scaleY);
        glEnd();
    }

    // Shading  slits
    draw_horizontal_stripes(-0.44f, -0.16f, -0.38f, 0.02f, 0.03f, stoneDark[0], stoneDark[1], stoneDark[2], centerX, centerY, scaleX, scaleY);
    draw_horizontal_stripes(0.16f, 0.44f, -0.38f, 0.02f, 0.03f, stoneDark[0], stoneDark[1], stoneDark[2], centerX, centerY, scaleX, scaleY);

    // ==========================================
    // ENTRANCE GATE
    // ==========================================
    glColor3f(stoneLight[0], stoneLight[1], stoneLight[2]);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.14f * scaleX, centerY - 0.40f * scaleY); 
        glVertex2f(centerX + 0.14f * scaleX, centerY - 0.40f * scaleY);
        glVertex2f(centerX + 0.14f * scaleX, centerY + 0.02f * scaleY);  
        glVertex2f(centerX - 0.14f * scaleX, centerY + 0.02f * scaleY);
    glEnd();

    glColor3f(stoneDark[0], stoneDark[1], stoneDark[2]);
    glBegin(GL_POLYGON);
        glVertex2f(centerX - 0.09f * scaleX, centerY - 0.40f * scaleY);
        glVertex2f(centerX + 0.09f * scaleX, centerY - 0.40f * scaleY);
        glVertex2f(centerX + 0.09f * scaleX, centerY - 0.18f * scaleY);
        glVertex2f(centerX + 0.06f * scaleX, centerY - 0.10f * scaleY);
        glVertex2f(centerX,                  centerY - 0.04f * scaleY); 
        glVertex2f(centerX - 0.06f * scaleX, centerY - 0.10f * scaleY);
        glVertex2f(centerX - 0.09f * scaleX, centerY - 0.18f * scaleY);
    glEnd();

    glColor3f(0.18f, 0.16f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.045f * scaleX, centerY - 0.40f * scaleY); 
        glVertex2f(centerX + 0.045f * scaleX, centerY - 0.40f * scaleY);
        glVertex2f(centerX + 0.045f * scaleX, centerY - 0.16f * scaleY);  
        glVertex2f(centerX - 0.045f * scaleX, centerY - 0.16f * scaleY);
    glEnd();

    // ==========================================
    // PEDESTALS AND STEPS
    // ==========================================
    glColor3f(stoneDark[0], stoneDark[1], stoneDark[2]);
    glBegin(GL_QUADS);
        glVertex2f(centerX - 0.34f * scaleX, centerY - 0.55f * scaleY); 
        glVertex2f(centerX - 0.18f * scaleX, centerY - 0.55f * scaleY);
        glVertex2f(centerX - 0.18f * scaleX, centerY - 0.42f * scaleY); 
        glVertex2f(centerX - 0.34f * scaleX, centerY - 0.42f * scaleY);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(centerX + 0.18f * scaleX, centerY - 0.55f * scaleY);  
        glVertex2f(centerX + 0.34f * scaleX, centerY - 0.55f * scaleY);
        glVertex2f(centerX + 0.34f * scaleX, centerY - 0.42f * scaleY);  
        glVertex2f(centerX + 0.18f * scaleX, centerY - 0.42f * scaleY);
    glEnd();

    float st_y[] = {-0.75f, -0.64f, -0.53f, -0.42f};
    float st_w[] = {0.38f,  0.32f,  0.26f,  0.20f};

    for (int s = 0; s < 3; s++) {
        float factor = (float)s / 3.0f;
        glColor3f(stoneLight[0] - (factor * 0.12f), 
                  stoneLight[1] - (factor * 0.10f), 
                  stoneLight[2] - (factor * 0.08f));
                  
        glBegin(GL_QUADS);
            glVertex2f(centerX - st_w[s] * scaleX, centerY + st_y[s] * scaleY);
            glVertex2f(centerX + st_w[s] * scaleX, centerY + st_y[s] * scaleY);
            glVertex2f(centerX + st_w[s+1] * scaleX, centerY + st_y[s+1] * scaleY);
            glVertex2f(centerX - st_w[s+1] * scaleX, centerY + st_y[s+1] * scaleY);
        glEnd();
    }
}
