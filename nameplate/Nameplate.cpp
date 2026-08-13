#include "../core/Shriraj/Engine/Headers/Ng_shapes.h"
#include "../core/Shriraj/Engine/GlyphDS/Ng_glyph_DS.h"
#include <GL/freeglut.h>

void drawNameplate(
    const char* text,
    float centerX,
    float centerY,
    float width,
    float height)
{
    glColor3f(0.5f, 0.2f, 0.1f);
    Ng_drawRectangle(centerX, centerY, width, height);

    const float scaleX = 0.05f;
    const float scaleY = 0.05f;
    const float letterSpacing = 0.03f;
    const float thickness = 0.02f;

    // Must match Ng_drawText's actual glyph width formula: (4/6) * scaleX
    const float characterWidth = (4.0f / 6.0f) * scaleX;

    int length = 0;
    while (text[length] != '\0')
        ++length;

    float textWidth =
        length * characterWidth +
        (length - 1) * letterSpacing;

    float availableWidth = width * 0.9f;

    float finalScaleX = scaleX;
    float finalScaleY = scaleY;
    float finalLetterSpacing = letterSpacing;

    if (textWidth > availableWidth)
    {
        float scale = availableWidth / textWidth;

        finalScaleX *= scale;
        finalScaleY *= scale;
        finalLetterSpacing *= scale;

        textWidth =
            length * (characterWidth * scale) +
            (length - 1) * finalLetterSpacing;
    }

    float startX = centerX - textWidth * 0.5f;

    glColor3f(1.0f, 1.0f, 1.0f);

    Ng_drawText(
        text,
        startX,
        centerY,          // pass straight through — Ng_drawLetter centers on this already
        finalScaleX,
        finalScaleY,
        finalLetterSpacing,
        thickness
    );
}