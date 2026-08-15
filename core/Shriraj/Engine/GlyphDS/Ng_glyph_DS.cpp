#include "Ng_glyph_DS.h"
#include <GL/freeglut.h>
#include <vector>
#include <utility>
#include <cctype>
#include <cstddef> 
#include <cmath> 

void Ng_drawRectangle(float x, float y, float width, float height);
void Ng_drawRotatedRectangle(float x, float y, float width, float height, float angle);

static inline void Ng_letterGridToWorld(float gridX, float gridY,
                                         float centerX, float centerY,
                                         float scaleX, float scaleY,
                                         float* outX, float* outY)
{
    const float UNIT = 1.0f / 6.0f;
    *outX = centerX + (gridX - 2.0f) * UNIT * scaleX;
    *outY = centerY + (gridY - 3.0f) * UNIT * scaleY;
}

typedef std::vector<std::pair<float, float> > Ng_Stroke;   // one polyline
typedef std::vector<Ng_Stroke> Ng_Glyph;                   // set of polylines

static void Ng_drawThickSegment(float x1, float y1, float x2, float y2, float thickness)
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
        {
            // Horizontal segment: no rotation needed.
            Ng_drawRectangle(midX, midY, length, thickness);
        }
        else if (std::fabs(dx) < EPS)
        {
            // Vertical segment: no rotation needed.
            Ng_drawRectangle(midX, midY, thickness, length);
        }
        else
        {
            // Diagonal segment: needs rotation.
            float angleDeg = std::atan2(dy, dx) * (180.0f / 3.14159265f);
            Ng_drawRotatedRectangle(midX, midY, length, thickness, angleDeg);
        }
    }

    // Joint caps so corners between segments don't show gaps.
    Ng_drawRectangle(x1, y1, thickness, thickness);
    Ng_drawRectangle(x2, y2, thickness, thickness);
}

static void Ng_drawGlyph(const Ng_Glyph& glyph,
                          float centerX, float centerY,
                          float scaleX, float scaleY,
                          float thickness)
{
    for (size_t s = 0; s < glyph.size(); s++)
    {
        const Ng_Stroke& stroke = glyph[s];
        if (stroke.size() < 2)
            continue;

        float prevX, prevY;
        Ng_letterGridToWorld(stroke[0].first, stroke[0].second,
                              centerX, centerY, scaleX, scaleY,
                              &prevX, &prevY);

        for (size_t p = 1; p < stroke.size(); p++)
        {
            float curX, curY;
            Ng_letterGridToWorld(stroke[p].first, stroke[p].second,
                                  centerX, centerY, scaleX, scaleY,
                                  &curX, &curY);

            Ng_drawThickSegment(prevX, prevY, curX, curY, thickness);

            prevX = curX;
            prevY = curY;
        }
    }
}

// -----------------------------------------------------------------------
// Letter glyphs (authored on the 4 x 6 grid described above)
// -----------------------------------------------------------------------

