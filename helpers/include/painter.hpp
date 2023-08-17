#ifndef PAINTER_HPP
#define PAINTER_HPP

#include "../../utils/ray_widget_utils.hpp"

#include <raylib.h>

struct Border;

class Painter
{
private:
    float alpha = 1.0f;

public:
    Rectangle surface;

    void  setAlpha(float a);
    Color applyFade(const Color& c) const;

    const Painter& on(Rectangle rec);
    const Painter& drawColor(Color color, float roundness) const;
    const Painter& drawBorders(Border border) const;
    const Painter& drawTexture(const FullTexture& tex) const;
    const Painter& drawText(const MultiLineText& text, Color color) const;
};

#endif