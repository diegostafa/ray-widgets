#include "../include/ray_text_button.hpp"
#include "../../core/include/ray_label.hpp"
#include <iostream>

RayTextButton::RayTextButton(const std::string& text)
{
    textButtonState.label->text = text;

    child = textButtonState.label;
}

RayTextButton*
RayTextButton::clone() const
{
    return new RayTextButton(*this);
}