#ifndef RAY_COL_HPP
#define RAY_COL_HPP

#include "ray_flex.hpp"
#include "ray_widget.hpp"
#include <raylib.h>
#include <vector>

class RayCol : public RayFlex
{
protected:
    virtual float& mainAxis(Rectangle& rec) const override;
    virtual float& crossAxis(Rectangle& rec) const override;
    virtual float& mainAxisSize(Rectangle& rec) const override;
    virtual float& crossAxisSize(Rectangle& rec) const override;

    virtual float getMainPaddingSpace() const override;
    virtual float getMainMouseDeltaAxis() const override;
    virtual void  setScrollHandler(std::function<void(float)> scrollHandler) override;

public:
    virtual RayCol* clone() const override;
};

#endif