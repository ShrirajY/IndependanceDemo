#include <GL/freeglut.h>

#include "Monuments/Lakshmi/Headers/Konark.h"
#include "Monuments/Shriraj/Headers/RedFort.h"
#include "Monuments/Mrunali/Headers/Sarnath.h"
#include "Monuments/Siddharth/Headers/Hampi.h"
#include "Monuments/Ankush/Headers/CSMT.h"
#include "Monuments/Prashant/include/AgraFort.h"

#include "core/Shriraj/Engine/Headers/india_draw_map.h"
#include "core/Shriraj/Engine/Headers/Blend_intro.h"
#include "core/Shriraj/Engine/GlyphDS/Ng_glyph_DS.h"

#include "nameplate/Nameplate.h"

#include "Monuments/Rugved/Headers/cholaTemple.h"

#include "outro/Headers/AnimatedText.h"
#include "outro/Headers/musicnotes.h"
#include "outro/Headers/OutroAnimation.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>


// =====================================================================
// Forward declarations
// =====================================================================

void InitializeOutroAnimation(void);
void DrawOutroAnimation(float globalTime);


// =====================================================================
// Global state
// =====================================================================

bool bIsFullScreen = false;

float elapsedTimeSeconds = 0.0f;
float deltaTime = 0.016f;


// This is now the SINGLE timing value used to start the outro.
float mainAnimationEndTime = 0.0f;


// =====================================================================
// Monument drawing function type
// =====================================================================

typedef void (*DrawMonument)(float, float, float, float);

int flag = 0;


// =====================================================================
// India map control
// =====================================================================

bool bUseManualMapControl = false;
bool bShowIndiaMapManual = false;


// =====================================================================
// Outro animation text
// =====================================================================

AnimatedTextInfo outroText;


// =====================================================================
// Animation timing constants
// =====================================================================

#define PHASE1_ENTER_DURATION 2.0f
#define PHASE2_HOLD_DURATION 2.0f
#define PHASE3_SHRINK_DURATION 2.0f

#define TOTAL_MONUMENT_DURATION \
    (PHASE1_ENTER_DURATION + \
     PHASE2_HOLD_DURATION + \
     PHASE3_SHRINK_DURATION)


#define ENTER_FROM_X -3.0f
#define ENTER_FROM_Y 0.0f

#define FINAL_SCALE 0.2f
#define START_SCALE 1.0f

#define NAMEPLATE_FADE_DURATION 1.0f

#define LERP(a, b, t) \
    ((a) + (((b) - (a)) * (t)))


#define MAX_MONUMENTS 7


// =====================================================================
// Monument information
// =====================================================================

typedef struct
{
    DrawMonument drawFunc;

    const char* name;

    float finalX;
    float finalY;

    float startDelay;

    float colorR;
    float colorG;
    float colorB;

} MonumentInfo;


MonumentInfo monuments[MAX_MONUMENTS];

int monumentCount = 0;


// =====================================================================
// Add monument
// =====================================================================

void AddMonument(
    DrawMonument drawFunc,
    const char* name,
    float finalX,
    float finalY,
    float colorR,
    float colorG,
    float colorB)
{
    if (monumentCount >= MAX_MONUMENTS)
        return;


    monuments[monumentCount].drawFunc =
        drawFunc;

    monuments[monumentCount].name =
        name;

    monuments[monumentCount].finalX =
        finalX;

    monuments[monumentCount].finalY =
        finalY;


    // First monument starts at 27 seconds.
    // Every subsequent monument starts 6 seconds later.
    monuments[monumentCount].startDelay =
        27.0f +
        (float)monumentCount *
        TOTAL_MONUMENT_DURATION;


    monuments[monumentCount].colorR =
        colorR;

    monuments[monumentCount].colorG =
        colorG;

    monuments[monumentCount].colorB =
        colorB;


    monumentCount++;
}


// =====================================================================
// Clamp
// =====================================================================

