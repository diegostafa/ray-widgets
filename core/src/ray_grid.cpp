#include "../include/ray_grid.hpp"
#include "../../utils/ray_widget_utils.hpp"
#include "../include/ray_box.hpp"

#include <functional>
#include <iostream>
#include <raylib.h>
#include <stdexcept>
#include <string>
#include <vector>

RayGrid::RayGrid(int rows, int cols)
    : rows(rows), cols(cols) {}

void
RayGrid::setLayout()
{
    const auto spacing     = layoutState.spacing;
    const auto spacingMode = layoutState.spacingMode;

    float totSpacingW;
    float totSpacingH;
    float startX;
    float startY;

    switch (spacingMode)
    {
    case SpacingMode::SPACE_EVENLY:
        totSpacingW = cols * spacing + spacing;
        totSpacingH = rows * spacing + spacing;
        startX      = spacing;
        startY      = spacing;
        break;

    case SpacingMode::SPACE_BETWEEN:
        totSpacingW = cols * spacing - spacing;
        totSpacingH = rows * spacing - spacing;
        startX      = 0;
        startY      = 0;
        break;
    }

    auto itemWidth  = (surface.width - totSpacingW) / cols;
    auto itemHeight = (surface.height - totSpacingH) / rows;

    auto totWeightsByRow = std::vector<float>();
    for (int i = 0; i < rows; i++)
    {
        auto totByRow = 0.0f;

        for (int j = 0; j < cols; j++)
        {
            auto childIndex = i * cols + j;
            if (children[childIndex] == nullptr || childIndex >= children.size())
                continue;

            totByRow += children[childIndex]->widgetState.weight;
        }

        totWeightsByRow.push_back(totByRow);
    }

    auto itemWidths = std::vector<float>();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            auto childIndex = i * cols + j;
            if (children[childIndex] == nullptr || childIndex >= children.size())
                continue;

            auto relWeight = children[childIndex]->widgetState.weight / totWeightsByRow[i];
            itemWidths.push_back((surface.width - totSpacingW) * relWeight);
        }
    }

    auto offsetY = startY;
    for (int i = 0; i < rows; i++)
    {
        auto offsetX = startX;
        offsetY      = startY + (spacing + itemHeight) * i;

        for (int j = 0; j < cols; j++)
        {
            auto childIndex = i * cols + j;

            if (childIndex >= children.size() || children[childIndex] == nullptr)
                continue;

            Rectangle itemSurface =
                {surface.x + offsetX,
                 surface.y + offsetY,
                 itemWidths[childIndex],
                 itemHeight};

            children[childIndex]->setSurface(children[childIndex]->placeWidget(itemSurface));
            offsetX += itemWidths[childIndex] + spacing;
        }
    }
}

RayGrid*
RayGrid::clone() const
{
    return new RayGrid(*this);
}
