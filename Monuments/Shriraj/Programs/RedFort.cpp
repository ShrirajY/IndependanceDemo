// RedFort.cpp
#include "../../../core/Shriraj/Engine/Headers/Ng_shapes.h"
#include "../Headers/RedFort.h"


static float transformX(float x, float tx, float sx) { return x * sx + tx; }
static float transformY(float y, float ty, float sy) { return y * sy + ty; }
static float scaleThickness(float thickness, float sx, float sy) { return thickness * ((sx + sy) / 2.0f); }

static void drawScaledRectangle(float cx, float cy, float width, float height, float tx, float ty, float sx, float sy)
{
    Ng_drawRectangle(transformX(cx, tx, sx), transformY(cy, ty, sy), width * sx, height * sy);
}

static void drawScaledEllipse(float cx, float cy, float rx, float ry, float tx, float ty, float sx, float sy)
{
    Ng_drawEllipse(transformX(cx, tx, sx), transformY(cy, ty, sy), rx * sx, ry * sy);
}

static void drawScaledCircle(float cx, float cy, float radius, float tx, float ty, float sx, float sy)
{
    Ng_drawCircle(transformX(cx, tx, sx), transformY(cy, ty, sy), radius * ((sx + sy) / 2.0f));
}

static void drawScaledLine(float x1, float y1, float x2, float y2, float thickness, float tx, float ty, float sx, float sy)
{
    Ng_drawLine(transformX(x1, tx, sx), transformY(y1, ty, sy), transformX(x2, tx, sx), transformY(y2, ty, sy), scaleThickness(thickness, sx, sy));
}

static void drawScaledEllipseArc(float cx, float cy, float startAngle, float endAngle, float rx, float ry, float tx, float ty, float sx, float sy)
{
    Ng_drawEllipseArc(transformX(cx, tx, sx), transformY(cy, ty, sy), startAngle, endAngle, rx * sx, ry * sy);
}

// ---------------------------------------------------------------------
// Domes / chhatris
// ---------------------------------------------------------------------

static void drawDome(float cx, float baseY, float rx, float ry, float r, float g, float b, float tx, float ty, float sx, float sy)
{
    glColor3f(r, g, b);
    drawScaledEllipseArc(cx, baseY, 0.0f, 180.0f, rx, ry, tx, ty, sx, sy);
}

// Solid-drum chhatri - used for the small, distant roofline domes where
// pillars would be too fine to read.
static void drawChhatri(float cx, float baseY, float scale, float tx, float ty, float sx, float sy)
{
    float drumW = 0.10f * scale;
    float drumH = 0.05f * scale;
    float domeR = 0.065f * scale;

    glColor3f(0.72f, 0.30f, 0.24f);
    drawScaledRectangle(cx, baseY + drumH / 2.0f, drumW, drumH, tx, ty, sx, sy);

    drawDome(cx, baseY + drumH, domeR, domeR * 0.85f, 0.98f, 0.95f, 0.88f, tx, ty, sx, sy);

    float tipY = baseY + drumH + domeR * 0.85f;
    glColor3f(0.85f, 0.68f, 0.15f);
    drawScaledLine(cx, tipY, cx, tipY + 0.05f * scale, 2.0f, tx, ty, sx, sy);
    drawScaledCircle(cx, tipY + 0.05f * scale, 0.008f * scale, tx, ty, sx, sy);
}

static void drawPillaredChhatri(float cx, float baseY, float scale, float tx, float ty, float sx, float sy)
{
    float pillarSpan = 0.09f * scale;
    float pillarH = 0.075f * scale;
    float domeR = 0.075f * scale;

    // base platform
    glColor3f(0.72f, 0.30f, 0.24f);
    drawScaledRectangle(cx, baseY + 0.008f, pillarSpan * 1.35f, 0.016f, tx, ty, sx, sy);

    // four pillars
    glColor3f(0.95f, 0.92f, 0.85f);
    for (int i = 0; i < 4; i++)
    {
        float px = cx + (-1.5f + i) * (pillarSpan / 3.0f);
        drawScaledLine(px, baseY, px, baseY + pillarH, 2.0f, tx, ty, sx, sy);
    }

    // rim under the dome
    glColor3f(0.72f, 0.30f, 0.24f);
    drawScaledRectangle(cx, baseY + pillarH + 0.006f, pillarSpan * 1.4f, 0.012f, tx, ty, sx, sy);

    drawDome(cx, baseY + pillarH + 0.012f, domeR, domeR * 0.8f, 0.98f, 0.95f, 0.88f, tx, ty, sx, sy);

    float tipY = baseY + pillarH + 0.012f + domeR * 0.8f;
    glColor3f(0.85f, 0.68f, 0.15f);
    drawScaledLine(cx, tipY, cx, tipY + 0.045f * scale, 2.0f, tx, ty, sx, sy);
    drawScaledCircle(cx, tipY + 0.045f * scale, 0.007f * scale, tx, ty, sx, sy);
}

