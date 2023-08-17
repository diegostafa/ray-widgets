#ifndef RAY_FLEX_HPP_
#define RAY_FLEX_HPP_

#include "ray_layout.hpp"
#include "ray_widget.hpp"
#include <raylib.h>
#include <vector>

struct Scrollbar
{
    float       thickness       = 0;
    Color       color           = BLACK;
    Color       indicatorColor  = WHITE;
    FullTexture tex             = {};
    FullTexture indicatorTex    = {};
    Border      border          = {};
    Border      indicatorBorder = {};
};

struct RayFlexState
{
    int       viewableItems = -1;
    bool      isScrollable  = false;
    float     scrollSpeed   = 80;
    Scrollbar scrollbar     = {};

    void applyTo(const std::vector<RayFlex*>& widgets) const;
    void propagateFrom(RayWidget* widget) const;
};

class RayFlex : public RayLayout
{

private:
    InputScanner scrollbarInput       = {};
    Rectangle    sbarIndicatorSurface = {};

    float scrollPosition = 0.0f;
    float scrollEnd      = 0.0f;

    std::vector<float> computeItemSizes(float availableSurface) const;

protected:
    virtual float& mainAxis(Rectangle& rec) const      = 0;
    virtual float& crossAxis(Rectangle& rec) const     = 0;
    virtual float& mainAxisSize(Rectangle& rec) const  = 0;
    virtual float& crossAxisSize(Rectangle& rec) const = 0;

    virtual float getMainPaddingSpace() const                                = 0;
    virtual float getMainMouseDeltaAxis() const                              = 0;
    virtual void  setScrollHandler(std::function<void(float)> scrollHandler) = 0;

    virtual void init() override;
    virtual void preUpdate() override;
    virtual void preDraw() override;
    virtual void postDraw() override;
    virtual void setLayout() override;

public:
    RayFlexState flexState = {};
};

#endif