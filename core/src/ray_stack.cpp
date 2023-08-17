#include "../include/ray_stack.hpp"
#include <iostream>

std::vector<RayWidget*>
RayStack::getRenderChildren()
{
    return {children[childrenFocus]};
}

void
RayStack::giveFocus(int index)
{
    childrenFocus = index;
}

void
RayStack::giveFocus(const RayWidget* widget)
{
    if (children[childrenFocus] == widget)
        return;

    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == widget)
        {
            childrenFocus = i;
            break;
        }
    }
}

void
RayStack::setLayout()
{
    auto child = children[childrenFocus];

    if (!child)
        return;

    auto pad = layoutState.padding;

    Rectangle paddedSurface = {
        surface.x + pad.left,
        surface.y + pad.top,
        surface.width - (pad.left + pad.right),
        surface.height - (pad.top + pad.bottom)};

    child->setSurface(child->placeWidget(paddedSurface));
}

RayStack*
RayStack::clone() const
{
    return new RayStack(*this);
}