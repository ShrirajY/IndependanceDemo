#ifndef OUTRO_ANIMATION_H
#define OUTRO_ANIMATION_H

// Call once during setup to initialize any starting state
void InitOutroAnimation();

// Call inside your main display loop/function when it is time to draw
void DrawOutroAnimationStep(float deltaTime);


void InitializeOutroAnimation();
void SetOutroStartTime(float startTime);
void DrawOutroAnimation(float globalTime);

#endif // OUTRO_ANIMATION_H
