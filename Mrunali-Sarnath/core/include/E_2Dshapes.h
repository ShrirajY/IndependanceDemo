// Four coordinate functions
void E_DrawSquareFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scale, float tx, float ty);
void E_DrawTriangleFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float scale, float tx, float ty);
void E_DrawRectangleFourCoord(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scale, float tx, float ty);
void E_DrawStraightLines2Coor(float x1, float y1, float x2, float y2, float scale, float tx, float ty);

// Circle functions
void E_DrawSemiCircle(float scale, float tx, float ty);
void E_DrawCircle(float scale, float tx, float ty);

// Width Height Functions
void E_DrawRectangleWH(float w, float h, float tx, float ty, float theta, float r, float g, float b);
void E_DrawTriangleWH(float w, float h, float scale, float tx, float ty, float theta, float r, float g, float b);
