// blend_intro.h
// -----------------------------------------------------------------------
// Self-contained BLEND -> INDIA intro, reduced to one function you call
// every frame from your OWN display():
//
//     bool done = DrawIndiaBlendIntro(deltaTime);
//
// It handles its own glClear()/drawing while the intro is running (wake
// -> vehicles -> flag morph -> hold -> 2s black), and once it's fully
// finished it returns true FOREVER after and does nothing further — at
// that point your main program's display code takes over completely.
//
// Typical wiring in your main program's display():
//
//     void display(void)
//     {
//         static bool introDone = false;
//         if (!introDone)
//             introDone = DrawIndiaBlendIntro(deltaTime);
//
//         if (introDone)
//         {
//             glClear(GL_COLOR_BUFFER_BIT);
//             glMatrixMode(GL_MODELVIEW);
//             glLoadIdentity();
//             // ... your existing monument-sequence drawing here ...
//         }
//
//         glutSwapBuffers();
//     }
//
// Nothing else needs to change in your resize()/timer() - this reuses
// whatever ortho projection your program's own resize() already sets up
// (same -aspect..aspect / -1..1 style), and just needs a deltaTime each
// call (0.016f if you're driving it from a 16ms glutTimerFunc, same as
// the rest of your project).
//
// Build: same as the rest of your project (g++ / cl.exe + freeglut).
// -----------------------------------------------------------------------

#ifndef BLEND_INTRO_H
#define BLEND_INTRO_H

#include <GL/freeglut.h>
#include <vector>
#include <utility>   // std::pair
#include <cctype>
#include <cstddef>   // std::size_t
#include <cmath>     // std::sqrt, std::atan2, std::fabs, std::sin, std::cos
#include <algorithm> // std::min, std::max
#include <cstring>   // std::strcpy

namespace blend_intro_detail {

static inline float clamp01(float t) { return t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t); }
static inline float lerp(float a, float b, float t) { return a + (b - a) * t; }

// -----------------------------------------------------------------------
// Basic filled-shape primitives.
// -----------------------------------------------------------------------

static void drawRectangle(float x, float y, float width, float height)
{
    float leftX = x - (width / 2.0f);
    float leftY = y + (height / 2.0f);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(leftX, leftY, 0.0f);
    glVertex3f(leftX + width, leftY, 0.0f);
    glVertex3f(leftX, leftY - height, 0.0f);
    glVertex3f(leftX + width, leftY - height, 0.0f);
    glEnd();
}

static void rotatePoint(float x, float y, float angleDeg, float refX, float refY, float *outX, float *outY)
{
    float angle = 3.14159265f / 180.0f * angleDeg;

    x -= refX;
    y -= refY;

    *outX = x * std::cos(angle) - y * std::sin(angle);
    *outY = y * std::cos(angle) + x * std::sin(angle);

    *outX += refX;
    *outY += refY;
}

static void drawRotatedRectangle(float x, float y, float width, float height, float angleDeg)
{
    float cornersX[4] = {-width / 2.0f, width / 2.0f, width / 2.0f, -width / 2.0f};
    float cornersY[4] = {height / 2.0f, height / 2.0f, -height / 2.0f, -height / 2.0f};

    float rx[4], ry[4];
    for (int i = 0; i < 4; i++)
        rotatePoint(x + cornersX[i], y + cornersY[i], angleDeg, x, y, &rx[i], &ry[i]);

    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(rx[0], ry[0], 0.0f);
    glVertex3f(rx[1], ry[1], 0.0f);
    glVertex3f(rx[3], ry[3], 0.0f);
    glVertex3f(rx[2], ry[2], 0.0f);
    glEnd();
}

static void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x2, y2, 0.0f);
    glVertex3f(x3, y3, 0.0f);
    glEnd();
}

