#ifndef RAY_BUTTON_HPP
#define RAY_BUTTON_HPP

#include "../../helpers/ray_widget_helpers.hpp"
#include "ray_box.hpp"
#include <raylib.h>
#include <vector>

struct RayButtonEvents
{
    std::function<void()> onClick;

    void applyTo(const std::vector<RayButton*>& widgets) const;
};

struct RayButtonState
{
    Color       inactiveColor = {0, 0, 0, 0};
    Color       hoverColor    = {100, 100, 100, 100};
    Color       splashColor   = {200, 200, 200, 200};
    FullTexture inactiveTex   = {};
    FullTexture hoverTex      = {};
    FullTexture splashTex     = {};
    Timer       timerHover    = Timer(200);
    Timer       timerSplash   = Timer(100);

    void applyTo(const std::vector<RayButton*>& widgets) const;
    void propagateFrom(RayWidget* widget) const;
};

class RayButton : public RayBox
{
private:
    Color fadingHoverColor  = {0, 0, 0, 0};
    Color fadingSplashColor = {0, 0, 0, 0};
    bool  showHover         = false;
    bool  showSplash        = false;

protected:
    virtual void init() override;
    virtual void preUpdate() override;
    virtual void preDraw() override;

public:
    RayButtonState  buttonState  = {};
    RayButtonEvents buttonEvents = {};

    virtual RayButton* clone() const override;
};

#endif