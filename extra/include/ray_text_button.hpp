#ifndef RAY_TEXT_BUTTON_HPP
#define RAY_TEXT_BUTTON_HPP

#include "../../core/include/ray_button.hpp"
#include "../../core/include/ray_label.hpp"

struct RayTextButtonState
{
    RayLabel* label = new RayLabel;
};

class RayTextButton : public RayButton
{
public:
    RayTextButtonState textButtonState = {};

    RayTextButton(const std::string& text);

    virtual RayTextButton* clone() const override;
};

#endif