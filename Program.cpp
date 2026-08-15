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


// Forward declarations
void InitializeOutroAnimation(void);
void DrawOutroAnimation(float globalTime);

bool bIsFullScreen = false;
float elapsedTimeSeconds = 0.0f;
float deltaTime = 0.016f;

// declare typedef function pointer to this definition  void draw_redfort(float x, float y, float scaleX, float scaleY)
typedef void (*DrawMonument)(float, float, float, float);
int flag = 0;

// ---------------------------------------------------------------------
// India map control
// ---------------------------------------------------------------------
// Leave bUseManualMapControl = false to have the map appear on its own,
// the instant every monument has finished shrinking to its final spot.
//
// Set bUseManualMapControl = true if YOU want to decide when it shows —
// e.g. flip bShowIndiaMapManual from a keypress, a menu, whatever. The
// display() function only ever looks at a single "showIndiaMap" bool
// either way, so swapping between the two modes doesn't touch drawing code.
bool bUseManualMapControl = false;
bool bShowIndiaMapManual = false; // only read when bUseManualMapControl == true

// Outro animation text
AnimatedTextInfo outroText;



// ---------------------------------------------------------------------
// Animation timing constants (seconds)
// ---------------------------------------------------------------------
#define PHASE1_ENTER_DURATION 2.0f  // left of screen  -> center, scale fixed at 1.0 2.0
#define PHASE2_HOLD_DURATION 2.0f   // stays at center, scale fixed at 1.0 2.0
#define PHASE3_SHRINK_DURATION 2.0f // center -> final point, scale 1.0 -> 0.2 3.0
#define TOTAL_MONUMENT_DURATION (PHASE1_ENTER_DURATION + PHASE2_HOLD_DURATION + PHASE3_SHRINK_DURATION)

#define ENTER_FROM_X -3.0f // off-screen point to the left
#define ENTER_FROM_Y 0.0f

#define FINAL_SCALE 0.2f
#define START_SCALE 1.0f

// Nameplate stays black-and-hidden until the monument settles at
// center; it then fades from black to its own color over this many
// seconds (must be <= PHASE2_HOLD_DURATION), and stays colored after.
#define NAMEPLATE_FADE_DURATION 1.0f

#define LERP(a, b, t) ((a) + (((b) - (a)) * (t)))

// ---------------------------------------------------------------------
// One entry per monument : what to draw, its label, where it ends up,
// and when (relative to program start) its own animation begins.
// ---------------------------------------------------------------------
typedef struct
{
    DrawMonument drawFunc;
    const char *name;
    float finalX;
    float finalY;
    float startDelay; // computed as index * TOTAL_MONUMENT_DURATION
    float colorR;     // nameplate's fully-faded-in color
    float colorG;
    float colorB;
} MonumentInfo;

#define MAX_MONUMENTS 7
MonumentInfo monuments[MAX_MONUMENTS];
int monumentCount = 0;

void AddMonument(DrawMonument drawFunc, const char *name, float finalX, float finalY,
                 float colorR, float colorG, float colorB)
{
    if (monumentCount >= MAX_MONUMENTS)
        return;

    monuments[monumentCount].drawFunc = drawFunc;
    monuments[monumentCount].name = name;
    monuments[monumentCount].finalX = finalX;
    monuments[monumentCount].finalY = finalY;
    monuments[monumentCount].startDelay = 27.0 + (float)monumentCount * TOTAL_MONUMENT_DURATION;
    monuments[monumentCount].colorR = colorR;
    monuments[monumentCount].colorG = colorG;
    monuments[monumentCount].colorB = colorB;
    monumentCount++;
}

float ClampF(float value, float minValue, float maxValue)
{
    if (value < minValue)
        return (minValue);
    if (value > maxValue)
        return (maxValue);
    return (value);
}

