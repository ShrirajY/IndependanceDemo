#define _USE_MATH_DEFINES

#include <cmath>
#include <GL/freeglut.h>

#include "../Headers/OutroAnimation.h"
#include "../Headers/AnimatedText.h"
#include "../Headers/musicnotes.h"


// ================================================================
// GLOBAL STATE
// ================================================================

int bOutroStarted = 0;


// ================================================================
// UTILITY
// ================================================================

inline float LERP(float a, float b, float t)
{
    return a + (b - a) * t;
}


// ================================================================
// OUTRO TEXT CONFIGURATION
// ================================================================

typedef struct
{
    const char* text;

    float posY;

    float baseScale;
    float minScale;
    float maxScale;

    float pulseDuration;

    float colorR;
    float colorG;
    float colorB;

} OutroTextConfig;


// ================================================================
// OUTRO TEXT CONFIGURATIONS
// ================================================================

OutroTextConfig outroConfigs[] =
{

    // ============================================================
    // TEXT 1
    // ============================================================

    {
        "BLEND GROUP:\n"
        "Sagar Kalbande ( Group Leader )\n"
        "Shriraj Yamkanmardi\n"
        "Lakshmi Priya M\n"
        "Ankush Aglawe\n"
        "Siddharth M Bhise\n"
        "Lokesh Sonawane\n"
        "Mrunali Jibhakate\n"
        "Prashant Gharge\n"
        "Rugved Dhable",

        0.65f,

        0.20f,
        0.12f,
        0.30f,

        3.0f,

        0.0f,
        0.8f,
        0.0f
    },


    // ============================================================
    // TEXT 2
    // ============================================================

    {
        "SPECIAL THANKS,\n"
        "Pradnya Gokhale Madam,\n"
        "Dr Rama Gokhale Madam",

        0.45f,

        0.32f,
        0.20f,
        0.48f,

        3.0f,

        1.0f,
        0.8f,
        0.0f
    },


    // ============================================================
    // TEXT 3
    // ============================================================

    {
        "IGNITED BY\n"
        "DR VIJAY GOKHALE",

        0.15f,

        0.34f,
        0.20f,
        0.48f,

        3.0f,

        1.0f,
        0.6f,
        0.0f
    },


    // ============================================================
    // TEXT 4
    // TECHNOLOGY / SONG CREDITS
    // ============================================================

    {
        "TECHNOLOGY USED\n"
        "C++ PROGRAMMING LANGUAGE, FREEGLUT\n"
        "\n"
        "SONGS USED\n"
        "\n"
        "Song: Jayostule Shree Mahanmangale\n"
        "Album: Jay Jay Maharashtra Maaza\n"
        "Artist: Lata Mangeshkar\n"
        "Music Director: Madhukar Golvalkar\n"
        "Lyricist: Vinayak Damodar Savarkar\n"
        "\n"
        "Jana Gana Mana (Instrumental)\n"
        "By,\n"
        "Pandit Hariprasad Chaurasia, Pandit Shiv Kumar Sharma, Pandit A. Ananthapadmanabhan, Dr. N. Rajam\n"
        "Ustad Amjad Ali Khan, Pandit Vikku Vinayakram, Ustad Shahid Parvez Khan, Pandit Vishwa Mohan Bhatt\n"
        "Ustad Zakir Hussain, Pandit Rakesh Chaurasia, Ustad Dilshad Khan, Dr. Sangeeta Shankar\n"
        "\n"
        "Jagga Jitteya\n"
        "\n"
        "Song: Jagga Jiteya\n"
        "Singer(s): Daler Mehndi, Dee MC & Shashwat Sachdev\n"
        "Music: Shashwat Sachdev\n"
        "Lyrics: Kumaar",

    0.70f,      // posY
    0.21f,      // baseScale
    0.13f,      // minScale
    0.25f,      // maxScale
    3.0f,       // pulseDuration

    1.0f, 0.75f, 0.15f
    }

};


