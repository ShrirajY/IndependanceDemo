#ifndef NG_GLYPH_H
#define NG_GLYPH_H



#define NG_LETTER_DEFAULT_LINE_WIDTH 0.08f

void Ng_drawLetter(char c, float centerX, float centerY,
                    float scaleX, float scaleY,
                    float thickness = NG_LETTER_DEFAULT_LINE_WIDTH);

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
void Ng_drawTextTricolor(const char* text, float centerY,
                          float scaleX, float scaleY,
                          float letterSpacing, float thickness,
                          float brightness = 1.0f);
#endif // NG_GLYPH_H