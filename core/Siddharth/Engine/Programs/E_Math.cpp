#include "../Headers/E_Math.h"
#define _USE_MATH_DEFINES
#include <math.h>
// #include <stdio.h>  // for debug logs

float lerp(float startVal, float endVal, float t)
{
    startVal = startVal + (endVal - startVal) * t;
    return startVal;
}

bool  isFloatValueEqualTo(const float value, const float equalTo, float epsilon)
{
    // const float epsilon = 1e-5f;
    float diff = fabs(value - equalTo);

    // printf("isFloatValueEqualTo(): value = %f, equalTo = %f \t epsilon = %f, diff = %f\n", value, equalTo, epsilon, diff);
    if(diff <= epsilon) return true;

    return false;
}
