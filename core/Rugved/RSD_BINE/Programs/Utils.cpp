#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int g_readyToStart = 1;

SYSTEMTIME engineStartTime;
BOOL timerInitialized = FALSE;

double engineDeltaTime = 0.0;
double g_LastTime = 0.0;

double getElapsedTimeInSeconds()
{
    if (!g_readyToStart) return 0.0;

    SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);

    double currentInSeconds = currentTime.wHour * 3600 +
                              currentTime.wMinute * 60 +
                              currentTime.wSecond +
                              currentTime.wMilliseconds / 1000.0;

    if (!timerInitialized)
    {
        engineStartTime  = currentTime;
        timerInitialized = TRUE;
        g_LastTime       = 0.0;
        engineDeltaTime = 0.0;
        return 0.0;
    }

    double startInSeconds = engineStartTime.wHour * 3600 +
                            engineStartTime.wMinute * 60 +
                            engineStartTime.wSecond +
                            engineStartTime.wMilliseconds / 1000.0;

    double elapsed = currentInSeconds - startInSeconds;

    engineDeltaTime = elapsed - g_LastTime;
    g_LastTime          = elapsed;

    return elapsed;
}