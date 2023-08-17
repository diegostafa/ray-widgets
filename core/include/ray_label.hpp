#ifndef RAY_LABEL_HPP
#define RAY_LABEL_HPP

#include "ray_widget.hpp"
#include <raylib.h>
#include <string>
#include <vector>

struct RayLabelState
{
    Color textColor = BLACK;
    int   fontSize  = 20;

    void applyTo(const std::vector<RayLabel*>& widgets) const;
    void propagateFrom(RayWidget* widget) const;
};

class RayLabel : public RayWidget
{
private:
    MultiLineText mlt;

protected:
    virtual Rectangle getRelativeSurface(const Rectangle& targetSurface);
    virtual void      preDraw() override;

public:
    std::string   text;
    RayLabelState labelState = {};

    RayLabel() = default;
    RayLabel(const std::string& text);

    virtual RayLabel* clone() const override;
};

#endif