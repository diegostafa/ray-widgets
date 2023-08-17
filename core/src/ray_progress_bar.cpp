#include "../include/ray_progress_bar.hpp"
#include "../../utils/ray_widget_utils.hpp"
#include <cmath>
#include <iostream>

void
RayProgressBar::init()
{
    RayWidget::init();

    // with the same radius > 0, inner and outer bars render differently
    widgetState.border.radius = 0;
}

void
RayProgressBar::preDraw()
{
    RayWidget::preDraw();

    const auto& bs            = barState;
    double      currWidthVal  = bs.value / bs.maxValue * surface.width;
    Rectangle   filledSurface = {surface.x, surface.y, (float)currWidthVal, surface.height};

    painter
        .on(surface)
        .drawColor(bs.emptyColor, widgetState.border.radius)
        .drawTexture(bs.emptyTex);

    painter
        .on(filledSurface)
        .drawColor(bs.fillColor, widgetState.border.radius)
        .drawTexture(bs.fillTex);

    painter
        .on(surface)
        .drawTexture(bs.coverTex);

    if (bs.showValue)
    {
        auto fontSize    = std::min(surface.width, surface.height) / 2;
        auto prettyValue = bs.value == int(bs.value) ? std::to_string((int)bs.value) : std::to_string(bs.value);
        drawCenteredText(prettyValue, fontSize, bs.valueColor, surface);
    }
}

RayProgressBar*
RayProgressBar::clone() const
{
    return new RayProgressBar(*this);
}