// ================================================================
// ANIMATED TEXT OBJECTS
// ================================================================

AnimatedTextInfo outroText1;
AnimatedTextInfo outroText2;
AnimatedTextInfo outroText3;
AnimatedTextInfo outroText4;

int outroConfigCount = 4;


// ================================================================
// MUSICAL NOTE ANIMATION STATE
// ================================================================

static float currentScale = 0.05f;
static float rotationAngle = 0.0f;


// ================================================================
// OUTRO TIMING
// ================================================================

#define NOTES_DURATION       3.0f
#define TEXT_DURATION        3.0f

#define OUTRO_TOTAL_DURATION 21.0f

static float outroStartTime = 0.0f;


// ================================================================
// SET OUTRO START TIME
// ================================================================

void SetOutroStartTime(float startTime)
{
    outroStartTime = startTime;
}


// ================================================================
// INITIAL INTERNAL ANIMATION STATE
// ================================================================

void InitOutroAnimation()
{
    currentScale = 0.05f;
    rotationAngle = 0.0f;
}


// ================================================================
// DRAW OUTRO ANIMATION STEP
// ================================================================

void DrawOutroAnimationStep(float deltaTime)
{
    // ------------------------------------------------------------
    // Update animation state
    // ------------------------------------------------------------

    currentScale += 0.012f;

    if (currentScale > 2.0f)
    {
        currentScale = 0.05f;
    }


    rotationAngle += 0.015f;

    if (rotationAngle > 2.0f * (float)M_PI)
    {
        rotationAngle -= 2.0f * (float)M_PI;
    }


    // ------------------------------------------------------------
    // Render notes
    // ------------------------------------------------------------

    float baseRadius = 0.5f;

    int totalNotes = 6;


    for (int i = 0;
         i < totalNotes;
         i++)
    {
        float currentAngle =
            (i *
            (2.0f * (float)M_PI /
             totalNotes))
            +
            rotationAngle;


        float noteX =
            cosf(currentAngle) *
            (baseRadius * currentScale);


        float noteY =
            sinf(currentAngle) *
            (baseRadius * currentScale);


        int noteType = i % 4;


        if (noteType == 0)
        {
            drawQuarterNote(
                noteX,
                noteY,
                currentScale
            );
        }
        else if (noteType == 1)
        {
            drawSharpNote(
                noteX,
                noteY,
                currentScale
            );
        }
        else if (noteType == 2)
        {
            drawHalfNote(
                noteX,
                noteY,
                currentScale
            );
        }
        else
        {
            drawBeamedEighthNotes(
                noteX,
                noteY,
                currentScale
            );
        }
    }
}


// ================================================================
// INITIALIZE OUTRO ANIMATION
// ================================================================

