#include "../Headers/Hampi.h"
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../../../core/Siddharth/Engine/Headers/E_Math.h"
#include "../../../core/Siddharth/Engine/Headers/E_2DShapes.h"

void drawHampi(float centerX, float centerY, float scaleX, float scaleY)
{
    float scaleXInPercent, scaleYInPercent;
    scaleXInPercent = scaleYInPercent = scaleX * 100.0f;
    float width = 0.5f, height = 0.15f;
    float translationX = centerX, translationY = centerY;
    float radius = 0.01f;
    float theta = 0.0f;
    float r, g, b, a;
    r = g = a = 1.0f; b = 1.0f;

    /////////////////
    // top - decor //
    /////////////////
    drawHampiTempleOutline(scaleXInPercent, scaleYInPercent, translationX + 0.2f, translationY + -0.2f, r * 0.0f, g * 0.0f, b * 0.0f, a);
    drawHampiTempleOutline(scaleXInPercent * 0.98f, scaleYInPercent * 0.98f, translationX + 0.2f, translationY + -0.2f, r * 0.92f, g * 0.92f, b * 0.92f, a * 0.11f);
    // top - pillar decor objects
    for(float x = -0.12f; x <= 0.6f; x = x + (radius * 10.0f))
    {
        float _radius = (x > -0.1f && x < 0.57f) ? 2 * radius : radius;
        drawHampiTemplePillarDecor(scaleXInPercent, scaleYInPercent, _radius, translationX + x, translationY + 0.525f, r * 0.87f, g * 0.87f, b * 0.87f, a);
    }

    // top - pillar
    drawQuad(scaleXInPercent, scaleYInPercent, width / 14.0f, height * 2.5f, translationX + 0.08f, translationY + 0.3f, theta, r * 0.87f, g * 0.87f, b * 0.87f, a);
    drawQuad(scaleXInPercent, scaleYInPercent, width / 14.0f, height * 2.5f, translationX + 0.28f, translationY + 0.3f, theta, r * 0.87f, g * 0.87f, b * 0.87f, a);
    drawQuad(scaleXInPercent, scaleYInPercent, width / 14.0f, height * 2.5f, translationX + 0.38f, translationY + 0.3f, theta, r * 0.87f, g * 0.87f, b * 0.87f, a);
    drawQuad(scaleXInPercent, scaleYInPercent, width / 14.0f, height * 2.5f, translationX + 0.48f, translationY + 0.3f, theta, r * 0.87f, g * 0.87f, b * 0.87f, a);

    // top - sine decors
    drawHampiTempleTopSineLowerDecor(scaleXInPercent * 1.05f, scaleYInPercent, width / 2.0f, height / 2.0f, translationX + 0.22f, translationY + 0.605f, theta, r * 0.08f, g * 0.07f, b * 0.09f, a);
    drawHampiTempleTopSineDecor(scaleXInPercent * 1.26f, scaleYInPercent, width / 4.0f, height / 2.0f, translationX - 0.04f, translationY + 0.63f, theta,  r * 0.25f, g * 0.25f, b * 0.25f, a);
    drawHampiTempleTopSineDecor(scaleXInPercent * 1.34f, scaleYInPercent, width / 4.0f, height / 2.0f, translationX + 0.487f, translationY + 0.63f, theta, r * 0.25f, g * 0.25f, b * 0.25f, a);
    drawHampiTempleTopSineDecor(scaleXInPercent * 1.42f, scaleYInPercent, width / 2.0f, height / 2.0f, translationX + 0.22f, translationY + 0.63f, theta,  r * 0.25f, g * 0.25f, b * 0.25f, a);

    ////////////////////
    // middle - decor //
    ////////////////////
    drawHampiTempleMiddleDecor(scaleXInPercent, scaleYInPercent, width, height, translationX, translationY, theta, r * 0.25f, g * 0.25f, b * 0.25f, a);

    ///////////////////
    // lower - decor //
    ///////////////////
    drawHampiTempleLowerDecor(scaleXInPercent, scaleYInPercent, radius * 10.0f, width, height, translationX, translationY, theta, r * 0.85f, g * 0.85f, b * 0.85f, a);
}

