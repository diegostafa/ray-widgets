#include "../include/ray_widget.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

void
RayWidgetState::applyTo(const std::vector<RayWidget*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->widgetState = *this;
}

void
RayWidgetState::propagateFrom(RayWidget* widget) const
{
    if (widget == nullptr)
        return;

    widget->widgetState = *this;

    for (auto&& child : widget->getChildren())
        propagateFrom(child);
}

void
RayWidget::setSurface(const Rectangle& newSurface)
{
    const auto& mar = widgetState.margin;

    surface =
        {newSurface.x + mar.left,
         newSurface.y + mar.top,
         newSurface.width - (mar.left + mar.right),
         newSurface.height - (mar.top + mar.bottom)};
}

void
RayWidget::disableEvents()
{
    handleEvents = false;
}

void
RayWidget::enableEvents()
{
    handleEvents = true;
}

void
RayWidget::fadeIn()
{
    if (isVisible())
        return;

    toggleFade();
}

bool
RayWidget::isVisible()
{
    return widgetState.isVisible;
}

void
RayWidget::fadeOut()
{
    if (!isVisible())
        return;

    toggleFade();
}

void
RayWidget::toggleFade()
{
    if (widgetState.fadeTimer.hasStarted)
        return;

    widgetState.fadeTimer.reset().start();

    widgetState.fadeTimer.onTick = [this](float progress)
    {
        auto alpha = widgetState.isVisible ? 1 - progress : progress;
        propagateAlpha(alpha);
    };

    widgetState.fadeTimer.onFinish = [this]()
    {
        widgetState.isVisible = !widgetState.isVisible;
        widgetState.fadeTimer.reset();
    };
}

void
RayWidget::preUpdate()
{
    widgetState.fadeTimer.update();
}

void
RayWidget::postUpdate()
{
}

void
RayWidget::preDraw()
{
    painter
        .on(surface)
        .drawColor(widgetState.backgroundColor, widgetState.border.radius)
        .drawTexture(widgetState.texture);
}

void
RayWidget::postDraw()
{
    painter
        .on(surface)
        .drawBorders(widgetState.border);
}

void
RayWidget::run()
{
    if (!inited)
        init();

    if (!isVisible() && !widgetState.fadeTimer.hasStarted)
        return;

    preUpdate();
    preDraw();

    for (auto&& child : getRenderChildren())
        if (child)
            child->run();

    postDraw();
    postUpdate();
}

Rectangle
RayWidget::getRelativeSurface(const Rectangle& targetSurface)
{
    const auto bbox       = widgetState.bbox;
    const auto convertDim = [](float dim, float parentDim)
    {
        if (dim < 0)
            return parentDim;

        if (dim < 1)
            return parentDim * dim;

        return dim;
    };

    auto w = convertDim(bbox.width, targetSurface.width);
    auto h = convertDim(bbox.height, targetSurface.height);

    if (widgetState.scaleAsSquare)
    {
        auto min = std::min(w, h);

        w = min;
        h = min;
    }

    return {targetSurface.x + bbox.x, targetSurface.y + bbox.y, w, h};
}

Rectangle
RayWidget::placeWidget(const Rectangle& surface)
{
    const auto bbox = getRelativeSurface(surface);
    auto       res  = surface;

    if (bbox.width < surface.width)
    {
        res.width = bbox.width;
        switch (widgetState.alignment.h)
        {
        case HorizontalAlignment::LEFT:
            res.x = bbox.x;
            break;
        case HorizontalAlignment::CENTER:
            res.x = bbox.x + (surface.width - bbox.width) / 2;
            break;
        case HorizontalAlignment::RIGHT:
            res.x = bbox.x + surface.width - bbox.width;
            break;
        }
    }

    if (bbox.height < surface.height)
    {
        res.height = bbox.height;
        switch (widgetState.alignment.v)
        {
        case VerticalAlignment::TOP:
            res.y = bbox.y;
            break;
        case VerticalAlignment::MIDDLE:
            res.y = bbox.y + (surface.height - bbox.height) / 2;
            break;
        case VerticalAlignment::BOTTOM:
            res.y = bbox.y + surface.height - bbox.height;
            break;
        }
    }

    return res;
}

void
RayWidget::init()
{
    inited = true;
}

void
RayWidget::propagateAlpha(float alpha)
{
    painter.setAlpha(alpha);
}

std::vector<RayWidget*>
RayWidget::getChildren()
{
    return {};
}

std::vector<RayWidget*>
RayWidget::getRenderChildren()
{
    return getChildren();
}