static void drawFilledCircle(float x, float y, float r)
{
    const float PI = 3.14159265f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0f);
    for (int i = 0; i <= 32; i++)
    {
        float angle = 2.0f * PI * (float)i / 32.0f;
        glVertex3f(x + r * std::cos(angle), y + r * std::sin(angle), 0.0f);
    }
    glEnd();
}

// -----------------------------------------------------------------------
// Letter glyph data - 4 (wide) x 6 (tall) design grid, in GRID space
// (tricolor bands are cut at fixed grid-Y values, so clipping happens
// before the grid -> world transform).
// -----------------------------------------------------------------------

typedef std::vector<std::pair<float, float>> Stroke; // one polyline, in grid space
typedef std::vector<Stroke> Glyph;

static void getGlyph(char c, Glyph &g)
{
    switch (std::toupper(static_cast<unsigned char>(c)))
    {
    case 'A':
        g.push_back(Stroke{{0.0f, 0.0f}, {2.0f, 6.0f}, {4.0f, 0.0f}});
        g.push_back(Stroke{{0.8f, 2.0f}, {3.2f, 2.0f}});
        break;
    case 'B':
        g.push_back(Stroke{{0.0f, 0.0f}, {0.0f, 6.0f}, {2.5f, 6.0f}, {3.2f, 5.3f}, {3.2f, 3.7f}, {2.5f, 3.0f}, {0.0f, 3.0f}});
        g.push_back(Stroke{{0.0f, 3.0f}, {2.7f, 3.0f}, {3.4f, 2.3f}, {3.4f, 0.7f}, {2.7f, 0.0f}, {0.0f, 0.0f}});
        break;
    case 'D':
        g.push_back(Stroke{{0.0f, 0.0f}, {0.0f, 6.0f}, {2.0f, 6.0f}, {4.0f, 4.0f}, {4.0f, 2.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}});
        break;
    case 'E':
        g.push_back(Stroke{{4.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 6.0f}, {4.0f, 6.0f}});
        g.push_back(Stroke{{0.0f, 3.0f}, {3.0f, 3.0f}});
        break;
    case 'I':
        g.push_back(Stroke{{1.0f, 0.0f}, {3.0f, 0.0f}});
        g.push_back(Stroke{{2.0f, 0.0f}, {2.0f, 6.0f}});
        g.push_back(Stroke{{1.0f, 6.0f}, {3.0f, 6.0f}});
        break;
    case 'L':
        g.push_back(Stroke{{0.0f, 6.0f}, {0.0f, 0.0f}, {4.0f, 0.0f}});
        break;
    case 'N':
        g.push_back(Stroke{{0.0f, 0.0f}, {0.0f, 6.0f}, {4.0f, 0.0f}, {4.0f, 6.0f}});
        break;
    default:
        break; // only glyphs BLEND+INDIA need are included
    }
}

// -----------------------------------------------------------------------
// Grid -> world mapping and tricolor band drawing.
// -----------------------------------------------------------------------

static inline void letterGridToWorld(float gridX, float gridY,
                                      float centerX, float centerY,
                                      float scaleX, float scaleY,
                                      float *outX, float *outY)
{
    const float UNIT = 1.0f / 6.0f;
    *outX = centerX + (gridX - 2.0f) * UNIT * scaleX;
    *outY = centerY + (gridY - 3.0f) * UNIT * scaleY;
}

// Indian flag colors: saffron / white / India green.
// band 0 = bottom -> green when "activated" (tank passed)
// band 1 = middle -> always white
// band 2 = top    -> orange when "activated" (jet passed)
static void setBandColorEx(int band, bool topActive, bool bottomActive)
{
    if (band == 0)
    {
        if (bottomActive)
            glColor3f(0.0745f, 0.5333f, 0.0314f); // green
        else
            glColor3f(1.0f, 1.0f, 1.0f);
    }
    else if (band == 1)
    {
        glColor3f(1.0f, 1.0f, 1.0f); // middle always white
    }
    else
    {
        if (topActive)
            glColor3f(1.0f, 0.6f, 0.2f); // orange
        else
            glColor3f(1.0f, 1.0f, 1.0f);
    }
}

