#ifndef RAY_LAYOUT_HPP_
#define RAY_LAYOUT_HPP_

#include "ray_box.hpp"
#include "ray_widget.hpp"
#include <raylib.h>
#include <vector>

struct RayLayoutState
{
    float             spacing           = 0;
    SpacingMode       spacingMode       = SpacingMode::SPACE_BETWEEN;
    WeightOrientation weightOrientation = WeightOrientation::HORIZONTAL;
    Spacing           padding           = {0, 0, 0, 0};

    void applyTo(const std::vector<RayLayout*>& widgets) const;
    void propagateFrom(RayWidget* widget) const;
};

class RayLayout : public RayWidget
{
private:
    void cleanup();

protected:
    std::vector<RayWidget*>  children    = {};
    std::function<void(int)> onItemClick = nullptr;

    virtual void setLayout() = 0;
    virtual void preUpdate() override;

public:
    RayLayoutState layoutState{};

    RayLayout() = default;
    RayLayout(const RayLayout& other);
    RayLayout& operator=(const RayLayout& other);
    virtual ~RayLayout();

    virtual void                    propagateAlpha(float alpha) override;
    virtual std::vector<RayWidget*> getChildren() override;
    virtual RayLayout*              add(const std::vector<RayWidget*>& otherChildren);
};

#endif