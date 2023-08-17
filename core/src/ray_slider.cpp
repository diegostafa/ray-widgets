#include "../include/ray_slider.hpp"
#include "../../utils/ray_widget_utils.hpp"
#include <cmath>
#include <iostream>

void
RaySlider::init()
{
    RayProgressBar::init();

    input.onMouseDrag = [this](Vector2 pos)
    {
        double progress       = (pos.x - surface.x) / surface.width;
        double unsteppedValue = progress * barState.maxValue;
        int    numSteps       = std::round(unsteppedValue / barState.step);
        double val            = numSteps * barState.step;
        barState.value        = std::clamp(val, barState.minValue, barState.maxValue);

        if (onSlide)
            onSlide(barState.value);
    };

    input.onMouseDragEnd = [this](Vector2 pos)
    {
        if (onSlideEnd)
            onSlideEnd(barState.value);
    };
}

void
RaySlider::preUpdate()
{
    RayWidget::preUpdate();
    input.scan(surface);
}

RaySlider*
RaySlider::clone() const
{
    return new RaySlider(*this);
}