float ClampF(
    float value,
    float minValue,
    float maxValue)
{
    if (value < minValue)
        return minValue;

    if (value > maxValue)
        return maxValue;

    return value;
}


// =====================================================================
// Get monument transform
// =====================================================================

int GetMonumentTransform(
    MonumentInfo* info,
    float globalTime,
    float* outX,
    float* outY,
    float* outScale)
{
    float localTime =
        globalTime -
        info->startDelay;


    // -------------------------------------------------------------
    // Monument hasn't started yet
    // -------------------------------------------------------------

    if (localTime < 0.0f)
    {
        return 0;
    }


    // -------------------------------------------------------------
    // Phase 1
    // Slide from left to center
    // -------------------------------------------------------------

    if (localTime < PHASE1_ENTER_DURATION)
    {
        flag = 0;

        float t =
            ClampF(
                localTime /
                PHASE1_ENTER_DURATION,
                0.0f,
                1.0f
            );


        *outX =
            LERP(
                ENTER_FROM_X,
                0.0f,
                t
            );

        *outY =
            LERP(
                ENTER_FROM_Y,
                0.0f,
                t
            );

        *outScale =
            START_SCALE;
    }


    // -------------------------------------------------------------
    // Phase 2
    // Hold at center
    // -------------------------------------------------------------

    else if (
        localTime <
        PHASE1_ENTER_DURATION +
        PHASE2_HOLD_DURATION)
    {
        flag = 1;

        *outX = 0.0f;
        *outY = 0.0f;

        *outScale =
            START_SCALE;
    }


    // -------------------------------------------------------------
    // Phase 3
    // Shrink and move to final position
    // -------------------------------------------------------------

    else if (
        localTime <
        TOTAL_MONUMENT_DURATION)
    {
        flag = 0;

        float phase3Time =
            localTime -
            (
                PHASE1_ENTER_DURATION +
                PHASE2_HOLD_DURATION
            );


        float t =
            ClampF(
                phase3Time /
                PHASE3_SHRINK_DURATION,
                0.0f,
                1.0f
            );


        *outX =
            LERP(
                0.0f,
                info->finalX,
                t
            );

        *outY =
            LERP(
                0.0f,
                info->finalY,
                t
            );

        *outScale =
            LERP(
                START_SCALE,
                FINAL_SCALE,
                t
            );
    }


    // -------------------------------------------------------------
    // Done
    // -------------------------------------------------------------

    else
    {
        flag = 0;

        *outX =
            info->finalX;

        *outY =
            info->finalY;

        *outScale =
            FINAL_SCALE;
    }


    return 1;
}


// =====================================================================
// Nameplate color
// =====================================================================

int GetNameplateColor(
    MonumentInfo* info,
    float globalTime,
    float* outR,
    float* outG,
    float* outB)
{
    float localTime =
        globalTime -
        info->startDelay;


    if (localTime < PHASE1_ENTER_DURATION)
    {
        return 0;
    }


    float holdLocalTime =
        localTime -
        PHASE1_ENTER_DURATION;


    float t =
        ClampF(
            holdLocalTime /
            NAMEPLATE_FADE_DURATION,
            0.0f,
            1.0f
        );


    *outR =
        LERP(
            0.0f,
            info->colorR,
            t
        );

    *outG =
        LERP(
            0.0f,
            info->colorG,
            t
        );

    *outB =
        LERP(
            0.0f,
            info->colorB,
            t
        );


    return 1;
}


// =====================================================================
// CSMT adapter
// =====================================================================

void DrawCSMTAdapter(
    float x,
    float y,
    float scaleX,
    float scaleY)
{
    drawBuilding(
        scaleX,
        x,
        y
    );
}


// =====================================================================
// Agra Fort adapter
// =====================================================================

void drawAgraFortAdapter(
    float x,
    float y,
    float scaleX,
    float scaleY)
{
    DrawAgraFortScene(
        x,
        y,
        scaleX
    );
}


// =====================================================================
// IMPORTANT:
// Determine when the LAST monument has ACTUALLY completed.
// =====================================================================

