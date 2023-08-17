#ifndef RAY_STACK_HPP
#define RAY_STACK_HPP

#include "ray_layout.hpp"

class RayStack : public RayLayout
{
protected:
    virtual void setLayout() override;

public:
    int childrenFocus = 0;

    void giveFocus(int index);
    void giveFocus(const RayWidget* widget);

    virtual std::vector<RayWidget*> getRenderChildren() override;

    virtual RayStack* clone() const override;
};

#endif