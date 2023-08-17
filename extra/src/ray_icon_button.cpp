#include "../include/ray_icon_button.hpp"
#include "../../core/include/ray_box.hpp"

RayIconButton::RayIconButton(FullTexture tex)
{
    child                      = new RayBox();
    child->widgetState.texture = tex;
    child->widgetState.bbox    = {0, 0, 0.5, 0.5};
}

RayIconButton*
RayIconButton::clone() const
{
    return new RayIconButton(*this);
}