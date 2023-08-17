#include "../include/ray_col.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

float
RayCol::getMainPaddingSpace() const
{
    return layoutState.padding.top + layoutState.padding.bottom;
}

float&
RayCol::mainAxis(Rectangle& rec) const
{
    return rec.y;
}

float&
RayCol::crossAxis(Rectangle& rec) const
{
    return rec.x;
}
float&
RayCol::mainAxisSize(Rectangle& rec) const
{
    return rec.height;
}
float&
RayCol::crossAxisSize(Rectangle& rec) const
{
    return rec.width;
}

float
RayCol::getMainMouseDeltaAxis() const
{
    return GetMouseDelta().y;
}
void
RayCol::setScrollHandler(std::function<void(float)> scrollHandler)
{
    input.onMouseScrollV = scrollHandler;
}

RayCol*
RayCol::clone() const
{
    return new RayCol(*this);
}