static void drawThickSegmentWorld(float x1, float y1, float x2, float y2, float thickness)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx * dx + dy * dy);

    if (length > 1e-6f)
    {
        float midX = (x1 + x2) * 0.5f;
        float midY = (y1 + y2) * 0.5f;

        const float EPS = 1e-4f;
        if (std::fabs(dy) < EPS)
            drawRectangle(midX, midY, length, thickness);
        else if (std::fabs(dx) < EPS)
            drawRectangle(midX, midY, thickness, length);
        else
        {
            float angleDeg = std::atan2(dy, dx) * (180.0f / 3.14159265f);
            drawRotatedRectangle(midX, midY, length, thickness, angleDeg);
        }
    }

    drawRectangle(x1, y1, thickness, thickness);
    drawRectangle(x2, y2, thickness, thickness);
}

static void drawTricolorSegmentEx(float gx1, float gy1, float gx2, float gy2,
                                   float centerX, float centerY,
                                   float scaleX, float scaleY,
                                   float thickness, bool topActive, bool bottomActive)
{
    static const float BAND_BOUNDS[4] = {0.0f, 2.0f, 4.0f, 6.0f};

    if (std::fabs(gy2 - gy1) < 1e-5f)
    {
        int band = (gy1 < 2.0f) ? 0 : (gy1 < 4.0f) ? 1 : 2;
        float wx1, wy1, wx2, wy2;
        letterGridToWorld(gx1, gy1, centerX, centerY, scaleX, scaleY, &wx1, &wy1);
        letterGridToWorld(gx2, gy2, centerX, centerY, scaleX, scaleY, &wx2, &wy2);
        setBandColorEx(band, topActive, bottomActive);
        drawThickSegmentWorld(wx1, wy1, wx2, wy2, thickness);
        return;
    }

    float minY = std::min(gy1, gy2);
    float maxY = std::max(gy1, gy2);

    for (int band = 0; band < 3; band++)
    {
        float bandLo = BAND_BOUNDS[band];
        float bandHi = BAND_BOUNDS[band + 1];

        float loY = std::max(minY, bandLo);
        float hiY = std::min(maxY, bandHi);
        if (loY >= hiY)
            continue;

        float t0 = (loY - gy1) / (gy2 - gy1);
        float t1 = (hiY - gy1) / (gy2 - gy1);
        float tA = std::min(t0, t1);
        float tB = std::max(t0, t1);

        float subGX1 = gx1 + (gx2 - gx1) * tA;
        float subGY1 = gy1 + (gy2 - gy1) * tA;
        float subGX2 = gx1 + (gx2 - gx1) * tB;
        float subGY2 = gy1 + (gy2 - gy1) * tB;

        float wx1, wy1, wx2, wy2;
        letterGridToWorld(subGX1, subGY1, centerX, centerY, scaleX, scaleY, &wx1, &wy1);
        letterGridToWorld(subGX2, subGY2, centerX, centerY, scaleX, scaleY, &wx2, &wy2);

        setBandColorEx(band, topActive, bottomActive);
        drawThickSegmentWorld(wx1, wy1, wx2, wy2, thickness);
    }
}

static void drawLetterAnimated(char c, float baselineCenterX, float baselineY,
                                float scaleX, float baseScaleY, float thickness,
                                float heightScale, float widthPulse,
                                bool topActive, bool bottomActive)
{
    Glyph glyph;
    getGlyph(c, glyph);
    if (glyph.empty())
        return;

    float scaleY = baseScaleY * heightScale;
    if (scaleY < 0.001f)
        scaleY = 0.001f;
    float scaleXEff = scaleX * widthPulse;

    const float UNIT = 1.0f / 6.0f;
    float adjustedCenterY = baselineY + 3.0f * UNIT * scaleY;

    for (std::size_t s = 0; s < glyph.size(); s++)
    {
        const Stroke &stroke = glyph[s];
        for (std::size_t p = 0; p + 1 < stroke.size(); p++)
        {
            drawTricolorSegmentEx(stroke[p].first, stroke[p].second,
                                   stroke[p + 1].first, stroke[p + 1].second,
                                   baselineCenterX, adjustedCenterY,
                                   scaleXEff, scaleY, thickness,
                                   topActive, bottomActive);
        }
    }
}


