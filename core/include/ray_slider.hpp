#ifndef RAY_SLIDER_HPP
#define RAY_SLIDER_HPP

#include "ray_progress_bar.hpp"

class RaySlider : public RayProgressBar
{
protected:
    virtual void init() override;
    virtual void preUpdate() override;

public:
    std::function<void(double)> onSlide;
    std::function<void(double)> onSlideEnd;

    virtual RaySlider* clone() const override;
};

#endif