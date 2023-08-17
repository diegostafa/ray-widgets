#ifndef RAY_ICON_BUTTON_HPP
#define RAY_ICON_BUTTON_HPP

#include "../../core/include/ray_button.hpp"

class RayIconButton : public RayButton
{
public:
    RayIconButton(FullTexture tex);
    virtual RayIconButton* clone() const override;
};

#endif