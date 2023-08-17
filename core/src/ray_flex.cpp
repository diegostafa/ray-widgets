#include "../include/ray_flex.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <raylib.h>
#include <string>
#include <vector>

void
RayFlexState::applyTo(const std::vector<RayFlex*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->flexState = *this;
}

void
RayFlexState::propagateFrom(RayWidget* widget) const
{
    if (widget == nullptr)
        return;

    auto der = dynamic_cast<RayFlex*>(widget);

    if (der)
        der->flexState = *this;

    for (auto&& child : widget->getChildren())
        propagateFrom(child);
}

void
RayFlex::init()
{
    RayLayout::init();

    if (!flexState.isScrollable || flexState.viewableItems < 0 || flexState.viewableItems > children.size())
        flexState.viewableItems = children.size();

    if (flexState.isScrollable)
    {
        auto updateScrollPosition = [this](float direction)
        {
            auto amount            = direction * flexState.scrollSpeed * -1;
            auto newScrollPosition = scrollPosition - amount;
            scrollPosition         = std::clamp(newScrollPosition, mainAxisSize(surface) - scrollEnd, 0.0f);
        };

        setScrollHandler(updateScrollPosition);
    }

    if (flexState.scrollbar.thickness > 0)
    {
        scrollbarInput.onMouseDrag = [this](Vector2 pos)
        {
            auto delta             = getMainMouseDeltaAxis();
            auto newScrollPosition = scrollPosition - delta;
            scrollPosition         = std::clamp(newScrollPosition, mainAxisSize(surface) - scrollEnd, 0.0f);
        };
    }
}

void
RayFlex::preUpdate()
{
    RayLayout::preUpdate();

    if (flexState.isScrollable)
    {
        input.scan(surface);

        if (flexState.scrollbar.thickness > 0)
            scrollbarInput.scan(sbarIndicatorSurface);
    }
}

void
RayFlex::preDraw()
{
    RayLayout::preDraw();

    if (flexState.scrollbar.thickness > 0 && flexState.viewableItems < children.size())
    {
        const auto sbar            = flexState.scrollbar;
        auto       sbarIndicLenght = 2 * mainAxisSize(surface) - scrollEnd;

        auto sbarSurface           = surface;
        crossAxisSize(sbarSurface) = sbar.thickness;

        sbarIndicatorSurface                = surface;
        mainAxisSize(sbarIndicatorSurface)  = sbarIndicLenght;
        crossAxisSize(sbarIndicatorSurface) = sbar.thickness;
        mainAxis(sbarIndicatorSurface)      = mainAxis(sbarIndicatorSurface) - sbar.thickness;

        painter
            .on(sbarSurface)
            .drawColor(sbar.color, 0)
            .drawTexture(sbar.tex)
            .drawBorders(sbar.border);

        painter
            .on(sbarIndicatorSurface)
            .drawColor(sbar.indicatorColor, 0)
            .drawTexture(sbar.indicatorTex)
            .drawBorders(sbar.indicatorBorder);
    }

    BeginScissorMode(surface.x, surface.y, surface.width, surface.height);
}

void
RayFlex::postDraw()
{
    EndScissorMode();
    RayWidget::postDraw();
}

std::vector<float>
RayFlex::computeItemSizes(float availableSurface) const
{
    if (flexState.isScrollable)
        return std::vector<float>(children.size(), availableSurface / flexState.viewableItems);

    auto totWeight = 0.0f;
    auto itemSizes = std::vector<float>();

    for (auto&& child : children)
        if (child)
            totWeight += child->widgetState.weight;

    for (auto&& child : children)
        if (child)
            itemSizes.push_back(availableSurface * (child->widgetState.weight / totWeight));

    return itemSizes;
}

void
RayFlex::setLayout()
{
    const auto pad               = layoutState.padding;
    auto       visibleTotSpacing = 0.0f;
    auto       offset            = 0.0f;
    auto       totSpacing        = 0.0f;

    switch (layoutState.spacingMode)
    {
    case SpacingMode::SPACE_EVENLY:
        totSpacing        = (children.size() + 1) * layoutState.spacing;
        visibleTotSpacing = (flexState.viewableItems + 1) * layoutState.spacing;
        offset            = layoutState.spacing;
        break;

    case SpacingMode::SPACE_BETWEEN:
        totSpacing        = (children.size() - 1) * layoutState.spacing;
        visibleTotSpacing = (flexState.viewableItems - 1) * layoutState.spacing;
        offset            = 0;
        break;
    }

    Rectangle layoutSurface = {
        surface.x + pad.left,
        surface.y + pad.top,
        surface.width - (pad.left + pad.right),
        surface.height - (pad.top + pad.bottom)};

    totSpacing += getMainPaddingSpace();
    crossAxis(layoutSurface)     = crossAxis(layoutSurface) + flexState.scrollbar.thickness;
    crossAxisSize(layoutSurface) = crossAxisSize(layoutSurface) - flexState.scrollbar.thickness;

    auto itemSizes = computeItemSizes(mainAxisSize(layoutSurface) - visibleTotSpacing);

    scrollEnd = children.size() * itemSizes[0] + totSpacing;

    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == nullptr)
            continue;

        auto itemSurface          = layoutSurface;
        mainAxis(itemSurface)     = mainAxis(itemSurface) + scrollPosition + offset;
        mainAxisSize(itemSurface) = itemSizes[i];

        auto pl = children[i]->placeWidget(itemSurface);
        children[i]->setSurface(pl);

        offset += itemSizes[i] + layoutState.spacing;
    }
}
