#ifndef RAY_BOX_HPP
#define RAY_BOX_HPP

#include "ray_widget.hpp"

#include <raylib.h>
#include <vector>

class RayBox : public RayWidget
{
protected:
    RayWidget* child = nullptr;

private:
    void cleanup();

public:
    RayBox() = default;
    RayBox(const RayBox& other);
    virtual ~RayBox();

    RayBox&                         operator=(const RayBox& other);
    RayBox*                         add(RayWidget* otherChild);
    virtual void                    propagateAlpha(float alpha) override;
    virtual std::vector<RayWidget*> getChildren() override;
    virtual void                    preUpdate() override;
    virtual RayBox*                 clone() const override;
};

#endif