// ---------------------------------------------------------------------
// Minarets / guldastas
// ---------------------------------------------------------------------

static void drawMinaret(float cx, float baseY, float height, float width, float tx, float ty, float sx, float sy)
{
    glColor3f(0.80f, 0.36f, 0.28f);
    drawScaledRectangle(cx, baseY + height / 2.0f, width, height, tx, ty, sx, sy);

    glColor3f(0.55f, 0.20f, 0.16f);
    for (int i = 1; i <= 3; i++)
    {
        float y = baseY + height * (i / 4.0f);
        drawScaledRectangle(cx, y, width * 1.15f, 0.012f, tx, ty, sx, sy);
    }

    drawPillaredChhatri(cx, baseY + height, 0.55f, tx, ty, sx, sy);
}

static void drawGuldasta(float cx, float baseY, float tx, float ty, float sx, float sy)
{
    glColor3f(0.72f, 0.30f, 0.24f);
    drawScaledRectangle(cx, baseY + 0.03f, 0.02f, 0.06f, tx, ty, sx, sy);
    drawDome(cx, baseY + 0.06f, 0.014f, 0.014f, 0.98f, 0.95f, 0.88f, tx, ty, sx, sy);
}


static void drawScallopedMerlons(float xStart, float xEnd, float y, int count, float r, float g, float b, float tx, float ty, float sx, float sy)
{
    float span = xEnd - xStart;
    float step = span / count;
    float merlonW = step * 0.5f;
    float merlonH = 0.03f;

    glColor3f(r, g, b);
    for (int i = 0; i < count; i++)
    {
        float cx = xStart + step * (i + 0.5f);
        drawScaledRectangle(cx, y + merlonH / 2.0f, merlonW, merlonH, tx, ty, sx, sy);
        drawScaledEllipseArc(cx, y + merlonH, 0.0f, 180.0f, merlonW / 2.0f, merlonW / 2.0f * 0.8f, tx, ty, sx, sy);
    }
}

// ---------------------------------------------------------------------
// Arches
// ---------------------------------------------------------------------

static void drawArchNiche(float cx, float baseY, float width, float height, float r, float g, float b, float tx, float ty, float sx, float sy)
{
    glColor3f(r, g, b);
    drawScaledRectangle(cx, baseY + height / 2.0f, width, height, tx, ty, sx, sy);
    drawScaledEllipseArc(cx, baseY + height, 0.0f, 180.0f, width / 2.0f, width / 2.0f * 0.9f, tx, ty, sx, sy);
}

static void drawArchRow(float xStart, float xEnd, float baseY, int count, float widthFrac, float height, float r, float g, float b, float tx, float ty, float sx, float sy)
{
    float span = xEnd - xStart;
    float step = span / count;
    for (int i = 0; i < count; i++)
    {
        float cx = xStart + step * (i + 0.5f);
        drawArchNiche(cx, baseY, step * widthFrac, height, r, g, b, tx, ty, sx, sy);
    }
}


static void drawForegroundWall(float xStart, float xEnd, float baseY, float height, float tx, float ty, float sx, float sy)
{
    glColor3f(0.55f, 0.20f, 0.15f);
    drawScaledRectangle((xStart + xEnd) / 2.0f, baseY + height / 2.0f, xEnd - xStart, height, tx, ty, sx, sy);

    glColor3f(0.40f, 0.13f, 0.10f);
    for (int i = 1; i < 5; i++)
    {
        float y = baseY + height * (i / 5.0f);
        drawScaledLine(xStart, y, xEnd, y, 1.0f, tx, ty, sx, sy);
    }

    drawScallopedMerlons(xStart, xEnd, baseY + height, 22, 0.55f, 0.20f, 0.15f, tx, ty, sx, sy);
}

static void drawSteps(float cx, float baseY, float tx, float ty, float sx, float sy)
{
    glColor3f(0.62f, 0.62f, 0.62f);
    for (int i = 0; i < 4; i++)
    {
        float w = 0.28f - i * 0.05f;
        float y = baseY + i * 0.018f;
        drawScaledRectangle(cx, y, w, 0.02f, tx, ty, sx, sy);
    }
}