static int computeWordLetterCenters(int len, float centerX, float scaleX,
                                     float letterSpacing, float *outCenters)
{
    if (len <= 0)
        return 0;

    const float glyphWidth = (4.0f / 6.0f) * scaleX;
    float totalWidth = len * glyphWidth + (len - 1) * letterSpacing;
    float cursorX = centerX - totalWidth / 2.0f + glyphWidth / 2.0f;

    for (int i = 0; i < len; i++)
    {
        outCenters[i] = cursorX;
        cursorX += glyphWidth + letterSpacing;
    }
    return len;
}

static float easeOutBack(float t)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;
    t = clamp01(t);
    float x = t - 1.0f;
    return 1.0f + c3 * x * x * x + c1 * x * x;
}

// -----------------------------------------------------------------------
// Vehicles.
// -----------------------------------------------------------------------

static void drawJet(float x, float y, float scale)
{
    glColor3f(0.35f, 0.38f, 0.42f);
    drawRectangle(x, y, 0.30f * scale, 0.055f * scale);
    drawTriangle(x + 0.15f * scale, y + 0.0275f * scale,
                 x + 0.15f * scale, y - 0.0275f * scale,
                 x + 0.24f * scale, y);
    drawTriangle(x - 0.15f * scale, y + 0.02f * scale,
                 x - 0.10f * scale, y + 0.02f * scale,
                 x - 0.15f * scale, y + 0.08f * scale);
    glColor3f(0.55f, 0.58f, 0.6f);
    drawTriangle(x - 0.02f * scale, y - 0.02f * scale,
                 x + 0.06f * scale, y - 0.02f * scale,
                 x - 0.06f * scale, y - 0.11f * scale);
    glColor3f(0.6f, 0.85f, 0.95f);
    drawFilledCircle(x + 0.06f * scale, y + 0.01f * scale, 0.02f * scale);
}

static void drawTank(float x, float y, float scale)
{
    glColor3f(0.15f, 0.15f, 0.16f);
    drawRectangle(x, y - 0.02f * scale, 0.34f * scale, 0.05f * scale);
    for (int i = -2; i <= 2; i++)
        drawFilledCircle(x + i * 0.06f * scale, y - 0.02f * scale, 0.025f * scale);

    glColor3f(0.30f, 0.38f, 0.22f);
    drawRectangle(x, y + 0.02f * scale, 0.28f * scale, 0.06f * scale);

    glColor3f(0.26f, 0.33f, 0.19f);
    drawFilledCircle(x - 0.02f * scale, y + 0.065f * scale, 0.05f * scale);

    drawRectangle(x + 0.12f * scale, y + 0.065f * scale, 0.16f * scale, 0.014f * scale);
}

// -----------------------------------------------------------------------
// Animation state - all static, so the whole intro lives behind one
// externally-visible function (see DrawIndiaBlendIntro below).
// -----------------------------------------------------------------------

enum Phase
{
    PHASE_WAKE,
    PHASE_VEHICLES,
    PHASE_FLAG,
    PHASE_DONE,
    PHASE_BLACKOUT,
    PHASE_FINISHED
};

static Phase g_phase = PHASE_WAKE;
static float g_phaseStartTime = 0.0f;
static float g_elapsedTimeSeconds = 0.0f;
static bool g_initialized = false;

