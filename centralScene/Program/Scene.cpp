#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include <cmath>
#include "../Header/Scene.h"
#include "../../outro/Headers/musicnotes.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float currentScale = 0.05f;  
float rotationAngle = 0.0f;   

extern void drawKonark(float centerX, float centerY, float scaleX, float scaleY);

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float baseRadius = 0.5f; 
    int totalNotes = 6;

    for (int i = 0; i < totalNotes; i++) {
        float currentAngle = (i * (2.0f * M_PI / totalNotes)) + rotationAngle;
        
        float noteX = cos(currentAngle) * (baseRadius * currentScale);
        float noteY = sin(currentAngle) * (baseRadius * currentScale);

        int noteType = i % 4;
        if (noteType == 0) {
            drawQuarterNote(noteX, noteY, currentScale);
        } else if (noteType == 1) {
            drawSharpNote(noteX, noteY, currentScale);
        } else if (noteType == 2) {
            drawHalfNote(noteX, noteY, currentScale);
        } else {
            drawBeamedEighthNotes(noteX, noteY, currentScale);
        }
    }

    glutSwapBuffers();
}

void timer(int value) {
    currentScale += 0.012f; 

    if (currentScale > 2.0f) {
        currentScale = 0.05f; 
    }

    rotationAngle += 0.015f; 
    if (rotationAngle > 2.0f * M_PI) {
        rotationAngle -= 2.0f * M_PI;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Concentric Circles with Musical Notes");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