void InitializeOutroAnimation(void)
{
    bOutroStarted = 1;


    // ============================================================
    // TEXT 1
    // ============================================================

    outroText1 = AnimatedText_Create(
        outroConfigs[0].text,

        0.0f,
        outroConfigs[0].posY,

        outroConfigs[0].baseScale,
        outroConfigs[0].baseScale,

        outroConfigs[0].minScale,
        outroConfigs[0].maxScale,

        outroConfigs[0].pulseDuration,

        0.0f,

        outroConfigs[0].colorR,
        outroConfigs[0].colorG,
        outroConfigs[0].colorB
    );


    // ============================================================
    // TEXT 2
    // ============================================================

    outroText2 = AnimatedText_Create(
        outroConfigs[1].text,

        0.0f,
        outroConfigs[1].posY,

        outroConfigs[1].baseScale,
        outroConfigs[1].baseScale,

        outroConfigs[1].minScale,
        outroConfigs[1].maxScale,

        outroConfigs[1].pulseDuration,

        0.0f,

        outroConfigs[1].colorR,
        outroConfigs[1].colorG,
        outroConfigs[1].colorB
    );


    // ============================================================
    // TEXT 3
    // ============================================================

    outroText3 = AnimatedText_Create(
        outroConfigs[2].text,

        0.0f,
        outroConfigs[2].posY,

        outroConfigs[2].baseScale,
        outroConfigs[2].baseScale,

        outroConfigs[2].minScale,
        outroConfigs[2].maxScale,

        outroConfigs[2].pulseDuration,

        0.0f,

        outroConfigs[2].colorR,
        outroConfigs[2].colorG,
        outroConfigs[2].colorB
    );


    // ============================================================
    // TEXT 4
    // ============================================================

    outroText4 = AnimatedText_Create(
        outroConfigs[3].text,

        0.0f,
        outroConfigs[3].posY,

        outroConfigs[3].baseScale,
        outroConfigs[3].baseScale,

        outroConfigs[3].minScale,
        outroConfigs[3].maxScale,

        outroConfigs[3].pulseDuration,

        0.0f,

        outroConfigs[3].colorR,
        outroConfigs[3].colorG,
        outroConfigs[3].colorB
    );


    // ============================================================
    // Initially disable all text
    // ============================================================

    AnimatedText_SetActive(
        &outroText1,
        0
    );

    AnimatedText_SetActive(
        &outroText2,
        0
    );

    AnimatedText_SetActive(
        &outroText3,
        0
    );

    AnimatedText_SetActive(
        &outroText4,
        0
    );
}


// ================================================================
// MATRIX-FREE TEXT RENDERER
// ================================================================

void RenderOutroText(
    const char* text,
    float posY,
    float scale)
{
    // ------------------------------------------------------------
    // Determine longest line
    // ------------------------------------------------------------

    int longestLineLen = 0;
    int currentLineLen = 0;


    for (const char* p = text;
         *p != '\0';
         ++p)
    {
        if (*p == '\n')
        {
            if (currentLineLen >
                longestLineLen)
            {
                longestLineLen =
                    currentLineLen;
            }

            currentLineLen = 0;
        }
        else
        {
            currentLineLen++;
        }
    }


    if (currentLineLen >
        longestLineLen)
    {
        longestLineLen =
            currentLineLen;
    }


    // ------------------------------------------------------------
    // Bitmap character dimensions
    // ------------------------------------------------------------

    float charWidth =
        0.018f *
        (scale / 0.30f);


    float lineHeight =
        0.045f *
        (scale / 0.30f);


    // ------------------------------------------------------------
    // Center longest line
    // ------------------------------------------------------------

    float startX =
        -(longestLineLen *
          charWidth) *
        0.5f;


    float currentX = startX;
    float currentY = posY;


    // ------------------------------------------------------------
    // Draw characters
    // ------------------------------------------------------------

    for (const char* p = text;
         *p != '\0';
         ++p)
    {
        if (*p == '\n')
        {
            currentX = startX;

            currentY -= lineHeight;

            continue;
        }


        glRasterPos2f(
            currentX,
            currentY
        );


        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            *p
        );


        currentX += charWidth;
    }
}


// ================================================================
// MAIN OUTRO DRAW FUNCTION
// ================================================================

