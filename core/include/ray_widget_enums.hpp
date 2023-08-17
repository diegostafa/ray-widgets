#ifndef RAY_WIDGET_ENUMS_HPP
#define RAY_WIDGET_ENUMS_HPP

enum class VerticalAlignment
{
    MIDDLE,
    TOP,
    BOTTOM,
};

enum class SpacingMode
{
    SPACE_EVENLY,
    SPACE_BETWEEN
};

enum class TextureMode
{
    NINE_SLICE,
    STRETCH
};

enum class DisplayMode
{
    VISIBLE,
    NONE,
    HIDDEN,
};

enum class WeightOrientation
{
    HORIZONTAL,
    VERTICAL,
};

enum class HorizontalAlignment
{
    CENTER,
    LEFT,
    RIGHT,
};

enum class ScrollDirection
{
    NONE,
    VERTICAL,
    HORIZONTAL,
};

enum class FlexDirection
{
    ROW,
    COL,
};

#endif