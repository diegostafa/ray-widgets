#include "../include/painter.hpp"
#include "../../core/include/ray_widget.hpp"
#include "../../utils/ray_widget_utils.hpp"
#include <iostream>

Color
Painter::applyFade(const Color& c) const
{
    return {c.r, c.g, c.b, (unsigned char)(c.a * alpha)};
}

void
Painter::setAlpha(float a)
{
    if (a < 0)
        alpha = 0;
    else if (a > 1)
        alpha = 1;
    else
        alpha = a;
}

const Painter&
Painter::on(Rectangle rec)
{
    surface = rec;
    return *this;
}

const Painter&
Painter::drawColor(Color color, float roundness) const
{
    DrawRectangleRounded(surface, roundness, 10, applyFade(color));
    return *this;
}

const Painter&
Painter::drawBorders(Border border) const
{
    DrawRectangleRoundedLines(surface, border.radius, 10, border.size, applyFade(border.color));
    return *this;
}

const Painter&
Painter::drawTexture(const FullTexture& tex) const
{
    switch (tex.drawMode)
    {
    case TextureMode::STRETCH:
        DrawTexturePro(tex.texture, getTexRec(tex), surface, {0, 0}, 0, applyFade(tex.color));
        break;

    case TextureMode::NINE_SLICE:
        DrawTextureNPatchWithScaling(tex.texture, tex.nPatchInfo, surface, {0, 0}, 0, applyFade(tex.color));
        break;
    }

    return *this;
}

const Painter&
Painter::drawText(const MultiLineText& text, Color color) const
{
    for (int i = 0; i < text.lines.size(); i++)
    {
        DrawText(text.lines[i].c_str(), surface.x,
                 surface.y + text.fontSize * i,
                 text.fontSize,
                 applyFade(color));
    }
    return *this;
}