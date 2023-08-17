#include "../include/ray_checkbox.hpp"
#include "../../utils/ray_widget_utils.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

RayCheckBox::RayCheckBox()
{
    widgetState.border.size = 1;
}

void
RayCheckBox::init()
{
    RayWidget::init();

    input.onMouseClick = [this]()
    {
        checkboxState.isChecked = !checkboxState.isChecked;

        if (checkboxEvents.onCheck)
            checkboxEvents.onCheck(checkboxState.isChecked);
    };
}

void
RayCheckBox::preUpdate()
{
    RayWidget::preUpdate();

    input.scan(surface);
}

void
RayCheckBox::preDraw()
{
    RayWidget::preDraw();

    if (checkboxState.isChecked)
    {
        DrawLineEx(
            {surface.x, surface.y},
            {surface.x + surface.width, surface.y + surface.height},
            2, BLACK);

        DrawLineEx(
            {surface.x + surface.width, surface.y},
            {surface.x, surface.y + surface.height},
            2, BLACK);

        painter.on(surface).drawTexture(checkboxState.uncheckedTex);
    }
    else
    {
        painter.on(surface).drawTexture(checkboxState.checkedTex);
    }
}

RayCheckBox*
RayCheckBox::clone() const
{
    return new RayCheckBox(*this);
}
