#pragma once
#ifndef TIME_MATH_H
#define TIME_MATH_H

#include <GL/freeglut.h>

// Global variables declaration
extern float elapsedTime;
extern bool isCrawling;
extern float spiderTy;

// Animation update callback function
void updateTimer(int value);

#endif // TIME_MATH_H