static const char *SRC_WORD = "BLEND";
static const char *DST_WORD = "INDIA";
static const int WORD_LEN = 5;
static char g_word[WORD_LEN + 1] = "BLEND";
static bool g_morphed[WORD_LEN] = {false, false, false, false, false};
static float g_morphTime[WORD_LEN] = {0, 0, 0, 0, 0};
static float g_letterCenters[WORD_LEN];

static const float LETTER_CENTER_Y = -0.45f;
static const float LETTER_SCALE_X = 0.5f;
static const float LETTER_SCALE_Y = 0.5f;
static const float LETTER_SPACING = 0.15f;
static const float LETTER_THICKNESS = 0.05f;

static const float WAKE_STAGGER = 0.35f;
static const float WAKE_DURATION = 0.6f;
static const float WAKE_SETTLE_PAUSE = 0.2f;

static const float VEHICLE_TRAVEL_MIN = -3.0f;
static const float VEHICLE_TRAVEL_MAX =  3.0f;
static const float JET_DURATION = 8.0f;
static const float TANK_DURATION = 8.0f;
static const float VEHICLE_PHASE_DURATION = 7.0f;

static const float FLAG_SWEEP_DURATION = 8.0f;
static const float MORPH_POP_DURATION = 0.35f;

static const float DONE_HOLD_DURATION = 1.0f;      // "INDIA" sits tricolor before the blackout
static const float BLACKOUT_DURATION = 0.0f;        // <-- the 2 seconds of black between intro and main program

} // namespace blend_intro_detail