void Ng_drawLetterA(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {2.0f, 6.0f}, {4.0f, 0.0f} });
    g.push_back(Ng_Stroke{ {0.8f, 2.0f}, {3.2f, 2.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterB(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {2.5f, 6.0f}, {3.2f, 5.3f}, {3.2f, 3.7f}, {2.5f, 3.0f}, {0.0f, 3.0f} });
    g.push_back(Ng_Stroke{ {0.0f, 3.0f}, {2.7f, 3.0f}, {3.4f, 2.3f}, {3.4f, 0.7f}, {2.7f, 0.0f}, {0.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterC(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {4.0f, 5.0f}, {3.0f, 6.0f}, {1.0f, 6.0f}, {0.0f, 5.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {3.0f, 0.0f}, {4.0f, 1.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterD(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {2.0f, 6.0f}, {4.0f, 4.0f}, {4.0f, 2.0f}, {2.0f, 0.0f}, {0.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterE(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {4.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 6.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {0.0f, 3.0f}, {3.0f, 3.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterF(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {0.0f, 3.0f}, {3.0f, 3.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterG(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {4.0f, 5.0f}, {3.0f, 6.0f}, {1.0f, 6.0f}, {0.0f, 5.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {3.0f, 0.0f}, {4.0f, 1.0f}, {4.0f, 3.0f}, {2.5f, 3.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterH(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {4.0f, 0.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {0.0f, 3.0f}, {4.0f, 3.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterI(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {1.0f, 0.0f}, {3.0f, 0.0f} });
    g.push_back(Ng_Stroke{ {2.0f, 0.0f}, {2.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {1.0f, 6.0f}, {3.0f, 6.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterJ(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {3.0f, 6.0f}, {3.0f, 1.0f}, {2.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterK(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {4.0f, 6.0f}, {0.0f, 3.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterL(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {0.0f, 0.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterM(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {2.0f, 2.0f}, {4.0f, 6.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterN(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {4.0f, 0.0f}, {4.0f, 6.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterO(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {1.0f, 0.0f}, {3.0f, 0.0f}, {4.0f, 1.0f}, {4.0f, 5.0f}, {3.0f, 6.0f}, {1.0f, 6.0f}, {0.0f, 5.0f}, {0.0f, 1.0f}, {1.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterP(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {2.5f, 6.0f}, {3.4f, 5.3f}, {3.4f, 3.7f}, {2.5f, 3.0f}, {0.0f, 3.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterQ(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {1.0f, 0.0f}, {3.0f, 0.0f}, {4.0f, 1.0f}, {4.0f, 5.0f}, {3.0f, 6.0f}, {1.0f, 6.0f}, {0.0f, 5.0f}, {0.0f, 1.0f}, {1.0f, 0.0f} });
    g.push_back(Ng_Stroke{ {2.3f, 1.6f}, {4.2f, -0.4f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterR(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {0.0f, 6.0f}, {2.5f, 6.0f}, {3.4f, 5.3f}, {3.4f, 3.7f}, {2.5f, 3.0f}, {0.0f, 3.0f} });
    g.push_back(Ng_Stroke{ {1.5f, 3.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterS(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {4.0f, 5.0f}, {3.0f, 6.0f}, {1.0f, 6.0f}, {0.0f, 5.0f}, {0.0f, 3.8f}, {1.0f, 3.0f}, {3.0f, 3.0f}, {4.0f, 2.2f}, {4.0f, 1.0f}, {3.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterT(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {2.0f, 6.0f}, {2.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterU(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {3.0f, 0.0f}, {4.0f, 1.0f}, {4.0f, 6.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterV(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {2.0f, 0.0f}, {4.0f, 6.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterW(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {1.0f, 0.0f}, {2.0f, 4.0f}, {3.0f, 0.0f}, {4.0f, 6.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterX(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 0.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterY(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {2.0f, 3.0f}, {4.0f, 6.0f} });
    g.push_back(Ng_Stroke{ {2.0f, 3.0f}, {2.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

void Ng_drawLetterZ(float centerX, float centerY, float scaleX, float scaleY, float thickness)
{
    Ng_Glyph g;
    g.push_back(Ng_Stroke{ {0.0f, 6.0f}, {4.0f, 6.0f}, {0.0f, 0.0f}, {4.0f, 0.0f} });
    Ng_drawGlyph(g, centerX, centerY, scaleX, scaleY, thickness);
}

// -----------------------------------------------------------------------
// Dispatcher + string helper
// -----------------------------------------------------------------------

void Ng_drawLetter(char c, float centerX, float centerY,
                    float scaleX, float scaleY, float thickness)
{
    switch (std::toupper(static_cast<unsigned char>(c)))
    {
        case 'A': Ng_drawLetterA(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'B': Ng_drawLetterB(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'C': Ng_drawLetterC(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'D': Ng_drawLetterD(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'E': Ng_drawLetterE(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'F': Ng_drawLetterF(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'G': Ng_drawLetterG(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'H': Ng_drawLetterH(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'I': Ng_drawLetterI(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'J': Ng_drawLetterJ(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'K': Ng_drawLetterK(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'L': Ng_drawLetterL(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'M': Ng_drawLetterM(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'N': Ng_drawLetterN(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'O': Ng_drawLetterO(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'P': Ng_drawLetterP(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'Q': Ng_drawLetterQ(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'R': Ng_drawLetterR(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'S': Ng_drawLetterS(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'T': Ng_drawLetterT(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'U': Ng_drawLetterU(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'V': Ng_drawLetterV(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'W': Ng_drawLetterW(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'X': Ng_drawLetterX(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'Y': Ng_drawLetterY(centerX, centerY, scaleX, scaleY, thickness); break;
        case 'Z': Ng_drawLetterZ(centerX, centerY, scaleX, scaleY, thickness); break;
        default: break; // unsupported char (space, digit, punctuation) - skip
    }
}

void Ng_drawText(const char* text, float startX, float centerY,
                  float scaleX, float scaleY,
                  float letterSpacing, float thickness)
{
    if (!text) return;

    const float glyphWidth = (4.0f / 6.0f) * scaleX; // matches grid mapping above
    float cursorX = startX + glyphWidth / 2.0f;       // start at first glyph's center

    for (const char* p = text; *p != '\0'; ++p)
    {
        if (*p == ' ')
        {
            cursorX += glyphWidth + letterSpacing;
            continue;
        }

        Ng_drawLetter(*p, cursorX, centerY, scaleX, scaleY, thickness);
        cursorX += glyphWidth + letterSpacing;
    }
}

static const float Ng_TRICOLOR[3][3] = {
    { 1.00f, 0.60f, 0.20f },  // saffron
    { 1.00f, 1.00f, 1.00f },  // white
    { 0.07f, 0.53f, 0.03f }   // india green
};

static float Ng_textWidth(const char* text, float scaleX, float letterSpacing)
{
    if (!text) return 0.0f;

    std::size_t len = std::strlen(text);
    if (len == 0) return 0.0f;

    const float glyphWidth = (4.0f / 6.0f) * scaleX;
    const float advance = glyphWidth + letterSpacing;

    return glyphWidth + (static_cast<float>(len) - 1.0f) * advance;
}

void Ng_drawTextTricolor(const char* text, float centerY,
                          float scaleX, float scaleY,
                          float letterSpacing, float thickness,
                          float brightness)
{
    if (!text) return;

    const float glyphWidth = (4.0f / 6.0f) * scaleX;
    const float advance = glyphWidth + letterSpacing;

    float totalWidth = Ng_textWidth(text, scaleX, letterSpacing);
    float startX = -totalWidth / 2.0f;   // centers on x = 0
    float cursorX = startX + glyphWidth / 2.0f;

    bool inWord = false;
    int wordIndex = -1;

    for (const char* p = text; *p != '\0'; ++p)
    {
        if (*p == ' ')
        {
            inWord = false;
            cursorX += advance;
            continue;
        }

        if (!inWord)
        {
            inWord = true;
            wordIndex++;
        }

        const float* c = Ng_TRICOLOR[wordIndex % 3];
        glColor3f(c[0] * brightness, c[1] * brightness, c[2] * brightness);

        Ng_drawLetter(*p, cursorX, centerY, scaleX, scaleY, thickness);
        cursorX += advance;
    }
}