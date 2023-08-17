#ifndef MULTI_LINE_TEXT_HPP
#define MULTI_LINE_TEXT_HPP

#include <raylib.h>
#include <string>
#include <vector>

struct MultiLineText
{
    std::vector<std::string> lines;
    float                    width;
    float                    height;
    float                    fontSize;
};

#endif