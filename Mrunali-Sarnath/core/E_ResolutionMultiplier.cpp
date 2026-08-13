// Resolution multiplier
float CurrentWidth = 0.0f;
float CurrentHeight = 0.0f;
float ResolutionMultiplier = 0.0f;
void Resize(int width, int height)
{
    if(height <= 0)
        height = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	CurrentWidth = glutGet(GLUT_WINDOW_WIDTH);
	CurrentHeight = glutGet(GLUT_WINDOW_HEIGHT);
	ResolutionMultiplier = CurrentWidth/CurrentHeight;
}