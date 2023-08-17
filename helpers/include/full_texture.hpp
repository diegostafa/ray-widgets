#ifndef FULL_TEXTURE_HPP
#define FULL_TEXTURE_HPP

#include "../../core/include/ray_widget_enums.hpp"
#include <array>
#include <raylib.h>
#include <rlgl.h>

// patched from "raylib.h - NPatchInfo"
typedef struct NPatchInfoWithScaling
{
    Rectangle source     = {};
    int       left       = 0;
    int       top        = 0;
    int       right      = 0;
    int       bottom     = 0;
    float     sliceScale = 1;
    int       layout     = 0;
} NPatchInfoWithScaling;

struct FullTexture
{
    Texture2D             texture    = {};
    Color                 color      = WHITE;
    TextureMode           drawMode   = TextureMode::STRETCH;
    NPatchInfoWithScaling nPatchInfo = {};
};

#endif