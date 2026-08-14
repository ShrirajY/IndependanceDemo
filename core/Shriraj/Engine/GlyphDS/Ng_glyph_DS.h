#ifndef NG_GLYPH_H
#define NG_GLYPH_H

// -----------------------------------------------------------------------
// Ng_glyph
//
// Filled, "double stranded" capital letter glyphs: every stroke is drawn
// as a solid bar (two parallel edges) using Ng_drawRectangle for
// horizontal/vertical segments and Ng_drawRotatedRectangle for diagonal
// ones, with small square joints (also Ng_drawRectangle) filling the
// corners where segments meet. This replaces the old single hairline
// GL_LINE_STRIP look with bold, filled letters.
//
// Every glyph is authored on the SAME fixed 4 (wide) x 6 (tall) design
// grid, so all letters share one consistent base size. That base size is
// mapped to a 1.0-unit-tall box centered on (centerX, centerY):
//
//      worldX = centerX + (gridX - 2) * (1/6) * scaleX
//      worldY = centerY + (gridY - 3) * (1/6) * scaleY
//
// So with scaleX = scaleY = 1.0 every letter is exactly 1.0 units tall
// and ~0.667 units wide, centered on (centerX, centerY). Passing
// different scaleX / scaleY values stretches the letter non-uniformly;
// pass equal values to scale it uniformly.
//
// `thickness` is now a WORLD-SPACE size (like width/height passed to
// Ng_drawRectangle), not a glLineWidth pixel width. It's the thickness
// of the filled bar that makes up each stroke. A good starting point is
// roughly 5-10% of the letter's height (e.g. 0.06-0.10 at scaleY = 1.0).
// -----------------------------------------------------------------------

// Default stroke thickness used by the letter functions, in world units.
#define NG_LETTER_DEFAULT_LINE_WIDTH 0.08f

// Draw any single uppercase letter 'A'-'Z' (unrecognized chars are skipped).
void Ng_drawLetter(char c, float centerX, float centerY,
                    float scaleX, float scaleY,
                    float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);

// Draw a left-to-right string of uppercase letters (spaces are honored).
// letterSpacing is the gap, in the same normalized units as the glyph
// width (~0.667 at scaleX = 1), added between successive letters.
void Ng_drawText(const char* text, float startX, float centerY,
                  float scaleX, float scaleY,
                  float letterSpacing = 0.15f,
                  float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);

// Individual letter functions, in case you want to call them directly.
void Ng_drawLetterA(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterB(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterC(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterD(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterE(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterF(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterG(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterH(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterI(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterJ(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterK(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterL(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterM(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterN(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterO(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterP(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterQ(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterR(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterS(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterT(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterU(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterV(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterW(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterX(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterY(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);
void Ng_drawLetterZ(float centerX, float centerY, float scaleX, float scaleY, float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);

#endif // NG_GLYPH_H