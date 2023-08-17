#ifndef TEXT_UTILS_HPP
#define TEXT_UTILS_HPP

#include "../helpers/ray_widget_helpers.hpp"

static MultiLineText
getMultiLineText(const std::string& text, float fontSize, const Rectangle& surface)
{
    MultiLineText at;
    std::string   acc;
    int           maxLineWidth = 0;

    for (int i = 0; i < text.size(); i++)
    {
        acc += text[i];
        auto lineWidth = MeasureText(acc.c_str(), fontSize);

        if (lineWidth >= surface.width)
        {
            at.lines.push_back(acc);
            acc.clear();
            maxLineWidth = std::max(maxLineWidth, lineWidth);
        }
    }

    if (!acc.empty())
    {
        at.lines.push_back(acc);
        maxLineWidth = std::max(maxLineWidth, MeasureText(at.lines.back().c_str(), fontSize));
    }

    at.width    = (float)maxLineWidth;
    at.height   = fontSize * at.lines.size();
    at.fontSize = fontSize; // todo : compute fontsize too

    return at;
}

static void
drawCenteredText(const std::string& text, int fontSize, Color color, const Rectangle& surface)
{
    auto ctext = text.c_str();
    auto tw    = MeasureText(ctext, fontSize);

    DrawText(
        ctext,
        surface.x + surface.width / 2 - tw / 2,
        (surface.y + surface.height / 2) - (fontSize / 2),
        fontSize, color);
}

#endif