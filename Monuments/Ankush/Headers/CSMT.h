// void drawRedFort(float centerX, float centerYXY);
void glTranslateVertex(float x, float y, float scalefactor, float translateX, float translateY);
void drawRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float scaleFactor, float translateX, float translateY);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float scaleFactor, float translateX, float translateY);
void drawLine(float x1, float y1,float x2, float y2, float scaleFactor, float translateX, float translateY);
void drawCircle(float centerX, float centerY, float radius, float scaleFactor, float translateX, float translateY);
void drawCircleOutline(float centerX, float centerY, float radius, float scaleFactor, float translateX, float translateY);
void drawArch(float centerX, float archBottomY, float width, float height, float scaleFactor, float translateX, float translateY);
void drawArchOutline(float centerX, float archBottomY, float width, float height, float scaleFactor, float translateX, float translateY);

void drawPillar(float x, float y, float width, float height, float scaleFactor, float translateX, float translateY);
void drawWindow(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY);
void drawGothicWindow(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY);
void drawCircularWindow(float cx, float cy, float radius, float scaleFactor, float translateX, float translateY);
void drawRoof(float x1, float y1, float x2, float y2, float peakX, float peakY, float scaleFactor, float translateX, float translateY);
void drawTowerRoof(float cx, float bottom, float width, float height, float scaleFactor, float translateX, float translateY);
void drawCross(float cx, float cy, float size, float scaleFactor, float translateX, float translateY);
void drawSideTower(float cx, float scaleFactor, float translateX, float translateY);
void drawDome(float scaleFactor, float translateX, float translateY);
void drawCenterTower(float scaleFactor, float translateX, float translateY);
void drawMainWall(float scaleFactor, float translateX, float translateY);
void drawDecorations(float scaleFactor, float translateX, float translateY);
void drawBuilding(float scaleFactor, float translateX, float translateY);
void drawGround(float scaleFactor, float translateX, float translateY);
void drawRoad(float scaleFactor, float translateX, float translateY);
void drawBackground(float scaleFactor, float translateX, float translateY);

