#include <GL/freeglut.h>
#include <math.h>
#include "include/AgraFort.h"

float sineLerp(float a, float b, float t) {
    float sineFactor = (sinf(t * 3.14159265f - 1.57079632f) + 1.0f) * 0.5f;
    return a + sineFactor * (b - a);
}

void drawGradientQuad(float centerX, float centerY, float width, float height, int segments, float dr, float dg, float db, float lr, float lg, float lb) {
    float startX = centerX - (width / 2.0f);
    float startY = centerY - (height / 2.0f);

    glBegin(GL_QUADS);
    for (int i = 0; i < segments; i++) {
        float factBottom = sqrtf((float)i / segments);
        float rBottom = sineLerp(dr, lr, factBottom);
        float gBottom = sineLerp(dg, lg, factBottom);
        float bBottom = sineLerp(db, lb, factBottom);

        float factTop = sqrtf((float)(i + 1) / segments);
        float rTop = sineLerp(dr, lr, factTop);
        float gTop = sineLerp(dg, lg, factTop);
        float bTop = sineLerp(db, lb, factTop);

        float yBottom = startY + (height * ((float)i / segments));
        float yTop = startY + (height * ((float)(i + 1) / segments));

        glColor3f(rBottom, gBottom, bBottom);
        glVertex2f(startX, yBottom);
        glVertex2f(startX + width, yBottom);

        glColor3f(rTop, gTop, bTop);
        glVertex2f(startX + width, yTop);
        glVertex2f(startX, yTop);
    }
    glEnd();
}

void drawMughalArch(float centerX, float bottomY, float baseWidth, float height, int segments, float dr, float dg, float db, float lr, float lg, float lb) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / (float)segments;
        float fact = sqrtf(t);

        float r = sineLerp(dr, lr, fact);
        float g = sineLerp(dg, lg, fact);
        float b = sineLerp(db, lb, fact);

        glColor3f(r, g, b);

        float currentY = bottomY + (t * height);
        float currentHalfWidth = (baseWidth / 2.0f) * (1.0f - powf(t, 1.5f));

        glVertex2f(centerX - currentHalfWidth, currentY);
        glVertex2f(centerX + currentHalfWidth, currentY);
    }
    glEnd();
}

void mughalDesign(float x, float y, float z, float length, float width, float dr, float dg, float db, float lr, float lg, float lb) {
    float archHeight = length * 0.43f;
    float quadHeight = length * 0.57f;

    drawMughalArch(x, y, width, archHeight, 30, dr, dg, db, lr, lg, lb);
    drawGradientQuad(x, y - (quadHeight * 0.5f), width, quadHeight, 15, dr, dg, db, lr, lg, lb);
}

void drawFrontWall(float centerX, float centerY, float length, float height, int numTeeth, float dr, float dg, float db, float lr, float lg, float lb, float teethR, float teethG, float teethB) {
    drawGradientQuad(centerX, centerY, length, height, 20, dr, dg, db, lr, lg, lb);

    float designWidth = length / (2.0f * numTeeth - 1.0f);
    float designLength = 0.12f;
    float startX = centerX - (length / 2.0f) + (designWidth / 2.0f);
    float designY = centerY + (height / 2.0f);

    for (int i = 0; i < numTeeth; i++) {
        float tx = startX + i * (designWidth * 2.0f);
        drawQuad(tx, designY - 0.015f + (designLength / 2.0f), designWidth + 0.025f, designLength - 0.01f, teethR, teethG, teethB);
        mughalDesign(tx, designY + 0.056f, 0.0f, designLength, designWidth, teethR * 0.8f, teethG * 0.8f, teethB * 0.8f, 0.369f, 0.204f, 0.0f);
    }
}

void drawPillar(float x, float y, float width, float height, float dr, float dg, float db, float lr, float lg, float lb, float teethR, float teethG, float teethB) {
    drawQuad(x, y - (height / 2.0f) + (height * 0.06f), width * 1.15f, height * 0.12f, dr, dg, db);
    drawGradientQuad(x, y, width, height * 0.76f, 20, dr, dg, db, lr, lg, lb);
    drawQuad(x, y + (height / 2.0f) - (height * 0.06f), width * 1.2f, height * 0.12f, teethR, teethG, teethB);
}