// ---------------------------------------------------------------------
// Top level
// ---------------------------------------------------------------------

void drawRedFort(float x, float y, float scaleX, float scaleY)
{
    // // sky
    // glColor3f(0.55f, 0.75f, 0.92f);
    // drawScaledRectangle(0.0f, 0.05f, 3.0f, 1.9f, x, y, scaleX, scaleY);

    // grassy mound in front of the main wall
    glColor3f(0.24f, 0.42f, 0.20f);
    drawScaledEllipse(0.0f, -0.46f, 0.42f, 0.09f, x, y, scaleX, scaleY);

    // --- main rampart wall ------------------------------------------------
    float wallLeft = -1.25f, wallRight = 1.25f;
    float wallBaseY = -0.55f, wallTopY = -0.12f;

    glColor3f(0.55f, 0.55f, 0.55f);
    drawScaledRectangle(0.0f, wallBaseY + 0.05f, wallRight - wallLeft, 0.10f, x, y, scaleX, scaleY);

    glColor3f(0.76f, 0.33f, 0.26f);
    drawScaledRectangle(0.0f, (wallBaseY + 0.1f + wallTopY) / 2.0f, wallRight - wallLeft, wallTopY - (wallBaseY + 0.1f), x, y, scaleX, scaleY);

    drawArchRow(wallLeft + 0.10f, wallRight - 0.10f, wallTopY - 0.14f, 20, 0.45f, 0.10f, 0.40f, 0.15f, 0.11f, x, y, scaleX, scaleY);

    drawScallopedMerlons(wallLeft + 0.05f, wallRight - 0.05f, wallTopY, 30, 0.76f, 0.33f, 0.26f, x, y, scaleX, scaleY);

    // guldastas dotted between the two arcade bands
    for (int i = -4; i <= 4; i++)
        if (i != 0)
            drawGuldasta(i * 0.14f, wallTopY, x, y, scaleX, scaleY);

    // --- corner bastions ----------------------------------------------
    for (int side = -1; side <= 1; side += 2)
    {
        float cx = side * 1.05f;
        float baseY = wallBaseY;
        float towerH = 0.68f;
        float towerW = 0.34f;

        glColor3f(0.78f, 0.35f, 0.27f);
        drawScaledRectangle(cx, baseY + towerH / 2.0f, towerW, towerH, x, y, scaleX, scaleY);

        // chamfered corner facets, to suggest the octagonal plan
        glColor3f(0.70f, 0.30f, 0.23f);
        // drawScaledRectangle(cx - towerW * 0.42f, baseY + towerH / 2.0f, towerW * 0.16f, towerH, x, y, scaleX, scaleY);
        // drawScaledRectangle(cx + towerW * 0.42f, baseY + towerH / 2.0f, towerW * 0.16f, towerH, x, y, scaleX, scaleY);

        // two stacked rows of arch niches on the tower face
        drawArchRow(cx - towerW * 0.32f, cx + towerW * 0.32f, baseY + towerH * 0.55f, 2, 0.55f, towerH * 0.20f, 0.32f, 0.10f, 0.08f, x, y, scaleX, scaleY);
        drawArchRow(cx - towerW * 0.32f, cx + towerW * 0.32f, baseY + towerH * 0.20f, 2, 0.55f, towerH * 0.20f, 0.32f, 0.10f, 0.08f, x, y, scaleX, scaleY);

        drawScallopedMerlons(cx - towerW / 2.0f, cx + towerW / 2.0f, baseY + towerH, 6, 0.78f, 0.35f, 0.27f, x, y, scaleX, scaleY);

        drawPillaredChhatri(cx - towerW * 0.28f, baseY + towerH, 0.55f, x, y, scaleX, scaleY);
        drawPillaredChhatri(cx,                  baseY + towerH, 0.95f, x, y, scaleX, scaleY);
        drawPillaredChhatri(cx + towerW * 0.28f, baseY + towerH, 0.55f, x, y, scaleX, scaleY);
    }

    // --- central gate block ---------------------------------------------
    float gateBaseY = wallTopY;
    float gateTopY = 0.42f;
    float gateHalfW = 0.34f;

    glColor3f(0.80f, 0.37f, 0.29f);
    drawScaledRectangle(0.0f, (gateBaseY + gateTopY) / 2.0f, gateHalfW * 2.0f, gateTopY - gateBaseY, x, y, scaleX, scaleY);

    // the archway opening itself
    glColor3f(0.15f, 0.08f, 0.06f);
    drawScaledRectangle(0.0f, gateBaseY + 0.12f, 0.18f, 0.24f, x, y, scaleX, scaleY);
    drawScaledEllipseArc(0.0f, gateBaseY + 0.24f, 0.0f, 180.0f, 0.09f, 0.09f, x, y, scaleX, scaleY);

    drawArchNiche(-0.20f, gateBaseY + 0.06f, 0.09f, 0.12f, 0.32f, 0.10f, 0.08f, x, y, scaleX, scaleY);
    drawArchNiche(0.20f, gateBaseY + 0.06f, 0.09f, 0.12f, 0.32f, 0.10f, 0.08f, x, y, scaleX, scaleY);

    // upper arcade band on the gate face, under the chhatri row
    drawArchRow(-gateHalfW + 0.03f, gateHalfW - 0.03f, gateTopY - 0.10f, 8, 0.45f, 0.08f, 0.40f, 0.15f, 0.11f, x, y, scaleX, scaleY);

    drawScallopedMerlons(-gateHalfW, gateHalfW, gateTopY, 10, 0.80f, 0.37f, 0.29f, x, y, scaleX, scaleY);

    // row of pillared chhatris along the top of the gate
    int chhatriCount = 7;
    for (int i = 0; i < chhatriCount; i++)
    {
        float t = (i + 0.5f) / (float)chhatriCount;
        float cx = -gateHalfW + t * (gateHalfW * 2.0f);
        drawPillaredChhatri(cx, gateTopY, 0.5f, x, y, scaleX, scaleY);
    }

    // minarets flanking the gate, inside the two bastions
    drawMinaret(-0.44f, gateBaseY, 0.55f, 0.045f, x, y, scaleX, scaleY);
    drawMinaret(0.44f, gateBaseY, 0.55f, 0.045f, x, y, scaleX, scaleY);

    float poleX = 0.03f;
    float poleBaseY = gateTopY + 0.02f;
    float poleTopY = poleBaseY + 0.56f;

    glColor3f(0.70f, 0.70f, 0.70f);
    drawScaledLine(poleX - 0.10f, poleBaseY, poleX, poleTopY, 0.8f, x, y, scaleX, scaleY);
    drawScaledLine(poleX + 0.10f, poleBaseY, poleX, poleTopY, 0.8f, x, y, scaleX, scaleY);

    glColor3f(0.85f, 0.85f, 0.85f);
    drawScaledLine(poleX, poleBaseY, poleX, poleTopY, 1.5f, x, y, scaleX, scaleY);

    float flagY = poleTopY - 0.10f;
    glColor3f(0.96f, 0.58f, 0.20f);
    drawScaledRectangle(poleX + 0.09f, flagY + 0.03f, 0.12f, 0.03f, x, y, scaleX, scaleY);
    glColor3f(0.95f, 0.95f, 0.95f);
    drawScaledRectangle(poleX + 0.09f, flagY, 0.12f, 0.03f, x, y, scaleX, scaleY);
    glColor3f(0.13f, 0.55f, 0.20f);
    drawScaledRectangle(poleX + 0.09f, flagY - 0.03f, 0.12f, 0.03f, x, y, scaleX, scaleY);
    glColor3f(0.05f, 0.05f, 0.45f);
    drawScaledCircle(poleX + 0.09f, flagY, 0.008f, x, y, scaleX, scaleY);

    // --- foreground boundary wall + railing + steps up to the flag -------
    drawForegroundWall(-1.3f, 1.3f, -0.65f, 0.20f, x, y, scaleX, scaleY);

    glColor3f(0.35f, 0.35f, 0.35f);
    drawScaledLine(-1.3f, -0.80f, 1.3f, -0.80f, 1.5f, x, y, scaleX, scaleY);
    for (float fx = -1.25f; fx <= 1.25f; fx += 0.12f)
        drawScaledLine(fx, -0.80f, fx, -0.86f, 1.0f, x, y, scaleX, scaleY);

    // drawSteps(poleX, -0.60f, x, y, scaleX, scaleY);
}

void drawRedFort()
{
    drawRedFort(0.0f, 0.0f, 1.0f, 1.0f);
}

void draw_redfort(float x, float y, float scaleX, float scaleY)
{
    drawRedFort(x, y, scaleX, scaleY);
}