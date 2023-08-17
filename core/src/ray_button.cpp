#include "../include/ray_button.hpp"
#include "../../helpers/ray_widget_helpers.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

void
RayButtonEvents::applyTo(const std::vector<RayButton*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->buttonEvents = *this;
}

void
RayButtonState::applyTo(const std::vector<RayButton*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->buttonState = *this;
}

void
RayButtonState::propagateFrom(RayWidget* widget) const
{
    if (widget == nullptr)
        return;

    auto der = dynamic_cast<RayButton*>(widget);

    if (der)
        der->buttonState = *this;

    for (auto&& child : widget->getChildren())
        propagateFrom(child);
}

void
RayButton::init()
{
    RayWidget::init();

    buttonState.timerHover.onTick = [this](float progress)
    {
        fadingHoverColor = LerpColor(buttonState.inactiveColor, buttonState.hoverColor, progress);
        showHover        = true;
    };

    buttonState.timerHover.onReset = [this]()
    {
        showHover        = false;
        fadingHoverColor = {0, 0, 0, 0};
    };

    buttonState.timerSplash.onTick = [this](float progress)
    {
        fadingSplashColor = LerpColor(buttonState.hoverColor, buttonState.splashColor, progress);
        showSplash        = true;
    };

    buttonState.timerSplash.onReset = [this]()
    {
        showSplash        = false;
        fadingSplashColor = {0, 0, 0, 0};
    };

    input.onMouseHover = [this](Vector2 pos)
    {
        buttonState.timerHover.start().update();
    };

    input.onMousePress = [this](Vector2 pos)
    {
        buttonState.timerSplash.start().update();
    };

    input.onMouseClick = [this]()
    {
        buttonState.timerSplash.reset();

        if (buttonEvents.onClick)
            buttonEvents.onClick();
    };

    input.onMouseLeave = [this]()
    {
        buttonState.timerHover.reset();
        buttonState.timerSplash.reset();
    };
}

void
RayButton::preUpdate()
{
    RayBox::preUpdate();

    input.scan(surface);
}

void
RayButton::preDraw()
{
    RayBox::preDraw();

    painter
        .on(surface)
        .drawColor(buttonState.inactiveColor, widgetState.border.radius)
        .drawTexture(buttonState.inactiveTex);

    if (showHover)
        painter
            .on(surface)
            .drawColor(fadingHoverColor, widgetState.border.radius)
            .drawTexture(buttonState.hoverTex);

    if (showSplash)
        painter
            .on(surface)
            .drawColor(fadingSplashColor, widgetState.border.radius)
            .drawTexture(buttonState.splashTex);
}

RayButton*
RayButton::clone() const
{
    return new RayButton(*this);
}
