#pragma once

/**
 * Animated Text System for syncing text animations with musical notes
 * Features:
 * - Text expands from center outward (inward-to-outward animation)
 * - Synchronized with musical beat/notes
 * - Intermittent visibility (appears/disappears with music)
 * - Supports color fading
 */

typedef struct
{
    const char* text;
    float centerX;
    float centerY;
    float scaleX;           // base scale
    float scaleY;           // base scale
    float letterSpacing;
    float thickness;
    
    // Animation properties
    float colorR, colorG, colorB;
    
    // For inward-to-outward animation
    float minScale;         // smallest scale (most contracted)
    float maxScale;         // largest scale (most expanded)
    float pulseDuration;    // time for one complete pulse (in/out) in seconds
    
    // For musical sync
    float beatInterval;     // time between beats in seconds
    int isActive;           // whether this text is currently animating
    float startTime;        // when the animation started
} AnimatedTextInfo;

/**
 * Initialize animated text
 * @param text The text to display
 * @param centerX X position
 * @param centerY Y position
 * @param scaleX Base X scale
 * @param scaleY Base Y scale
 * @param minScale Minimum scale for pulse effect
 * @param maxScale Maximum scale for pulse effect
 * @param pulseDuration Duration of one complete pulse cycle
 * @param beatInterval Interval between musical beats (0 = continuous)
 * @param colorR, colorG, colorB Color of the text
 * @return AnimatedTextInfo structure
 */
AnimatedTextInfo AnimatedText_Create(
    const char* text,
    float centerX,
    float centerY,
    float scaleX,
    float scaleY,
    float minScale,
    float maxScale,
    float pulseDuration,
    float beatInterval,
    float colorR,
    float colorG,
    float colorB);

/**
 * Draw animated text at current time
 * @param info Animation info structure
 * @param globalTime Current elapsed time in seconds
 */
void AnimatedText_Draw(AnimatedTextInfo* info, float globalTime);

/**
 * Update animated text parameters
 */
void AnimatedText_SetActive(AnimatedTextInfo* info, int isActive);
void AnimatedText_SetPosition(AnimatedTextInfo* info, float centerX, float centerY);
void AnimatedText_SetColor(AnimatedTextInfo* info, float r, float g, float b);
void AnimatedText_SetPulseTiming(AnimatedTextInfo* info, float pulseDuration, float beatInterval);

/**
 * Get current scale factor based on musical pulse
 * @param info Animation info
 * @param globalTime Current time
 * @param outScale Output scale factor
 * @return 1 if should be drawn, 0 otherwise
 */
int AnimatedText_GetPulseScale(AnimatedTextInfo* info, float globalTime, float* outScale);
