#include "../include/ray_box.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

void
RayBox::cleanup()
{
    if (child)
        delete child;
}

RayBox::RayBox(const RayBox& other)
{
    cleanup();
    child = other.child->clone();
}

RayBox::~RayBox()
{
    cleanup();
}

RayBox&
RayBox::operator=(const RayBox& other)
{
    if (this != &other)
    {
        cleanup();
        child = other.child->clone();
    }

    return *this;
}

void
RayBox::preUpdate()
{
    RayWidget::preUpdate();

    if (child == nullptr)
        return;

    child->setSurface(child->placeWidget(surface));
}

RayBox*
RayBox::clone() const
{
    return new RayBox(*this);
}

RayBox*
RayBox::add(RayWidget* otherChild)
{
    cleanup();
    child = otherChild;
    return this;
}

std::vector<RayWidget*>
RayBox::getChildren()
{
    return {child};
}

void
RayBox::propagateAlpha(float alpha)
{
    if (child == nullptr)
        return;

    painter.setAlpha(alpha);
    child->propagateAlpha(alpha);
}