// The one function you call, every frame, from your display(). Returns
// false while the intro (including its trailing 2s blackout) is still
// playing; once it returns true, it has finished for good and does
// nothing further on every subsequent call - your main program's own
// drawing takes over from there.
inline bool DrawIndiaBlendIntro(float deltaTime = 0.016f)
{
    using namespace blend_intro_detail;

    if (g_phase == PHASE_FINISHED)
        return true;

    if (!g_initialized)
    {
        computeWordLetterCenters(WORD_LEN, 0.0f, LETTER_SCALE_X, LETTER_SPACING, g_letterCenters);
        g_phaseStartTime = 0.0f;
        g_initialized = true;
    }

    g_elapsedTimeSeconds += deltaTime;
    float localT = g_elapsedTimeSeconds - g_phaseStartTime;

    // Blackout is drawn (and exited) before anything else, since it has
    // no letters/vehicles to compute.
    if (g_phase == PHASE_BLACKOUT)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (localT >= BLACKOUT_DURATION)
            g_phase = PHASE_FINISHED;

        return (g_phase == PHASE_FINISHED);
    }

    glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float heightScale[WORD_LEN];
    float widthPulse[WORD_LEN];
    bool topActive[WORD_LEN];
    bool bottomActive[WORD_LEN];
    for (int i = 0; i < WORD_LEN; i++)
    {
        heightScale[i] = 1.0f;
        widthPulse[i] = 1.0f;
        topActive[i] = false;
        bottomActive[i] = false;
    }

    if (g_phase == PHASE_WAKE)
    {
        bool allAwake = true;
        for (int i = 0; i < WORD_LEN; i++)
        {
            float t = clamp01((localT - i * WAKE_STAGGER) / WAKE_DURATION);
            if (t < 1.0f)
                allAwake = false;
            heightScale[i] = lerp(0.06f, 1.0f, easeOutBack(t));
            if (heightScale[i] < 0.06f)
                heightScale[i] = 0.06f;
        }

        if (allAwake && localT - ((WORD_LEN - 1) * WAKE_STAGGER + WAKE_DURATION) >= WAKE_SETTLE_PAUSE)
        {
            g_phase = PHASE_VEHICLES;
            g_phaseStartTime = g_elapsedTimeSeconds;
        }
    }
    else if (g_phase == PHASE_VEHICLES)
    {
        float jetSpeed = (VEHICLE_TRAVEL_MAX - VEHICLE_TRAVEL_MIN) / JET_DURATION;
        float tankSpeed = (VEHICLE_TRAVEL_MAX - VEHICLE_TRAVEL_MIN) / TANK_DURATION;
        float jetX = VEHICLE_TRAVEL_MIN + jetSpeed * localT;
        float tankX = VEHICLE_TRAVEL_MIN + tankSpeed * localT;

        for (int i = 0; i < WORD_LEN; i++)
        {
            topActive[i] = jetX > g_letterCenters[i];
            bottomActive[i] = tankX > g_letterCenters[i];
        }

        float jetY = 0.0f;
        float tankY = -0.4f;

        if (localT < JET_DURATION + 2.0f)
            drawJet(jetX, jetY, 0.85f);
        if (localT < TANK_DURATION + 2.0f)
            drawTank(tankX, tankY, 0.85f);

        if (localT >= VEHICLE_PHASE_DURATION)
        {
            g_phase = PHASE_FLAG;
            g_phaseStartTime = g_elapsedTimeSeconds;
        }
    }
    else if (g_phase == PHASE_FLAG)
    {
        for (int i = 0; i < WORD_LEN; i++)
        {
            topActive[i] = true;
            bottomActive[i] = true;
        }

        float sweepSpeed = (VEHICLE_TRAVEL_MAX - VEHICLE_TRAVEL_MIN) / FLAG_SWEEP_DURATION;
        float sweepX = VEHICLE_TRAVEL_MIN + sweepSpeed * localT;

        bool allMorphed = true;
        for (int i = 0; i < WORD_LEN; i++)
        {
            if (!g_morphed[i] && sweepX > g_letterCenters[i])
            {
                g_morphed[i] = true;
                g_morphTime[i] = g_elapsedTimeSeconds;
                g_word[i] = DST_WORD[i];
            }
            if (!g_morphed[i])
                allMorphed = false;
        }

        for (int i = 0; i < WORD_LEN; i++)
        {
            if (g_morphed[i])
            {
                float pt = clamp01((g_elapsedTimeSeconds - g_morphTime[i]) / MORPH_POP_DURATION);
                float pop = std::sin(pt * 3.14159265f) * (1.0f - pt);
                heightScale[i] = 1.0f + 0.35f * pop;
                widthPulse[i] = 1.0f + 0.15f * pop;
            }
        }

        glColor3f(1.0f, 0.6f, 0.2f);
        drawRectangle(sweepX, 0.0f, 0.7f, 0.2f);
        glColor3f(1.0f, 1.0f, 1.0f);
        drawRectangle(sweepX, -0.2f, 0.7f, 0.2f);
        glColor3f(0.0745f, 0.5333f, 0.0314f);
        drawRectangle(sweepX, -0.4f, 0.7f, 0.2f);

        if (allMorphed && localT >= FLAG_SWEEP_DURATION)
        {
            g_phase = PHASE_DONE;
            g_phaseStartTime = g_elapsedTimeSeconds;
        }
    }
    else if (g_phase == PHASE_DONE)
    {
        // "INDIA" sits fully tricolor, no sweep bar, until the hold ends.
        for (int i = 0; i < WORD_LEN; i++)
        {
            topActive[i] = true;
            bottomActive[i] = true;
        }

        if (localT >= DONE_HOLD_DURATION)
        {
            g_phase = PHASE_BLACKOUT;
            g_phaseStartTime = g_elapsedTimeSeconds;
        }
    }

    for (int i = 0; i < WORD_LEN; i++)
    {
        drawLetterAnimated(g_word[i], g_letterCenters[i], LETTER_CENTER_Y,
                            LETTER_SCALE_X, LETTER_SCALE_Y, LETTER_THICKNESS,
                            heightScale[i], widthPulse[i],
                            topActive[i], bottomActive[i]);
    }

    return false;
}

#endif // BLEND_INTRO_H