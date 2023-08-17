#ifndef RAY_PROGRESS_BAR_HPP
#define RAY_PROGRESS_BAR_HPP

#include "ray_widget.hpp"
#include <functional>
#include <iostream>

struct RayProgressBarState
{
    double      minValue     = 0;
    double      maxValue     = 10;
    double      value        = 0;
    double      step         = 1;
    Color       emptyColor   = GRAY;
    Color       fillColor    = RED;
    FullTexture fillTex      = {};
    FullTexture emptyTex     = {};
    FullTexture coverTex     = {};
    FullTexture indicatorTex = {};
    bool        showValue    = true;
    Color       valueColor   = BLACK;
};

class RayProgressBar : public RayWidget
{
protected:
    virtual void init() override;
    virtual void preDraw() override;

public:
    RayProgressBarState     barState = {};
    virtual RayProgressBar* clone() const override;
};

#endif