// the flowery looking artefact from which the pillar comes out
void drawHampiTemplePillarDecor(float scaleXInPercent, float scaleYInPercent, float radius, float tx, float ty, float red, float green, float blue, float alpha)
{
    drawCircleWithPolygon(scaleXInPercent, scaleYInPercent * 3.0f, radius, tx, ty, red, green, blue, alpha);
    drawCircleWithPolygon(scaleXInPercent * 3.0f, scaleYInPercent, radius, tx, ty, red, green, blue, alpha);
}

// hampi temple outline
void drawHampiTempleOutline(float scaleXInPercent, float scaleYInPercent, float tx, float ty, float red, float green, float blue, float alpha)
{    // hampi temple outline variables and code
    float scaleX = scaleXInPercent / 100.0f;
    float scaleY = scaleYInPercent / 100.0f;

    glColor4f(red, green, blue, alpha);

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(0.24702f  * scaleX + tx, 0.71712f * scaleY + ty, 0.0f);
        glVertex3f(0.40147f  * scaleX + tx, 0.68618f * scaleY + ty, 0.0f);
        glVertex3f(0.45517f  * scaleX + tx, 0.73837f * scaleY + ty, 0.0f);
        glVertex3f(0.45485f  * scaleX + tx, 0.75255f * scaleY + ty, 0.0f);
        glVertex3f(0.43181f  * scaleX + tx, 0.75568f * scaleY + ty, 0.0f);
        glVertex3f(0.42613f  * scaleX + tx, 0.75966f * scaleY + ty, 0.0f);
        glVertex3f(0.40286f  * scaleX + tx, 0.79878f * scaleY + ty, 0.0f);
        glVertex3f(0.38625f  * scaleX + tx, 0.82195f * scaleY + ty, 0.0f);
        glVertex3f(0.3654f   * scaleX + tx, 0.86289f * scaleY + ty, 0.0f);
        glVertex3f(0.26113f  * scaleX + tx, 0.86327f * scaleY + ty, 0.0f);
        glVertex3f(0.23757f  * scaleX + tx, 0.85053f * scaleY + ty, 0.0f);
        glVertex3f(0.231f    * scaleX + tx, 0.84783f * scaleY + ty, 0.0f);
        glVertex3f(0.22482f  * scaleX + tx, 0.85555f * scaleY + ty, 0.0f);
        glVertex3f(-0.13081f * scaleX + tx, 0.88654f * scaleY + ty, 0.0f);
        glVertex3f(-0.14221f * scaleX + tx, 0.84839f * scaleY + ty, 0.0f);
        glVertex3f(-0.17088f * scaleX + tx, 0.85269f * scaleY + ty, 0.0f);
        glVertex3f(-0.2915f  * scaleX + tx, 0.85799f * scaleY + ty, 0.0f);
        glVertex3f(-0.29465f * scaleX + tx, 0.82569f * scaleY + ty, 0.0f);
        glVertex3f(-0.31278f * scaleX + tx, 0.80362f * scaleY + ty, 0.0f);
        glVertex3f(-0.32144f * scaleX + tx, 0.77211f * scaleY + ty, 0.0f);
        glVertex3f(-0.33563f * scaleX + tx, 0.77053f * scaleY + ty, 0.0f);
        glVertex3f(-0.34587f * scaleX + tx, 0.74138f * scaleY + ty, 0.0f);
        glVertex3f(-0.34193f * scaleX + tx, 0.72247f * scaleY + ty, 0.0f);
        glVertex3f(-0.37319f * scaleX + tx, 0.68719f * scaleY + ty, 0.0f);
        glVertex3f(-0.38251f * scaleX + tx, 0.65122f * scaleY + ty, 0.0f);
        glVertex3f(-0.39368f * scaleX + tx, 0.63233f * scaleY + ty, 0.0f);
        glVertex3f(-0.39368f * scaleX + tx, 0.6057f  * scaleY + ty, 0.0f);
        glVertex3f(-0.39363f * scaleX + tx, 0.56619f * scaleY + ty, 0.0f);
        glVertex3f(-0.3458f  * scaleX + tx, 0.56138f * scaleY + ty, 0.0f);
        glVertex3f(-0.33441f * scaleX + tx, 0.52925f * scaleY + ty, 0.0f);
        glVertex3f(-0.32754f * scaleX + tx, 0.49318f * scaleY + ty, 0.0f);
        glVertex3f(-0.31336f * scaleX + tx, 0.48673f * scaleY + ty, 0.0f);
        glVertex3f(-0.31397f * scaleX + tx, 0.31112f * scaleY + ty, 0.0f);
        glVertex3f(-0.34316f * scaleX + tx, 0.2715f  * scaleY + ty, 0.0f);
        glVertex3f(-0.4f     * scaleX + tx, 0.18f    * scaleY + ty, 0.0f);
        glVertex3f(-0.38522f * scaleX + tx, 0.17801f * scaleY + ty, 0.0f);
        glVertex3f(-0.38162f * scaleX + tx, 0.1573f  * scaleY + ty, 0.0f);
        glVertex3f(-0.39107f * scaleX + tx, 0.12714f * scaleY + ty, 0.0f);
        glVertex3f(-0.38792f * scaleX + tx, 0.10913f * scaleY + ty, 0.0f);
        glVertex3f(-0.37442f * scaleX + tx, 0.10643f * scaleY + ty, 0.0f);
        glVertex3f(-0.35371f * scaleX + tx, 0.10823f * scaleY + ty, 0.0f);
        glVertex3f(-0.35461f * scaleX + tx, 0.08348f * scaleY + ty, 0.0f);
        glVertex3f(-0.44678f * scaleX + tx, -0.26616f* scaleY + ty, 0.0f);
        glVertex3f(-0.44224f * scaleX + tx, -0.28834f* scaleY + ty, 0.0f);
        glVertex3f(-0.28754f * scaleX + tx, -0.27915f* scaleY + ty, 0.0f);
        glVertex3f(0.03499f  * scaleX + tx, -0.28112f* scaleY + ty, 0.0f);
        glVertex3f(0.27581f  * scaleX + tx, -0.2729f * scaleY + ty, 0.0f);
        glVertex3f(0.31223f  * scaleX + tx, 0.13474f * scaleY + ty, 0.0f);
        glVertex3f(0.39691f  * scaleX + tx, 0.29355f * scaleY + ty, 0.0f);
        glVertex3f(0.39387f  * scaleX + tx, 0.32699f * scaleY + ty, 0.0f);
        glVertex3f(0.40197f  * scaleX + tx, 0.35789f * scaleY + ty, 0.0f);
        glVertex3f(0.38221f  * scaleX + tx, 0.41362f * scaleY + ty, 0.0f);
        glVertex3f(0.36854f  * scaleX + tx, 0.46783f * scaleY + ty, 0.0f);
        glVertex3f(0.37056f  * scaleX + tx, 0.51039f * scaleY + ty, 0.0f);
        glVertex3f(0.36702f  * scaleX + tx, 0.6107f  * scaleY + ty, 0.0f);
        glVertex3f(0.39792f  * scaleX + tx, 0.63957f * scaleY + ty, 0.0f);
        glVertex3f(0.40147f  * scaleX + tx, 0.68618f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glVertex3f(0.45485f * scaleX + tx, 0.75255f * scaleY + ty, 0.0f);
        glVertex3f(0.43181f * scaleX + tx, 0.75568f * scaleY + ty, 0.0f);
        glVertex3f(0.44518f * scaleX + tx, 0.7807f  * scaleY + ty, 0.0f);
        glVertex3f(0.4594f  * scaleX + tx, 0.77274f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0.22482f  * scaleX + tx, 0.85555f  * scaleY + ty, 0.0f);
        glVertex3f(0.22366f  * scaleX + tx, 0.88811f  * scaleY + ty, 0.0f);
        glVertex3f(-0.13081f * scaleX + tx, 0.88654f  * scaleY + ty, 0.0f);
        glVertex3f(-0.17088f * scaleX + tx, 0.85269f  * scaleY + ty, 0.0f);
        glVertex3f(-0.18907f * scaleX + tx, 0.86745f  * scaleY + ty, 0.0f);
        glVertex3f(-0.2915f  * scaleX + tx, 0.85799f  * scaleY + ty, 0.0f);
        glVertex3f(-0.37319f * scaleX + tx, 0.68719f  * scaleY + ty, 0.0f);
        glVertex3f(-0.3905f  * scaleX + tx, 0.70362f  * scaleY + ty, 0.0f);
        glVertex3f(-0.38251f * scaleX + tx, 0.65122f  * scaleY + ty, 0.0f);
        glVertex3f(-0.37319f * scaleX + tx, 0.68719f  * scaleY + ty, 0.0f);
        glVertex3f(-0.34193f * scaleX + tx, 0.72247f  * scaleY + ty, 0.0f);
        glVertex3f(-0.35409f * scaleX + tx, 0.72227f  * scaleY + ty, 0.0f);
        glVertex3f(-0.37319f * scaleX + tx, 0.68719f  * scaleY + ty, 0.0f);
        glVertex3f(-0.35409f * scaleX + tx, 0.72227f  * scaleY + ty, 0.0f);
        glVertex3f(-0.35587f * scaleX + tx, 0.73514f  * scaleY + ty, 0.0f);
        glVertex3f(-0.34316f * scaleX + tx, 0.2715f   * scaleY + ty, 0.0f);
        glVertex3f(-0.33482f * scaleX + tx, 0.30903f  * scaleY + ty, 0.0f);
        glVertex3f(-0.31397f * scaleX + tx, 0.31112f  * scaleY + ty, 0.0f);
        glVertex3f(-0.38162f * scaleX + tx, 0.1573f   * scaleY + ty, 0.0f);
        glVertex3f(-0.4f     * scaleX + tx, 0.14f     * scaleY + ty, 0.0f);
        glVertex3f(-0.39107f * scaleX + tx, 0.12714f  * scaleY + ty, 0.0f);
        glVertex3f(0.38221f  * scaleX + tx, 0.41362f  * scaleY + ty, 0.0f);
        glVertex3f(0.39387f  * scaleX + tx, 0.44199f  * scaleY + ty, 0.0f);
        glVertex3f(0.36854f  * scaleX + tx, 0.46783f  * scaleY + ty, 0.0f);
        glVertex3f(0.4626f   * scaleX + tx, -0.2635f  * scaleY + ty, 0.0f);
        glVertex3f(0.56832f  * scaleX + tx, -0.20476f * scaleY + ty, 0.0f);
        glVertex3f(0.56597f  * scaleX + tx, -0.26585f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(-0.37532f  * scaleX + tx, 0.27119f * scaleY + ty, 0.0f);
        glVertex3f(-0.36193f  * scaleX + tx, 0.27984f * scaleY + ty, 0.0f);
        glVertex3f(-0.34316f  * scaleX + tx, 0.2715f  * scaleY + ty, 0.0f);
        glVertex3f(-0.4f      * scaleX + tx, 0.18f    * scaleY + ty, 0.0f);
        glVertex3f(-0.4f      * scaleX + tx, 0.24f    * scaleY + ty, 0.0f);
        glVertex3f(-0.38432f  * scaleX + tx, 0.27704f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex3f(0.31223f * scaleX + tx, 0.13474f * scaleY + ty, 0.0f);
        glVertex3f(0.52486f * scaleX + tx, 0.14062f * scaleY + ty, 0.0f);
        glVertex3f(0.52103f * scaleX + tx, 0.15702f * scaleY + ty, 0.0f);
        glVertex3f(0.50654f * scaleX + tx, 0.17541f * scaleY + ty, 0.0f);
        glVertex3f(0.49038f * scaleX + tx, 0.18544f * scaleY + ty, 0.0f);
        glVertex3f(0.48648f * scaleX + tx, 0.19993f * scaleY + ty, 0.0f);
        glVertex3f(0.50821f * scaleX + tx, 0.20662f * scaleY + ty, 0.0f);
        glVertex3f(0.48871f * scaleX + tx, 0.22835f * scaleY + ty, 0.0f);
        glVertex3f(0.49094f * scaleX + tx, 0.26903f * scaleY + ty, 0.0f);
        glVertex3f(0.47533f * scaleX + tx, 0.28965f * scaleY + ty, 0.0f);
        glVertex3f(0.43019f * scaleX + tx, 0.27572f * scaleY + ty, 0.0f);
        glVertex3f(0.39691f * scaleX + tx, 0.29355f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(0.27581f * scaleX + tx, -0.2729f  * scaleY + ty, 0.0f);
        glVertex3f(0.31223f * scaleX + tx, 0.13474f  * scaleY + ty, 0.0f);
        glVertex3f(0.36392f * scaleX + tx, 0.09832f  * scaleY + ty, 0.0f);
        glVertex3f(0.41443f * scaleX + tx, 0.04898f  * scaleY + ty, 0.0f);
        glVertex3f(0.43323f * scaleX + tx, -0.00858f * scaleY + ty, 0.0f);
        glVertex3f(0.43675f * scaleX + tx, -0.05087f * scaleY + ty, 0.0f);
        glVertex3f(0.41443f * scaleX + tx, -0.119f   * scaleY + ty, 0.0f);
        glVertex3f(0.4344f  * scaleX + tx, -0.16129f * scaleY + ty, 0.0f);
        glVertex3f(0.56832f * scaleX + tx, -0.20476f * scaleY + ty, 0.0f);
        glVertex3f(0.4626f  * scaleX + tx, -0.2635f  * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(-0.42684f * scaleX + tx, -0.2408f  * scaleY + ty, 0.0f);
        glVertex3f(-0.35461f * scaleX + tx, 0.08348f  * scaleY + ty, 0.0f);
        glVertex3f(-0.37082f * scaleX + tx, 0.08213f  * scaleY + ty, 0.0f);
        glVertex3f(-0.39557f * scaleX + tx, 0.09113f  * scaleY + ty, 0.0f);
        glVertex3f(-0.40773f * scaleX + tx, 0.08843f  * scaleY + ty, 0.0f);
        glVertex3f(-0.43564f * scaleX + tx, 0.0182f   * scaleY + ty, 0.0f);
        glVertex3f(-0.49461f * scaleX + tx, 0.02811f  * scaleY + ty, 0.0f);
        glVertex3f(-0.50451f * scaleX + tx, 0.02766f  * scaleY + ty, 0.0f);
        glVertex3f(-0.52207f * scaleX + tx, 0.04881f  * scaleY + ty, 0.0f);
        glVertex3f(-0.54682f * scaleX + tx, 0.04521f  * scaleY + ty, 0.0f);
        glVertex3f(-0.58914f * scaleX + tx, 0.02226f  * scaleY + ty, 0.0f);
        glVertex3f(-0.60624f * scaleX + tx, 0.02991f  * scaleY + ty, 0.0f);
        glVertex3f(-0.6229f  * scaleX + tx, 0.03126f  * scaleY + ty, 0.0f);
        glVertex3f(-0.67602f * scaleX + tx, 0.0146f   * scaleY + ty, 0.0f);
        glVertex3f(-0.64631f * scaleX + tx, -0.05382f * scaleY + ty, 0.0f);
        glVertex3f(-0.65576f * scaleX + tx, -0.07723f * scaleY + ty, 0.0f);
        glVertex3f(-0.64631f * scaleX + tx, -0.10649f * scaleY + ty, 0.0f);
        glVertex3f(-0.6532f  * scaleX + tx, -0.16115f * scaleY + ty, 0.0f);
        glVertex3f(-0.71804f * scaleX + tx, -0.16646f * scaleY + ty, 0.0f);
        glVertex3f(-0.7726f  * scaleX + tx, -0.17426f * scaleY + ty, 0.0f);
        glVertex3f(-0.78501f * scaleX + tx, -0.18595f * scaleY + ty, 0.0f);
        glVertex3f(-0.80981f * scaleX + tx, -0.1987f  * scaleY + ty, 0.0f);
        glVertex3f(-0.8415f  * scaleX + tx, -0.20062f * scaleY + ty, 0.0f);
        glVertex3f(-0.85612f * scaleX + tx, -0.22432f * scaleY + ty, 0.0f);
        glVertex3f(-0.84755f * scaleX + tx, -0.27221f * scaleY + ty, 0.0f);
        glVertex3f(-0.4221f  * scaleX + tx, -0.28834f * scaleY + ty, 0.0f);
       
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(-0.67737f * scaleX + tx, -0.03851f * scaleY + ty, 0.0f);
        glVertex3f(-0.72553f * scaleX + tx, -0.03671f * scaleY + ty, 0.0f);
        glVertex3f(-0.72193f * scaleX + tx, -0.01421f * scaleY + ty, 0.0f);
        glVertex3f(-0.67602f * scaleX + tx, 0.0146f   * scaleY + ty, 0.0f);
        glVertex3f(-0.64631f * scaleX + tx, -0.05382f * scaleY + ty, 0.0f);
        glVertex3f(-0.67602f * scaleX + tx, -0.04797f * scaleY + ty, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(-0.68f    * scaleX + tx, -0.12f    * scaleY + ty, 0.0f);
        glVertex3f(-0.65576f * scaleX + tx, -0.07723f * scaleY + ty, 0.0f);
        glVertex3f(-0.64631f * scaleX + tx, -0.10649f * scaleY + ty, 0.0f);
        glVertex3f(-0.66341f * scaleX + tx, -0.12584f * scaleY + ty, 0.0f);
        glVertex3f(-0.66f    * scaleX + tx, -0.14f    * scaleY + ty, 0.0f);
        glVertex3f(-0.67917f * scaleX + tx, -0.16501f * scaleY + ty, 0.0f);
    }
    glEnd();
}

void drawHampiTempleTopSineDecor(float scaleXInPercent, float scaleYInPercent, float width, float height, float tx, float ty, float theta, float r, float g, float b, float a)
{
    glColor4f(r, g, b, a);

    glBegin(GL_QUADS);
    {
        drawQuad(scaleXInPercent, scaleYInPercent, width, height, tx, ty, theta, r * 0.98f, g * 0.97f, b, a);
        drawQuad(scaleXInPercent, scaleYInPercent, width, height * 0.7667f, tx, -height + ty, theta, r, g, b, a);
    }
    glEnd();

    float rangePositive = (width * 0.5f) + (width * 0.1f);
    glBegin(GL_TRIANGLE_STRIP);
    {
        float angle = -M_PI;
        float t_angle = 100.0f / 60.0f;
        for(float x = -rangePositive; x <= rangePositive; x = x + 0.01f, t_angle = t_angle + (5.0f / 3.0f))
        {
            angle = lerp(-M_PI, 0.0f, t_angle);
            float y = (0.33f * height) * sinf(angle) - height;
            glVertex3f(x + tx, y + ty, 0.0f);
        }
    }
    glEnd();    
}

void drawHampiTempleTopSineLowerDecor(float scaleInXPercent, float scaleFactorYInPercent, float width, float height, float tx, float ty, float theta, float r, float g, float b, float a)
{
    glColor4f(r, g, b, a);
    glBegin(GL_LINE_STRIP);
    {
        float angle;
        float rangePositive = (width * 1.42f); // + (width * 0.1f);
        float t_angle = 100.0f / (60.0f);
        for(float x = -rangePositive; x <= rangePositive; x = x + 0.01f, t_angle = t_angle + M_PI * 0.5f)
        {
            angle = lerp(0.0f, 2 * M_PI, t_angle);
            float y1 = (0.33f * height) * sinf(angle) - height;
            float y2 = (0.33f * height) * -sinf(angle) - height;
            glVertex3f(x + tx, y1 + ty, 0.0f);
            glVertex3f(x + tx, y2 + ty, 0.0f);
        }
    }
    glEnd();
}

void drawHampiTempleMiddleDecor(float scaleXInPercent, float scaleYInPercent, float width, float height, float tx, float ty, float theta, float r, float g, float b, float a)
{
    // Middle - higher decor
    drawQuad(scaleXInPercent, scaleYInPercent, width / 5.0f, height / 3.75f, tx - 0.058f, ty + 0.11f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a);   // middle black
    drawQuad(scaleXInPercent, scaleYInPercent, width / 4.5f, height / 3.75f, tx - 0.058f, ty + 0.13f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent, scaleYInPercent, width / 6.0f, height / 3.75f, tx - 0.058f, ty + 0.1f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);

    drawQuad(scaleXInPercent * 3.5f, scaleYInPercent, width / 5.0f, height / 3.45f, tx + 0.2f, ty + 0.11f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a); // middle black bar
    drawQuad(scaleXInPercent * 3.0f, scaleYInPercent, width / 4.5f, height / 3.45f, tx + 0.2f, ty + 0.13f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent * 3.6f, scaleYInPercent, width / 6.0f, height / 3.45f, tx + 0.2f, ty + 0.1f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);

    drawQuad(scaleXInPercent * 1.65f, scaleYInPercent, width / 5.0f, height / 3.75f, tx + 0.48f, ty + 0.11f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a);   // middle black
    drawQuad(scaleXInPercent * 1.65f, scaleYInPercent, width / 4.5f, height / 3.75f, tx + 0.48f, ty + 0.13f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent * 2.2f, scaleYInPercent, width / 6.0f, height / 3.75f, tx  + 0.48f, ty  + 0.1f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);

    // Middle - lower decor
    drawQuad(scaleXInPercent, scaleYInPercent, width / 5.0f, height / 3.75f, tx - 0.14f, ty + 0.01f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a);   // middle black
    drawQuad(scaleXInPercent, scaleYInPercent, width / 4.5f, height / 3.75f, tx - 0.14f, ty + 0.03f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent, scaleYInPercent, width / 6.0f, height / 3.75f, tx - 0.14f, ty + 0.0f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);

    drawQuad(scaleXInPercent * 5.5f, scaleYInPercent, width / 5.0f, height / 3.45f, tx + 0.2f, ty + 0.01f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a); // middle black bar
    drawQuad(scaleXInPercent * 5.0f, scaleYInPercent, width / 4.5f, height / 3.45f, tx + 0.2f, ty + 0.03f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent * 5.6f, scaleYInPercent, width / 6.0f, height / 3.45f, tx + 0.2f, ty + 0.0f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);

    drawQuad(scaleXInPercent * 1.65f, scaleYInPercent, width / 5.0f, height / 3.75f, tx + 0.58f, ty + 0.01f, theta, r * 0.2f, g * 0.2f, b * 0.2f, a);   // middle black
    drawQuad(scaleXInPercent * 1.65f, scaleYInPercent, width / 4.5f, height / 3.75f, tx + 0.58f, ty + 0.03f + (height / 3.75f) / 2.0f, theta, r, g, b, a);
    drawQuad(scaleXInPercent * 2.2f, scaleYInPercent, width / 6.0f, height / 3.75f, tx + 0.58f, ty + 0.0f + -(height / 3.75f) / 2.0f, theta, r, g, b, a);
}

void drawHampiTempleLowerDecor(float scaleXInPercent, float scaleYInPercent, float radius, float width, float height, float tx, float ty, float theta, float r, float g, float b, float a)
{
    for(float x = radius; x >= 0.0f; x = x - (radius / 5.0f))
    {
        drawCircleWithPolygon(scaleXInPercent * 1.54f, scaleYInPercent * 1.54f, x, tx + 0.49f, ty - 0.23f, r * 0.85f - 2*x, g * 0.85f - 2*x, b * 0.85f - 2*x, a);
        drawCircleWithLine(scaleXInPercent * 1.54f, scaleYInPercent * 1.54f, x, tx + 0.49f, ty - 0.23f, r * 0.0f, g * 0.0f, b * 0.0f, a, 20.0f);
    }

    for(float x = radius; x >= 0.0f; x = x - (radius / 5.0f))
    {
        drawCircleWithPolygon(scaleXInPercent * 1.54f, scaleYInPercent * 1.54f, x, tx, ty - 0.23f, r * 0.85f - 2*x, g * 0.85f - 2*x, b * 0.85f - 2*x, a);
        drawCircleWithLine(scaleXInPercent * 1.54f, scaleYInPercent * 1.54f, x, tx, ty - 0.23f, r * 0.0f, g * 0.0f, b * 0.0f, a, 3.0f);
    }

    drawQuad(scaleXInPercent * 2.0f, scaleYInPercent * 2.42f, width, height / 4.0f, tx + 0.27f, ty - 0.43f, theta, r * 0.25f, g * 0.25f, b * 0.25f, a);

    // sine wave design
    glBegin(GL_LINE_STRIP);
    {
        glLineWidth(20.0f);
        glColor4f(r * 0.75f, g * 0.75f, b * 0.75f, a * 0.9f);
        float angleStep = 0.05f;
        float t_angle = 0.0f;
        float amplitude = 0.04f, frequency = 8.0f;
        for(float x = -width; x <= width; x = x + 0.05f, t_angle = t_angle + angleStep)
        {
            float y = amplitude * sinf(t_angle * frequency);
            glVertex3f(x + tx + 0.27f, y + ty - 0.43f, 0.0f);
        }
        for(float x = -width; x <= width; x = x + 0.05f, t_angle = t_angle + angleStep)
        {
            float y = amplitude * cosf(t_angle * frequency);
            glVertex3f(x + tx + 0.27f, y + ty - 0.43f, 0.0f);
        }
        
        for(float x = width; x >= -width; x = x - 0.05f, t_angle = t_angle + angleStep)
        {
            float y = amplitude * sinf(t_angle * frequency);
            glVertex3f(x + tx + 0.27f, y + ty - 0.43f, 0.0f);
        }
        for(float x = width; x >= -width; x = x - 0.05f, t_angle = t_angle + angleStep)
        {
            float y = amplitude * cosf(t_angle * frequency);
            glVertex3f(x + tx + 0.27f, y + ty - 0.43f, 0.0f);
        }
        glLineWidth(1.0f);
    }
    glEnd();
}

