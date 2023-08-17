#include "../include/ray_layout.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

void
RayLayoutState::applyTo(const std::vector<RayLayout*>& widgets) const
{
    for (auto&& widget : widgets)
        widget->layoutState = *this;
}

void
RayLayoutState::propagateFrom(RayWidget* widget) const
{
    if (widget == nullptr)
        return;

    auto der = dynamic_cast<RayLayout*>(widget);

    if (der)
        der->layoutState = *this;

    for (auto&& child : widget->getChildren())
        propagateFrom(child);
}

RayLayout::RayLayout(const RayLayout& other)
{
    for (auto&& child : children)
        if (child)
            delete child;

    std::vector<RayWidget*> tmp;

    for (auto&& child : other.children)
        tmp.push_back(child->clone());

    children = tmp;
}

void
RayLayout::cleanup()
{
    for (auto&& child : children)
        if (child)
            delete child;

    children.clear();
}

RayLayout::~RayLayout()
{
    cleanup();
}

RayLayout&
RayLayout::operator=(const RayLayout& other)
{
    if (this != &other)
    {
        cleanup();

        for (auto&& child : other.children)
            children.push_back(child->clone());
    }

    return *this;
}

RayLayout*
RayLayout::add(const std::vector<RayWidget*>& otherChildren)
{
    cleanup();
    children = otherChildren;
    return this;
}

void
RayLayout::preUpdate()
{
    if (children.empty())
        return;

    RayWidget::preUpdate();
    setLayout();
}

std::vector<RayWidget*>
RayLayout::getChildren()
{
    return children;
}

void
RayLayout::propagateAlpha(float alpha)
{
    painter.setAlpha(alpha);

    for (auto&& child : children)
    {
        if (child == nullptr)
            continue;

        child->propagateAlpha(alpha);
    }
}