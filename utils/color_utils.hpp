#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <raylib.h>
#include <raymath.h>

static Color
LerpColor(Color c1, Color c2, float progress)
{
    return Color{
        (unsigned char)Lerp(c1.r, c2.r, progress),
        (unsigned char)Lerp(c1.g, c2.g, progress),
        (unsigned char)Lerp(c1.b, c2.b, progress),
        (unsigned char)Lerp(c1.a, c2.a, progress),
    };
}

#endif