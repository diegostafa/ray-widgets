#include "../include/ray_row.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

float
RayRow::getMainPaddingSpace() const
{
    return layoutState.padding.left + layoutState.padding.right;
}

float&
RayRow::mainAxis(Rectangle& rec) const
{
    return rec.x;
}

float&
RayRow::crossAxis(Rectangle& rec) const
{
    return rec.y;
}
float&
RayRow::mainAxisSize(Rectangle& rec) const
{
    return rec.width;
}
float&
RayRow::crossAxisSize(Rectangle& rec) const
{
    return rec.height;
}

float
RayRow::getMainMouseDeltaAxis() const
{
    return GetMouseDelta().x;
}
void
RayRow::setScrollHandler(std::function<void(float)> scrollHandler)
{
    input.onMouseScrollH = scrollHandler;
}

RayRow*
RayRow::clone() const
{
    return new RayRow(*this);
}
