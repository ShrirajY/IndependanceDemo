#include <GL/freeglut.h>
#include "Monuments/Lakshmi/Headers/Konark.h"
#include "Monuments/Shriraj/Headers/RedFort.h"
#include "Monuments/Mrunali/Headers/Sarnath.h"

bool bIsFullScreen = false;
float elapsedTimeSeconds = 0.0f;
float deltaTime = 0.016f;

int main(int argc, char* argv[])
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
    return(0);
}

void initialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
    if (height <= 0) height = 1;
    float aspect = (float)width / (float)height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= 1.0f)
        glOrtho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    else
        glOrtho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawKonark(0.0f - elapsedTimeSeconds, 0.0f, 1.0f, 1.0f);
    draw_redfort(2.0 - elapsedTimeSeconds, 0.0, 0.5, 0.5);
    DrawSarnathTemple(4.0f - elapsedTimeSeconds, 0.0f, 1.0f, 1.0f);
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
// cl.exe /c /EHsc /I D:\freeglut\include OGL.cpp

// link.exe OGL.obj /LIBPATH:D:\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE