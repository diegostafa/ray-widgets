#include "../include/input_scanner.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <raylib.h>

bool
InputScanner::isMouseHovering() const
{
    return CheckCollisionPointRec(currPos, surface);
}

bool
InputScanner::isMouseEntering() const
{
    return !CheckCollisionPointRec(lastPos, surface) &&
           CheckCollisionPointRec(currPos, surface);
}

bool
InputScanner::isMouseLeaving() const
{
    return CheckCollisionPointRec(lastPos, surface) &&
           !CheckCollisionPointRec(currPos, surface);
}

void
InputScanner::detachAllEvents()
{
    onMouseHover     = nullptr;
    onMousePress     = nullptr;
    onMouseClick     = nullptr;
    onMouseEnter     = nullptr;
    onMouseLeave     = nullptr;
    onMouseScrollV   = nullptr;
    onMouseScrollH   = nullptr;
    onMouseDragStart = nullptr;
    onMouseDrag      = nullptr;
    onMouseDragEnd   = nullptr;
}

void
InputScanner::scan(Rectangle area)
{
    surface = area;
    lastPos = currPos;
    currPos = GetMousePosition();

    if (isMouseHovering())
    {
        if (onMouseHover)
            onMouseHover(currPos);

        if (onMouseEnter && isMouseEntering())
            onMouseEnter();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            prevPress = true;

        if (onMousePress && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && prevPress)
            onMousePress(currPos);

        if (onMouseClick && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && prevPress)
            onMouseClick();

        if (onMouseScrollV || onMouseScrollH)
        {
            auto scroll = GetMouseWheelMoveV();

            if (onMouseScrollV && scroll.y != 0.0f)
                onMouseScrollV(scroll.y);

            if (onMouseScrollH && scroll.x != 0.0f)
                onMouseScrollH(scroll.x);
        }

        if ((onMouseDrag || onMouseDragStart || onMouseDragEnd) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            isDragging = true;

            if (onMouseDragStart)
                onMouseDragStart(currPos);
        }
    }
    else
    {
        if (isMouseLeaving())
        {
            prevPress = false;

            if (onMouseLeave)
                onMouseLeave();
        }
    }

    if (isDragging)
    {
        if (onMouseDrag)
            onMouseDrag(currPos);

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            isDragging = false;

            if (onMouseDragEnd)
                onMouseDragEnd(currPos);
        }
    }
}