void drawWindow(float x, float y, float width, float height) {
    float frameR = 0.88f, frameG = 0.72f, frameB = 0.53f;
    float innerR = 0.20f, innerG = 0.08f, innerB = 0.03f;

    mughalDesign(x, y, 0.0f, height, width, frameR * 0.9f, frameG * 0.9f, frameB * 0.9f, frameR, frameG, frameB);
    mughalDesign(x, y - (height * 0.05f), 0.0f, height * 0.8f, width * 0.75f, innerR * 0.6f, innerG * 0.6f, innerB * 0.6f, innerR, innerG, innerB);
}

void DrawAgraFortScene(float x, float y, float scale) {
    float darkR = 0.36f, darkG = 0.15f, darkB = 0.05f;
    float medR = 0.65f, medG = 0.32f, medB = 0.09f;
    float orgR = 0.93f, orgG = 0.49f, orgB = 0.10f;
    float pchR = 0.98f, pchG = 0.67f, pchB = 0.37f;
    float crmR = 0.92f, crmG = 0.88f, crmB = 0.78f;

    drawFrontWall((0.0f * scale) + x, (0.1f * scale) + y, 1.4f * scale, 0.9f * scale, 18, darkR * 0.8f, darkG * 0.8f, darkB * 0.8f, darkR, darkG, darkB, pchR, pchG, pchB);
    drawFrontWall((-0.55f * scale) + x, (-0.119f * scale) + y, 0.5f * scale, 1.0f * scale, 7, medR * 0.8f, medG * 0.8f, medB * 0.8f, medR, medG, medB, pchR, pchG, pchB);
    drawFrontWall((0.55f * scale) + x, (-0.119f * scale) + y, 0.5f * scale, 1.0f * scale, 7, medR * 0.8f, medG * 0.8f, medB * 0.8f, medR, medG, medB, pchR, pchG, pchB);
    drawFrontWall((0.0f * scale) + x, (-0.05f * scale) + y, 0.5f * scale, 1.7f * scale, 7, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    drawFrontWall((-0.55f * scale) + x, (-0.5f * scale) + y, 0.9f * scale, 0.4f * scale, 10, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    drawFrontWall((0.55f * scale) + x, (-0.5f * scale) + y, 0.9f * scale, 0.4f * scale, 10, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    drawPillar((-0.3f * scale) + x, (-0.36f * scale) + y, 0.42f * scale, 0.85f * scale, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    drawPillar((0.3f * scale) + x, (-0.36f * scale) + y, 0.42f * scale, 0.85f * scale, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    drawGradientQuad((0.0f * scale) + x, (-0.35f * scale) + y, 0.45f * scale, 0.7f * scale, 15, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB);
    drawFrontWall((0.0f * scale) + x, (0.05f * scale) + y, 0.55f * scale, 0.2f * scale, 5, orgR * 0.8f, orgG * 0.8f, orgB * 0.8f, orgR, orgG, orgB, pchR, pchG, pchB);
    mughalDesign((0.0f * scale) + x, (-0.45f * scale) + y, 0.0f, 0.75f * scale, 0.39f * scale, crmR * 0.9f, crmG * 0.9f, crmB * 0.9f, crmR, crmG, crmB);
    mughalDesign((0.0f * scale) + x, (-0.49f * scale) + y, 0.0f, 0.6f * scale, 0.29f * scale, darkR * 0.6f, darkG * 0.6f, darkB * 0.6f, darkR, darkG, darkB);

    drawWindow((0.0f * scale) + x, (0.45f * scale) + y, 0.09f * scale, 0.22f * scale);
    drawWindow((-0.17f * scale) + x, (0.45f * scale) + y, 0.09f * scale, 0.22f * scale);
    drawWindow((0.17f * scale) + x, (0.45f * scale) + y, 0.09f * scale, 0.22f * scale);
    drawWindow((-0.55f * scale) + x, (0.23f * scale) + y, 0.19f * scale, 0.22f * scale);
    drawWindow((0.55f * scale) + x, (0.23f * scale) + y, 0.19f * scale, 0.22f * scale);
}