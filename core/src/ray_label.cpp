#include "../include/ray_label.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <istream>
#include <raylib.h>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

void
RayLabelState::applyTo(const std::vector<RayLabel*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->labelState = *this;
}

void
RayLabelState::propagateFrom(RayWidget* widget) const
{
    if (widget == nullptr)
        return;

    auto der = dynamic_cast<RayLabel*>(widget);

    if (der)
        der->labelState = *this;

    for (auto&& child : widget->getChildren())
        propagateFrom(child);
}

RayLabel::RayLabel(const std::string& text)
    : text(text) {}

Rectangle
RayLabel::getRelativeSurface(const Rectangle& targetSurface)
{
    mlt = getMultiLineText(text, labelState.fontSize, targetSurface);
    return {targetSurface.x, targetSurface.y, mlt.width, mlt.height};
}

void
RayLabel::preDraw()
{
    RayWidget::preDraw();

    painter
        .on(surface)
        .drawText(mlt, labelState.textColor);
}

RayLabel*
RayLabel::clone() const
{
    return new RayLabel(*this);
}
