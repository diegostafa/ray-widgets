#ifndef RAY_CHECKBOX_HPP
#define RAY_CHECKBOX_HPP

#include "ray_widget.hpp"
#include <raylib.h>
#include <vector>

struct RayCheckBoxState
{
    bool        isChecked    = false;
    FullTexture checkedTex   = {};
    FullTexture uncheckedTex = {};

    void applyTo(const std::vector<RayCheckBox*>& widgets) const;
};

struct RayCheckBoxEvents
{
    std::function<void(bool)> onCheck;
};

class RayCheckBox : public RayWidget
{
protected:
    virtual void init() override;
    virtual void preUpdate() override;
    virtual void preDraw() override;

public:
    RayCheckBoxState  checkboxState  = {};
    RayCheckBoxEvents checkboxEvents = {};

    RayCheckBox();

    virtual RayCheckBox* clone() const override;
};

#endif