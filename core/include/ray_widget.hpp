#ifndef RAY_WIDGET_HPP
#define RAY_WIDGET_HPP

#include "../../helpers/ray_widget_helpers.hpp"
#include "../forward_declarations.hpp"
#include "ray_widget_enums.hpp"

#include <functional>
#include <raylib.h>
#include <string>
#include <vector>

struct Alignment
{
    HorizontalAlignment h;
    VerticalAlignment   v;
};

struct Border
{
    Color color;
    float size;
    float radius;
};

struct Spacing
{
    float top;
    float right;
    float bottom;
    float left;
};

struct RayWidgetState
{
    bool        isVisible       = true;
    Rectangle   bbox            = {0, 0, -1, -1};
    bool        scaleAsSquare   = false;
    Color       backgroundColor = {0, 0, 0, 0};
    FullTexture texture         = {};
    int         weight          = 1;
    Timer       fadeTimer       = Timer(100);
    Alignment   alignment       = {HorizontalAlignment::CENTER, VerticalAlignment::MIDDLE};
    Border      border          = {BLACK, 0, 0};
    Spacing     margin          = {0, 0, 0, 0};

    void applyTo(const std::vector<RayWidget*>& widgets) const;
    void propagateFrom(RayWidget* widget) const;
};

class RayWidget
{
protected:
    bool         inited = false;
    Painter      painter;
    InputScanner input;
    bool         handleEvents = true;

    Rectangle surface = {0, 0, 0, 0};

    // methods to extend (i.e. the derivate must also call the base)
    virtual void init();
    virtual void preUpdate();
    virtual void postUpdate();
    virtual void preDraw();
    virtual void postDraw();

public:
    RayWidgetState widgetState = {};

    void disableEvents();
    void enableEvents();
    void toggleFade();
    void fadeIn();
    void fadeOut();
    bool isVisible();
    void run();

    // methods to override
    virtual void                    setSurface(const Rectangle& surface);
    virtual Rectangle               getRelativeSurface(const Rectangle& targetSurface);
    virtual Rectangle               placeWidget(const Rectangle& surface);
    virtual void                    propagateAlpha(float alpha);
    virtual std::vector<RayWidget*> getChildren();
    virtual std::vector<RayWidget*> getRenderChildren();
    virtual RayWidget*              clone() const = 0;
    virtual ~RayWidget()                          = default;
};

#endif