void DrawOutroAnimation(float globalTime)
{
    // ------------------------------------------------------------
    // Convert global time into outro-local time
    // ------------------------------------------------------------

    float outroTime =
        globalTime -
        outroStartTime;


    if (outroTime < 0.0f)
    {
        return;
    }


    // ============================================================
    // OUTRO TIMELINE
    //
    // 0  - 3   : Musical notes
    // 3  - 6   : Text 1
    //
    // 6  - 9   : Musical notes
    // 9  - 12  : Text 2
    //
    // 12 - 15  : Musical notes
    // 15 - 18  : Text 3
    //
    // 18 - 21  : Text 4
    // ============================================================


    // ============================================================
    // Disable all text first
    // ============================================================

    AnimatedText_SetActive(
        &outroText1,
        0
    );

    AnimatedText_SetActive(
        &outroText2,
        0
    );

    AnimatedText_SetActive(
        &outroText3,
        0
    );

    AnimatedText_SetActive(
        &outroText4,
        0
    );


    // ============================================================
    // MUSIC NOTE PHASE
    // ============================================================

    bool notesPhase =
        (outroTime >= 0.0f &&
         outroTime < 3.0f)

        ||

        (outroTime >= 6.0f &&
         outroTime < 9.0f)

        ||

        (outroTime >= 12.0f &&
         outroTime < 15.0f);


    if (notesPhase)
    {
        // --------------------------------------------------------
        // Determine current note-phase time
        // --------------------------------------------------------

        float phaseTime = 0.0f;


        if (outroTime < 3.0f)
        {
            phaseTime = outroTime;
        }
        else if (outroTime < 9.0f)
        {
            phaseTime =
                outroTime - 6.0f;
        }
        else
        {
            phaseTime =
                outroTime - 12.0f;
        }


        // --------------------------------------------------------
        // Fade notes
        // --------------------------------------------------------

        float progress =
            phaseTime / 3.0f;


        float notesAlpha = 1.0f;


        if (progress < 0.15f)
        {
            notesAlpha =
                progress / 0.15f;
        }
        else if (progress > 0.85f)
        {
            notesAlpha =
                (1.0f - progress) /
                0.15f;
        }


        // --------------------------------------------------------
        // Clamp alpha
        // --------------------------------------------------------

        if (notesAlpha < 0.0f)
        {
            notesAlpha = 0.0f;
        }

        if (notesAlpha > 1.0f)
        {
            notesAlpha = 1.0f;
        }


        // --------------------------------------------------------
        // Enable transparency
        // --------------------------------------------------------

        glEnable(GL_BLEND);

        glBlendFunc(
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA
        );


        // ========================================================
        // NOTE ORBIT CONFIGURATION
        // ========================================================

        const int numOrbits = 3;

        const int notesPerOrbit = 6;

        const float baseRadius = 0.40f;

        const float radiusStep = 0.35f;


        // ========================================================
        // DRAW THREE GOLDEN ORBITS
        // ========================================================

        glColor4f(
            1.0f,
            0.75f,
            0.15f,
            notesAlpha * 0.55f
        );


        glLineWidth(2.0f);


        const int circleSegments = 160;


        for (int c = 0;
             c < numOrbits;
             c++)
        {
            float radius =
                baseRadius +
                ((float)c *
                 radiusStep);


            glBegin(GL_LINE_LOOP);


            for (int i = 0;
                 i < circleSegments;
                 i++)
            {
                float angle =
                    2.0f *
                    (float)M_PI *
                    (float)i /
                    (float)circleSegments;


                float x =
                    radius *
                    cosf(angle);


                float y =
                    radius *
                    sinf(angle);


                glVertex2f(
                    x,
                    y
                );
            }


            glEnd();
        }


        // ========================================================
        // DRAW MUSICAL NOTES
        // ========================================================

        for (int c = 0;
             c < numOrbits;
             c++)
        {
            // ----------------------------------------------------
            // Orbit radius
            // ----------------------------------------------------

            float radius =
                baseRadius +
                ((float)c *
                 radiusStep);


            // ----------------------------------------------------
            // Rotation direction
            //
            // Inner  -> clockwise
            // Middle -> counter-clockwise
            // Outer  -> clockwise
            // ----------------------------------------------------

            float direction =
                (c % 2 == 0)
                ? 1.0f
                : -1.0f;


            // ----------------------------------------------------
            // Rotation speed
            // ----------------------------------------------------

            float currentRotationAngle =
                phaseTime *
                45.0f *
                direction;


            // ----------------------------------------------------
            // Six notes per orbit
            // ----------------------------------------------------

            for (int n = 0;
                 n < notesPerOrbit;
                 n++)
            {
                // ------------------------------------------------
                // Initial angle
                // ------------------------------------------------

                float initialAngleDeg =
                    (float)n *
                    (360.0f /
                     (float)notesPerOrbit);


                // ------------------------------------------------
                // Apply rotation
                // ------------------------------------------------

                float finalAngleDeg =
                    initialAngleDeg +
                    currentRotationAngle;


                float angleRad =
                    finalAngleDeg *
                    (float)M_PI /
                    180.0f;


                // ------------------------------------------------
                // Note position
                //
                // Notes sit directly on orbit.
                // ------------------------------------------------

                float noteX =
                    radius *
                    cosf(angleRad);


                float noteY =
                    radius *
                    sinf(angleRad);


                // ------------------------------------------------
                // Golden color
                // ------------------------------------------------

                glColor4f(
                    1.0f,
                    0.75f,
                    0.15f,
                    notesAlpha
                );


                float noteScale =
                    0.60f;


                // ------------------------------------------------
                // Different note types
                // ------------------------------------------------

                int noteType =
                    (c + n) % 5;


                switch (noteType)
                {
                    case 0:
                    {
                        drawQuarterNote(
                            noteX,
                            noteY,
                            noteScale
                        );

                        break;
                    }


                    case 1:
                    {
                        drawSlantedBeamedNotes(
                            noteX,
                            noteY,
                            noteScale
                        );

                        break;
                    }


                    case 2:
                    {
                        drawHalfNote(
                            noteX,
                            noteY,
                            noteScale
                        );

                        break;
                    }


                    case 3:
                    {
                        drawSharpNote(
                            noteX,
                            noteY,
                            noteScale
                        );

                        break;
                    }


                    case 4:
                    {
                        drawBeamedEighthNotes(
                            noteX,
                            noteY,
                            noteScale
                        );

                        break;
                    }
                }
            }
        }


        // --------------------------------------------------------
        // Restore line width
        // --------------------------------------------------------

        glLineWidth(1.0f);

        glDisable(GL_BLEND);


        return;
    }


    // ============================================================
    // TEXT 1
    //
    // 3 - 6 seconds
    // ============================================================

    if (outroTime >= 3.0f &&
        outroTime < 6.0f)
    {
        float localTime =
            outroTime - 3.0f;


        AnimatedText_SetActive(
            &outroText1,
            1
        );

        AnimatedText_SetPosition(
            &outroText1,
            0.0f,
            -0.10f
        );

        AnimatedText_Draw(
            &outroText1,
            localTime
        );


        return;
    }


    // ============================================================
    // TEXT 2
    //
    // 9 - 12 seconds
    // ============================================================

    if (outroTime >= 9.0f &&
        outroTime < 12.0f)
    {
        float localTime =
            outroTime - 9.0f;


        AnimatedText_SetActive(
            &outroText2,
            1
        );


        AnimatedText_Draw(
            &outroText2,
            localTime
        );


        return;
    }


    // ============================================================
    // TEXT 3
    //
    // 15 - 18 seconds
    // ============================================================

    if (outroTime >= 15.0f &&
        outroTime < 18.0f)
    {
        float localTime =
            outroTime - 15.0f;


        AnimatedText_SetActive(
            &outroText3,
            1
        );


        // --------------------------------------------------------
        // Shift final credits slightly downward
        // --------------------------------------------------------

        AnimatedText_SetPosition(
            &outroText3,
            0.0f,
            -0.10f
        );


        AnimatedText_Draw(
            &outroText3,
            localTime
        );


        return;
    }


    // ============================================================
    // TEXT 4
    //
    // 18 - 21 seconds
    //
    // Technology + Song Credits
    // ============================================================

    if (outroTime >= 18.0f &&
        outroTime < 21.0f)
    {
        float localTime =
            outroTime - 18.0f;


        AnimatedText_SetActive(
            &outroText4,
            1
        );


        // --------------------------------------------------------
        // Position TEXT 4
        // --------------------------------------------------------

        AnimatedText_SetPosition(
            &outroText4,
            0.0f,
            0.05f
        );


        AnimatedText_Draw(
            &outroText4,
            localTime
        );


        return;
    }
}