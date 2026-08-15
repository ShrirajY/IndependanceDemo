#include "../Headers/AnimatedText.h"
#include "../../core/Shriraj/Engine/Headers/Ng_shapes.h"
#include "../../core/Shriraj/Engine/GlyphDS/Ng_glyph_DS.h"
#include <GL/freeglut.h>
#include <math.h>

#define LERP(a, b, t) ((a) + (((b) - (a)) * (t)))

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
    float colorB)
{
    AnimatedTextInfo info;
    info.text = text;
    info.centerX = centerX;
    info.centerY = centerY;
    info.scaleX = scaleX;
    info.scaleY = scaleY;
    info.letterSpacing = 0.045f;
    info.thickness = 0.01f;
    
    info.colorR = colorR;
    info.colorG = colorG;
    info.colorB = colorB;
    
    info.minScale = minScale;
    info.maxScale = maxScale;
    info.pulseDuration = pulseDuration > 0.0f ? pulseDuration : 1.0f;
    info.beatInterval = beatInterval;
    
    info.isActive = 1;
    info.startTime = 0.0f;
    
    return info;
}

static float ClampF(float value, float minValue, float maxValue)
{
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}

/**
 * Calculate scale based on gradual growth (sawtooth wave)
 * Creates smooth inward-to-outward animation from small to large
 */
static float CalculateGrowthScale(float normalizedTime, float minScale, float maxScale)
{
    // Create a smooth linear growth from min to max
    // normalizedTime goes from 0 to 1 for a full cycle
    // Use sawtooth pattern: grows linearly then snaps back to start
    float scale = LERP(minScale, maxScale, normalizedTime);
    return scale;
}

/**
 * Calculate alpha (opacity) for fade in/out effects
 * Phase 1 (0-0.33): fade in (0 to 1)
 * Phase 2 (0.33-0.66): hold (1)
 * Phase 3 (0.66-1.0): fade out (1 to 0)
 */
static float CalculateFadeAlpha(float normalizedTime)
{
    if (normalizedTime < 0.33f)
    {
        // Fade in phase
        return normalizedTime / 0.33f;
    }
    else if (normalizedTime < 0.66f)
    {
        // Hold phase
        return 1.0f;
    }
    else
    {
        // Fade out phase
        return 1.0f - ((normalizedTime - 0.66f) / 0.34f);
    }
}

/**
 * Calculate if text should be visible based on beat
 * Creates intermittent/flickering effect synchronized to beats
 */
static int ShouldDrawBasedOnBeat(float globalTime, float beatInterval)
{
    if (beatInterval <= 0.0f)
        return 1;  // always draw if no beat interval
    
    // Calculate current position in beat cycle
    float beatPhase = fmodf(globalTime, beatInterval * 2.0f);
    
    // Show for first half of beat cycle
    return beatPhase < beatInterval ? 1 : 0;
}

int AnimatedText_GetPulseScale(AnimatedTextInfo* info, float globalTime, float* outScale)
{
    if (!info->isActive)
        return 0;
    
    // Calculate position within pulse cycle
    float timeInCycle = fmodf(globalTime, info->pulseDuration);
    float normalizedTime = timeInCycle / info->pulseDuration;
    
    // Get scale from growth animation (always smooth, no blinking)
    *outScale = CalculateGrowthScale(normalizedTime, info->minScale, info->maxScale);
    
    return 1;
}

void AnimatedText_Draw(AnimatedTextInfo* info, float globalTime)
{
    if (!info->isActive)
        return;
    
    float pulseScale = 1.0f;
    if (!AnimatedText_GetPulseScale(info, globalTime, &pulseScale))
        return;  // Don't draw if beat visibility is off
    
    // Calculate fade alpha
    float timeInCycle = fmodf(globalTime, info->pulseDuration);
    float normalizedTime = timeInCycle / info->pulseDuration;
    float alpha = CalculateFadeAlpha(normalizedTime);
    
    // Calculate final scales including pulse effect
    float finalScaleX = info->scaleX * pulseScale;
    float finalScaleY = info->scaleY * pulseScale;
    float finalLetterSpacing = info->letterSpacing * pulseScale;
    
    // Set color with fade alpha
    glColor3f(info->colorR * alpha, info->colorG * alpha, info->colorB * alpha);
    
    // Split text into lines and draw each separately
    const char* text = info->text;
    const char* lineStart = text;
    float lineHeight = finalScaleY * 2.0f;  // Triple the line spacing
    int lineIndex = 0;
    
    // Count total lines first to center vertically
    int totalLines = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
            totalLines++;
    }
    
    // Start Y position: offset up by half the total height
    float startY = info->centerY + (totalLines - 1) * lineHeight * 0.5f;
    
    for (int i = 0; ; i++)
    {
        if (text[i] == '\n' || text[i] == '\0')
        {
            // Found end of line or end of string
            int lineLength = (int)(text + i - lineStart);
            
            if (lineLength > 0)
            {
                // Calculate text width for this line
                const float characterWidth = (4.0f / 6.0f) * finalScaleX;
                float textWidth = 
                    lineLength * characterWidth +
                    (lineLength - 1) * finalLetterSpacing;
                
                // Center text horizontally
                float startX = info->centerX - textWidth * 0.5f;
                
                // Calculate Y position for this line
                float lineY = startY - (lineIndex * lineHeight);
                
                // Create a temporary buffer for the line
                char lineBuffer[256];
                for (int j = 0; j < lineLength && j < 255; j++)
                {
                    lineBuffer[j] = lineStart[j];
                }
                lineBuffer[lineLength] = '\0';
                
                // Draw this line
                Ng_drawText(
                    lineBuffer,
                    startX,
                    lineY,
                    finalScaleX,
                    finalScaleY,
                    finalLetterSpacing,
                    info->thickness
                );
            }
            
            if (text[i] == '\0')
                break;
            
            // Move to next line
            lineStart = text + i + 1;
            lineIndex++;
        }
    }
}

void AnimatedText_SetActive(AnimatedTextInfo* info, int isActive)
{
    info->isActive = isActive;
}

void AnimatedText_SetPosition(AnimatedTextInfo* info, float centerX, float centerY)
{
    info->centerX = centerX;
    info->centerY = centerY;
}

void AnimatedText_SetColor(AnimatedTextInfo* info, float r, float g, float b)
{
    info->colorR = r;
    info->colorG = g;
    info->colorB = b;
}

void AnimatedText_SetPulseTiming(AnimatedTextInfo* info, float pulseDuration, float beatInterval)
{
    info->pulseDuration = pulseDuration > 0.0f ? pulseDuration : 1.0f;
    info->beatInterval = beatInterval;
}
