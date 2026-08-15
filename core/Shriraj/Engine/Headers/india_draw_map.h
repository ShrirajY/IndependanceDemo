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

}

#define INDIA_MAP_DATA_HALF_H 100.0f
#define INDIA_MAP_NORM (1.0f / INDIA_MAP_DATA_HALF_H)

// The one function you call. Everything else lives inside it.
inline void drawIndiaMap(float cx = 0.0f, float cy = 0.0f,
                         float scale = 1.0f, bool reset = false) {
    static int stateDrawN = 0;
    static int outerDrawN = 0;
    static int stateTotalPts = 0;
    static int outerTotalPts = 0;

    static int stateCallCounter = 0;
    static bool initialized = false;
    const int stateCallsPerOuterCall = 6;

    // Number of vertices added during one state update
    const int drawStepState = 8;

    // Number of vertices added during one outer update
    const int drawStepOuter = 2;

    if (!initialized) {
        for (int i = 0; i < stateNumLoops; ++i)
            stateTotalPts += stateCounts[i];

        for (int i = 0; i < outerNumLoops; ++i)
            outerTotalPts += outerCounts[i];

        initialized = true;
    }

    // ============================================================
    // RESET
    // ============================================================
    if (reset) {
        stateDrawN = 0;
        outerDrawN = 0;
        stateCallCounter = 0;
    }

    // ============================================================
    // STATE BORDER
    // ============================================================
    if (stateDrawN < stateTotalPts) {
        stateDrawN =
            std::min(stateTotalPts,
                     stateDrawN + drawStepState);
    }

    // ============================================================
    // OUTER BORDER
    // ============================================================
    ++stateCallCounter;

    if (stateCallCounter >= stateCallsPerOuterCall) {
        stateCallCounter = 0;

        if (outerDrawN < outerTotalPts) {
            outerDrawN =
                std::min(outerTotalPts,
                         outerDrawN + drawStepOuter);
        }
    }

    // ============================================================
    // DRAW
    // ============================================================
    glPushMatrix();

    glTranslatef(cx, cy, 0.0f);

    glScalef(
        scale * INDIA_MAP_NORM,
        scale * INDIA_MAP_NORM,
        1.0f
    );

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // ------------------------------------------------------------
    // State borders
    // ------------------------------------------------------------
    glColor3f(0.55f, 0.55f, 0.55f);

    glLineWidth(1.0f);

    india_map_detail::drawRingsPartial(
        statePts,
        stateCounts,
        stateNumLoops,
        stateDrawN
    );

    // ------------------------------------------------------------
    // Outer national border
    // ------------------------------------------------------------
    glColor3f(1.0f, 1.0f, 1.0f);

    glLineWidth(3.0f);

    india_map_detail::drawRingsPartial(
        outerPts,
        outerCounts,
        outerNumLoops,
        outerDrawN
    );

    glPopMatrix();
}

#endif // INDIA_MAP_DRAW_H