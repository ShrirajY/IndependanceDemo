/*
 * india_map_draw.h
 *
 * Drop-in, single-function version of the India outline map.
 * Call drawIndiaMap(cx, cy, scale) once per frame from YOUR display()
 * function. It keeps its own progress state internally (as statics), so
 * every call just draws a little more of the map than the last one —
 * you don't need to manage any globals or write a dedicated timer for it.
 * Your program's existing timer (the one that calls glutPostRedisplay())
 * is all the "timer" this needs.
 *
 * Usage:
 *     #include "india_map_draw.h"
 *
 *     void display(void) {
 *         glClearColor(0,0,0,1);
 *         glClear(GL_COLOR_BUFFER_BIT);
 *         drawIndiaMap(0.0f, 0.0f, 1.0f);   // centered, natural size
 *         glutSwapBuffers();
 *     }
 *
 * To restart the draw-in animation from scratch (e.g. on a key press):
 *     drawIndiaMap(0.0f, 0.0f, 1.0f, true);   // reset = true
 *
 * cx, cy   : where to center the map in your current GL coordinate space
 * scale    : 1.0 = the map normalized to fit within roughly [-1, 1]
 *            vertically (its native ~190 x 200 unit data box is rescaled
 *            internally) — matches a resize()/reshape() that sets up an
 *            ortho projection like glOrtho(-aspect,aspect,-1,1,-1,1).
 *            Shrink/grow from there to fit your scene.
 * reset    : pass true once to restart the progressive animation
 *
 * Requires india_data.h (statePts/stateCounts/stateNumLoops,
 * outerPts/outerCounts/outerNumLoops) to be available, same as before.
 * Compile as C++ (uses std::min), e.g.:
 *     g++ your_program.c -o your_program -lGL -lGLU -lglut
 */

#ifndef INDIA_MAP_DRAW_H
#define INDIA_MAP_DRAW_H

#include <GL/freeglut.h>
#include <algorithm>
#include "india_data.h"

namespace india_map_detail {

inline void drawRingsPartial(const float pts[][2], const int counts[],
                              int numLoops, int drawLimit) {
    int startIdx = 0;
    int remaining = drawLimit;
    for (int i = 0; i < numLoops; ++i) {
        int n = counts[i];
        int drawHere = std::min(n, remaining);
        if (drawHere <= 0) {
            startIdx += n;
            continue;
        }

        if (drawHere == n)
            glBegin(GL_LINE_LOOP);
        else
            glBegin(GL_LINE_STRIP);

        for (int j = 0; j < drawHere; ++j)
            glVertex2f(pts[startIdx + j][0], pts[startIdx + j][1]);

        glEnd();

        remaining -= drawHere;
        startIdx += n;
        if (remaining <= 0)
            break;
    }
}

} // namespace india_map_detail

// The data's native bounding box is roughly 190 x 200 units
// (half-width ~95, half-height ~100). This normalizes it so half-height
// = 1.0, matching an ortho projection like glOrtho(-aspect,aspect,-1,1,-1,1).
#define INDIA_MAP_DATA_HALF_H 100.0f
#define INDIA_MAP_NORM (1.0f / INDIA_MAP_DATA_HALF_H)

// The one function you call. Everything else lives inside it.
inline void drawIndiaMap(float cx = 0.0f, float cy = 0.0f,
                          float scale = 1.0f, bool reset = false) {
    static int stateDrawN = 0;
    static int outerDrawN = 0;
    static int stateTotalPts = 0;
    static int outerTotalPts = 0;
    static bool initialized = false;

    const int drawStepState = 8; // state-border vertices added per call
    const int drawStepOuter = 2;  // outer-border vertices added per call

    if (!initialized) {
        for (int i = 0; i < stateNumLoops; ++i) stateTotalPts += stateCounts[i];
        for (int i = 0; i < outerNumLoops; ++i) outerTotalPts += outerCounts[i];
        initialized = true;
    }

    if (reset) {
        stateDrawN = 0;
        outerDrawN = 0;
    }

    if (stateDrawN < stateTotalPts)
        stateDrawN = std::min(stateTotalPts, stateDrawN + drawStepState);
    if (outerDrawN < outerTotalPts)
        outerDrawN = std::min(outerTotalPts, outerDrawN + drawStepOuter);

    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glScalef(scale * INDIA_MAP_NORM, scale * INDIA_MAP_NORM, 1.0f);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    /* State borders — thin, dim grey */
    glColor3f(0.55f, 0.55f, 0.55f);
    glLineWidth(1.0f);
    india_map_detail::drawRingsPartial(statePts, stateCounts, stateNumLoops, stateDrawN);

    /* Outer national border — thick, bright white, on top */
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    india_map_detail::drawRingsPartial(outerPts, outerCounts, outerNumLoops, outerDrawN);

    glPopMatrix();
}

#endif // INDIA_MAP_DRAW_H