// Works out where a monument should be drawn (x, y, scale) for the
// current global time, and whether it should be drawn at all yet.
// Returns 1 if the monument has started its sequence (visible), else 0.
int GetMonumentTransform(MonumentInfo *info, float globalTime, float *outX, float *outY, float *outScale)
{
    float localTime = globalTime - info->startDelay;

    if (localTime < 0.0f)
    {
        // this monument's turn hasn't come yet
        return (0);
    }

    if (localTime < PHASE1_ENTER_DURATION)
    {
        flag = 0;
        // Phase 1 : slide in from left to center, scale fixed at 1.0
        float t = ClampF(localTime / PHASE1_ENTER_DURATION, 0.0f, 1.0f);
        *outX = LERP(ENTER_FROM_X, 0.0f, t);
        *outY = LERP(ENTER_FROM_Y, 0.0f, t);
        *outScale = START_SCALE;
    }
    else if (localTime < PHASE1_ENTER_DURATION + PHASE2_HOLD_DURATION)
    {
        flag = 1;
        // Phase 2 : hold at center, scale fixed at 1.0
        *outX = 0.0f;
        *outY = 0.0f;
        *outScale = START_SCALE;
    }
    else if (localTime < TOTAL_MONUMENT_DURATION)
    {
        flag = 0;
        // Phase 3 : shrink and move from center to its final resting point
        float phase3Time = localTime - (PHASE1_ENTER_DURATION + PHASE2_HOLD_DURATION);
        float t = ClampF(phase3Time / PHASE3_SHRINK_DURATION, 0.0f, 1.0f);
        *outX = LERP(0.0f, info->finalX, t);
        *outY = LERP(0.0f, info->finalY, t);
        *outScale = LERP(START_SCALE, FINAL_SCALE, t);
    }
    else
    {
        flag = 0;
        // Done : sits permanently at its final small position
        *outX = info->finalX;
        *outY = info->finalY;
        *outScale = FINAL_SCALE;
    }

    return (1);
}

// Nameplate stays hidden while the monument is still sliding in.
// The moment the monument is fixed at center (start of Phase 2), the
// nameplate appears black and fades to its real color over
// NAMEPLATE_FADE_DURATION seconds, then stays that color from then on
// (through the hold, the shrink, and the final parked position).
// Returns 1 if the nameplate should be drawn at all, else 0.
int GetNameplateColor(MonumentInfo *info, float globalTime, float *outR, float *outG, float *outB)
{
    float localTime = globalTime - info->startDelay;

    if (localTime < PHASE1_ENTER_DURATION)
    {
        // still entering : no nameplate yet
        return (0);
    }

    float holdLocalTime = localTime - PHASE1_ENTER_DURATION;
    float t = ClampF(holdLocalTime / NAMEPLATE_FADE_DURATION, 0.0f, 1.0f);

    *outR = LERP(0.0f, info->colorR, t);
    *outG = LERP(0.0f, info->colorG, t);
    *outB = LERP(0.0f, info->colorB, t);

    return (1);
}

// drawBuilding's existing call site in the project passes (scale, x, y)
// rather than (x, y, scaleX, scaleY), so it doesn't match the DrawMonument
// signature used by every other monument. This adapter just reorders the
// arguments so CSMT can be scheduled through the same AddMonument()/
// GetMonumentTransform() pipeline as everything else. If drawBuilding's
// real parameter order is different, adjust the call below to match.
void DrawCSMTAdapter(float x, float y, float scaleX, float scaleY)
{
    drawBuilding(scaleX, x, y);
}

void drawAgraFortAdapter(float x, float y, float scaleX, float scaleY)
{
    DrawAgraFortScene(x, y, scaleX);
}

// All monuments (by startDelay order) have reached "Done" once global
// time passes monumentCount * TOTAL_MONUMENT_DURATION - this is that
// check, exposed as its own function so display() reads as a single line.
int AreAllMonumentsSettled(float globalTime)
{
    return (globalTime >= 27.0 + 35.0);
}

int main(int argc, char *argv[])
{
    void initialize(void);
    void uninitialize(void);
    void resize(int, int);
    void display(void);
    void keyboard(unsigned char, int, int);
    void mouse(int, int, int, int);
    void timer(int value);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("S Logo - Triangles Only : SSY");
    initialize();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutCloseFunc(uninitialize);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return (0);
}

void initialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Register monuments in the order they should appear, along with
    // the small "thumbnail" point on screen each one settles into, and
    // the color its nameplate fades into once centered.
    //
    // NOTE: finalX/finalY below are just a spread-out placeholder layout
    // so the five thumbnails don't overlap once they've shrunk. Swap
    // these for the monuments' real projected positions on the India
    // map once you know that mapping, so each one parks roughly where
    // it actually sits geographically.
    AddMonument(DrawSarnathTemple, "Sarnath Temple", -0.017f, 0.2f, 1.00f, 0.84f, 0.00f); // gold
    AddMonument(drawCholaTemple, "Chola Temple", -0.25, -0.7, 0.5, 0.0, 0.5);
    AddMonument(drawKonark, "Konark Sun Temple", 0.2f, -0.16f, 1.00f, 0.60f, 0.00f);      // saffron
    AddMonument(drawHampi,          "Hampi",               -0.4f,  -0.42f, 0.80f, 0.60f, 0.20f); // sandstone
    AddMonument(drawAgraFortAdapter, "Agra Fort", 0.05, 0.55, 1.0, 1.0, 0.0);
    AddMonument(draw_redfort, "Red Fort", -0.55f, 0.65f, 0.85f, 0.10f, 0.10f);              // red
    AddMonument(DrawCSMTAdapter, "CSMT", -0.6f, -0.12f, 0.60f, 0.30f, 0.10f); // heritage brown

    
    // Initialize outro animation sequence
    InitializeOutroAnimation();

    SetOutroStartTime((float)monumentCount * TOTAL_MONUMENT_DURATION);
}

void resize(int width, int height)
{
    if (height <= 0)
        height = 1;
    float aspect = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= 1.0f)
        glOrtho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    else
        glOrtho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

int introFlag = 0;

float color1 = 0.0f;
float color2 = 0.0f;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // TEMPORARILY DISABLED FOR TESTING OUTRO ONLY
    int showIndiaMap = bUseManualMapControl
                           ? bShowIndiaMapManual
                           : AreAllMonumentsSettled(elapsedTimeSeconds);
    if (showIndiaMap)
    {
        drawIndiaMap();
    }

    if (elapsedTimeSeconds < 27.0f)
    {
        if (introFlag == 0)
        {
            introFlag = DrawIndiaBlendIntro();
        }
        else
        {
            if (color1 <= 1.0)
            {
                color1 += 0.005f;
            }
            else
            {
                color2 += 0.005f;
            }
            
            Ng_drawTextTricolor("India has FOURTY FIVE", 0.6f, 0.1f, 0.1f, 0.03f, 0.02f, color1);
            Ng_drawTextTricolor("UNESCO World Heritage Sites", 0.3f, 0.1f, 0.1f, 0.03f, 0.02f, color1);
            Ng_drawTextTricolor("INCREDIBLE INDIA", 0.0f, 0.1f, 0.1f, 0.03f, 0.02f, color2);
        }
    }

    int i;
    for (i = 0; i < monumentCount; i++)
    {
        float x, y, scale;
        int visible = GetMonumentTransform(&monuments[i], elapsedTimeSeconds, &x, &y, &scale);

        if (visible)
        {
            monuments[i].drawFunc(x, y, scale, scale);

            if (flag == 1)
            {
                drawNameplate(monuments[i].name, x, y + 0.9f * scale, scale, 0.2f * scale);
            }
        }
    }


    // Draw outro animation with musical note synchronized text
    DrawOutroAnimation(elapsedTimeSeconds);

    // Single condition gating the India map - flip bUseManualMapControl
    // above if you'd rather drive bShowIndiaMapManual yourself (key
    // press, menu item, whatever) instead of the automatic trigger.

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
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
        // Only has an effect while bUseManualMapControl == true.
        bShowIndiaMapManual = !bShowIndiaMapManual;
        break;
    default:
        break;
    }
}

void mouse(int button, int state, int spaceX, int spaceY)
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



void uninitialize(void)
{
    // code
}

void timer(int value)
{
    elapsedTimeSeconds += deltaTime;

    glutPostRedisplay();

    glutTimerFunc(16, timer, 0);
}