int AreAllMonumentsSettled(
    float globalTime)
{
    if (monumentCount <= 0)
        return 0;


    // Use the actual start time of the last
    // registered monument.
    MonumentInfo* lastMonument =
        &monuments[monumentCount - 1];


    float lastMonumentEndTime =
        lastMonument->startDelay +
        TOTAL_MONUMENT_DURATION;


    return (
        globalTime >=
        lastMonumentEndTime
    );
}


// =====================================================================
// MAIN
// =====================================================================

int main(
    int argc,
    char* argv[])
{
    void initialize(void);
    void uninitialize(void);
    void resize(int, int);
    void display(void);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);
    void timer(int value);


    glutInit(
        &argc,
        argv
    );


    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGBA
    );


    glutInitWindowSize(
        800,
        600
    );


    glutInitWindowPosition(
        100,
        100
    );


    glutCreateWindow(
        "S Logo - Triangles Only : SSY"
    );


    initialize();


    glutReshapeFunc(resize);

    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);

    glutCloseFunc(uninitialize);

    glutTimerFunc(
        16,
        timer,
        0
    );


    glutMainLoop();


    return 0;
}


// =====================================================================
// INITIALIZE
// =====================================================================

void initialize(void)
{
    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );


    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    // ================================================================
    // Register monuments
    // ================================================================

    AddMonument(
        DrawSarnathTemple,
        "Sarnath Temple",
        -0.017f,
        0.2f,
        1.00f,
        0.84f,
        0.00f
    );


    AddMonument(
        drawCholaTemple,
        "Chola Temple",
        -0.25f,
        -0.7f,
        0.5f,
        0.0f,
        0.5f
    );


    AddMonument(
        drawKonark,
        "Konark Sun Temple",
        0.2f,
        -0.16f,
        1.00f,
        0.60f,
        0.00f
    );


    AddMonument(
        drawHampi,
        "Hampi",
        -0.4f,
        -0.42f,
        0.80f,
        0.60f,
        0.20f
    );


    AddMonument(
        drawAgraFortAdapter,
        "Agra Fort",
        0.05f,
        0.55f,
        1.0f,
        1.0f,
        0.0f
    );


    AddMonument(
        draw_redfort,
        "Red Fort",
        -0.55f,
        0.65f,
        0.85f,
        0.10f,
        0.10f
    );


    AddMonument(
        DrawCSMTAdapter,
        "CSMT",
        -0.6f,
        -0.12f,
        0.60f,
        0.30f,
        0.10f
    );


    // ================================================================
    // Calculate EXACT end of main monument animation
    // ================================================================

    if (monumentCount > 0)
    {
        MonumentInfo* lastMonument =
            &monuments[monumentCount - 1];


        mainAnimationEndTime =
            lastMonument->startDelay +
            TOTAL_MONUMENT_DURATION;
    }
    else
    {
        mainAnimationEndTime =
            27.0f;
    }


    // ================================================================
    // Initialize outro
    // ================================================================

    InitializeOutroAnimation();


    // Use exactly the same time for the outro.
    SetOutroStartTime(
        mainAnimationEndTime
    );
}


// =====================================================================
// RESIZE
// =====================================================================

void resize(
    int width,
    int height)
{
    if (height <= 0)
        height = 1;


    float aspect =
        (float)width /
        (float)height;


    glMatrixMode(
        GL_PROJECTION
    );


    glLoadIdentity();


    if (aspect >= 1.0f)
    {
        glOrtho(
            -aspect,
            aspect,
            -1.0f,
            1.0f,
            -1.0f,
            1.0f
        );
    }
    else
    {
        glOrtho(
            -1.0f,
            1.0f,
            -1.0f / aspect,
            1.0f / aspect,
            -1.0f,
            1.0f
        );
    }


    glViewport(
        0,
        0,
        (GLsizei)width,
        (GLsizei)height
    );
}


// =====================================================================
// Intro state
// =====================================================================

int introFlag = 0;

