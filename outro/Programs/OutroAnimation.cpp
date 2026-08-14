#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/freeglut.h>
#include "../Headers/OutroAnimation.h"


// Adjust relative path if needed based on your project layout
#include "../Headers/musicnotes.h"

static float currentScale = 0.05f;
static float rotationAngle = 0.0f;

void InitOutroAnimation() {
    currentScale = 0.05f;
    rotationAngle = 0.0f;
}

void DrawOutroAnimationStep(float deltaTime) {
    // Update internal animation state based on frame delta
    currentScale += 0.012f;
    if (currentScale > 2.0f) {
        currentScale = 0.05f;
    }

    rotationAngle += 0.015f;
    if (rotationAngle > 2.0f * (float)M_PI) {
        rotationAngle -= 2.0f * (float)M_PI;
    }

    // Render the notes
    float baseRadius = 0.5f;
    int totalNotes = 6;

    for (int i = 0; i < totalNotes; i++) {
        float currentAngle = (i * (2.0f * (float)M_PI / totalNotes)) + rotationAngle;
        
        float noteX = cosf(currentAngle) * (baseRadius * currentScale);
        float noteY = sinf(currentAngle) * (baseRadius * currentScale);

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
}