#ifndef RAY_GRID_HPP
#define RAY_GRID_HPP

#include "ray_layout.hpp"
#include "ray_widget.hpp"
#include <raylib.h>
#include <vector>

class RayGrid : public RayLayout
{
private:
    int rows = 0;
    int cols = 0;

protected:
    virtual void setLayout() override;

public:
    RayGrid(int rows = 0, int cols = 0);

    virtual RayGrid* clone() const override;
};

#endif