float color1 = 0.0f;
float color2 = 0.0f;


// =====================================================================
// DISPLAY
// =====================================================================

void display(void)
{
    glClear(
        GL_COLOR_BUFFER_BIT
    );


    glMatrixMode(
        GL_MODELVIEW
    );

    glLoadIdentity();


    // ================================================================
    // INDIA MAP
    // ================================================================

    int showIndiaMap =
        bUseManualMapControl
        ? bShowIndiaMapManual
        : AreAllMonumentsSettled(
            elapsedTimeSeconds
        );


    if (showIndiaMap)
    {
        drawIndiaMap();
    }


    // ================================================================
    // INTRO
    // ================================================================

    if (elapsedTimeSeconds < 27.0f)
    {
        if (introFlag == 0)
        {
            introFlag =
                DrawIndiaBlendIntro();
        }
        else
        {
            if (color1 <= 1.0f)
            {
                color1 += 0.005f;
            }
            else
            {
                color2 += 0.005f;
            }


            Ng_drawTextTricolor(
                "India has FOURTY FIVE",
                0.6f,
                0.1f,
                0.1f,
                0.03f,
                0.02f,
                color1
            );


            Ng_drawTextTricolor(
                "UNESCO World Heritage Sites",
                0.3f,
                0.1f,
                0.1f,
                0.03f,
                0.02f,
                color1
            );


            Ng_drawTextTricolor(
                "INCREDIBLE INDIA",
                0.0f,
                0.1f,
                0.1f,
                0.03f,
                0.02f,
                color2
            );
        }
    }


    // ================================================================
    // MONUMENTS
    // ================================================================

    int i;


    for (i = 0;
         i < monumentCount;
         i++)
    {
        float x;
        float y;
        float scale;


        int visible =
            GetMonumentTransform(
                &monuments[i],
                elapsedTimeSeconds,
                &x,
                &y,
                &scale
            );


        if (visible)
        {
            monuments[i].drawFunc(
                x,
                y,
                scale,
                scale
            );


            if (flag == 1)
            {
                drawNameplate(
                    monuments[i].name,
                    x,
                    y + 0.9f * scale,
                    scale,
                    0.2f * scale
                );
            }
        }
    }


    // ================================================================
    // OUTRO
    //
    // IMPORTANT:
    // The outro is not even called until the LAST monument
    // has completed its complete 6-second animation.
    // ================================================================

    if (
        elapsedTimeSeconds >=
        mainAnimationEndTime)
    {
        DrawOutroAnimation(
            elapsedTimeSeconds
        );
    }


    // ================================================================
    // Swap buffers
    // ================================================================

    glutSwapBuffers();
}


// =====================================================================
// KEYBOARD
// =====================================================================

void keyboard(
    unsigned char key,
    int x,
    int y)
{
    switch (key)
    {
        case 27:

            glutLeaveMainLoop();

            break;


        case 'F':
        case 'f':

            if (bIsFullScreen == false)
            {
                glutFullScreen();

                bIsFullScreen = true;
            }
            else
            {
                glutLeaveFullScreen();

                bIsFullScreen = false;
            }

            break;


        case 'M':
        case 'm':

            if (bUseManualMapControl)
            {
                bShowIndiaMapManual =
                    !bShowIndiaMapManual;
            }

            break;


        default:

            break;
    }
}


// =====================================================================
// MOUSE
// =====================================================================

void mouse(
    int button,
    int state,
    int spaceX,
    int spaceY)
{
    switch (button)
    {
        case GLUT_RIGHT_BUTTON:

            glutLeaveMainLoop();

            break;


        default:

            break;
    }
}


// =====================================================================
// UNINITIALIZE
// =====================================================================

void uninitialize(void)
{
    // code
}


// =====================================================================
// TIMER
// =====================================================================

void timer(int value)
{
    elapsedTimeSeconds +=
        deltaTime;


    glutPostRedisplay();


    glutTimerFunc(
        16,
        timer,
        0
    );
}