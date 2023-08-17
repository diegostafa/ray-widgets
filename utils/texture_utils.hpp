#ifndef TEXTURE_UTILS_HPP
#define TEXTURE_UTILS_HPP
#include <raylib.h>

static Rectangle
getTexRec(Texture2D tex)
{
    return {0, 0, (float)tex.width, (float)tex.height};
}

static Rectangle
getTexRec(FullTexture tex)
{
    return {0, 0, (float)tex.texture.width, (float)tex.texture.height};
}

// patched from "rtextures.c - DrawTextureNPatch"
static void
DrawTextureNPatchWithScaling(Texture2D texture, NPatchInfoWithScaling nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    if (texture.id < 1)
        return;

    float width  = (float)texture.width;
    float height = (float)texture.height;

    float patchWidth  = ((int)dest.width <= 0) ? 0.0f : dest.width;
    float patchHeight = ((int)dest.height <= 0) ? 0.0f : dest.height;

    if (nPatchInfo.source.width < 0)
        nPatchInfo.source.x -= nPatchInfo.source.width;
    if (nPatchInfo.source.height < 0)
        nPatchInfo.source.y -= nPatchInfo.source.height;
    if (nPatchInfo.layout == NPATCH_THREE_PATCH_HORIZONTAL)
        patchHeight = nPatchInfo.source.height;
    if (nPatchInfo.layout == NPATCH_THREE_PATCH_VERTICAL)
        patchWidth = nPatchInfo.source.width;

    bool  drawCenter   = true;
    bool  drawMiddle   = true;
    float leftBorder   = (float)nPatchInfo.left;
    float topBorder    = (float)nPatchInfo.top;
    float rightBorder  = (float)nPatchInfo.right;
    float bottomBorder = (float)nPatchInfo.bottom;

    // Adjust the lateral (left and right) border widths in case patchWidth < texture.width
    if (patchWidth <= (leftBorder + rightBorder) && nPatchInfo.layout != NPATCH_THREE_PATCH_VERTICAL)
    {
        drawCenter  = false;
        leftBorder  = (leftBorder / (leftBorder + rightBorder)) * patchWidth;
        rightBorder = patchWidth - leftBorder;
    }

    // Adjust the lateral (top and bottom) border heights in case patchHeight < texture.height
    if (patchHeight <= (topBorder + bottomBorder) && nPatchInfo.layout != NPATCH_THREE_PATCH_HORIZONTAL)
    {
        drawMiddle   = false;
        topBorder    = (topBorder / (topBorder + bottomBorder)) * patchHeight;
        bottomBorder = patchHeight - topBorder;
    }

    Vector2 vertA, vertB, vertC, vertD;
    vertA.x = 0.0f;                                               // outer left
    vertA.y = 0.0f;                                               // outer top
    vertB.x = nPatchInfo.sliceScale * leftBorder;                 // inner left
    vertB.y = nPatchInfo.sliceScale * topBorder;                  // inner top
    vertC.x = patchWidth - rightBorder * nPatchInfo.sliceScale;   // inner right
    vertC.y = patchHeight - bottomBorder * nPatchInfo.sliceScale; // inner bottom
    vertD.x = patchWidth;                                         // outer right
    vertD.y = patchHeight;                                        // outer bottom

    Vector2 coordA, coordB, coordC, coordD;
    coordA.x = nPatchInfo.source.x / width;
    coordA.y = nPatchInfo.source.y / height;
    coordB.x = (nPatchInfo.source.x + leftBorder) / width;
    coordB.y = (nPatchInfo.source.y + topBorder) / height;
    coordC.x = (nPatchInfo.source.x + nPatchInfo.source.width - rightBorder) / width;
    coordC.y = (nPatchInfo.source.y + nPatchInfo.source.height - bottomBorder) / height;
    coordD.x = (nPatchInfo.source.x + nPatchInfo.source.width) / width;
    coordD.y = (nPatchInfo.source.y + nPatchInfo.source.height) / height;

    rlSetTexture(texture.id);

    rlPushMatrix();
    rlTranslatef(dest.x, dest.y, 0.0f);
    rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
    rlTranslatef(-origin.x, -origin.y, 0.0f);

    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    rlNormal3f(0.0f, 0.0f, 1.0f); // Normal vector pointing towards viewer

    if (nPatchInfo.layout == NPATCH_NINE_PATCH)
    {
        // ------------------------------------------------------------
        // TOP-LEFT QUAD
        rlTexCoord2f(coordA.x, coordB.y);
        rlVertex2f(vertA.x, vertB.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordB.x, coordB.y);
        rlVertex2f(vertB.x, vertB.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordB.x, coordA.y);
        rlVertex2f(vertB.x, vertA.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordA.x, coordA.y);
        rlVertex2f(vertA.x, vertA.y); // Top-left corner for texture and quad
        if (drawCenter)
        {
            // TOP-CENTER QUAD
            rlTexCoord2f(coordB.x, coordB.y);
            rlVertex2f(vertB.x, vertB.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordC.x, coordB.y);
            rlVertex2f(vertC.x, vertB.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordC.x, coordA.y);
            rlVertex2f(vertC.x, vertA.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordB.x, coordA.y);
            rlVertex2f(vertB.x, vertA.y); // Top-left corner for texture and quad
        }
        // TOP-RIGHT QUAD
        rlTexCoord2f(coordC.x, coordB.y);
        rlVertex2f(vertC.x, vertB.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordD.x, coordB.y);
        rlVertex2f(vertD.x, vertB.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordD.x, coordA.y);
        rlVertex2f(vertD.x, vertA.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordC.x, coordA.y);
        rlVertex2f(vertC.x, vertA.y); // Top-left corner for texture and quad
        if (drawMiddle)
        {
            // ------------------------------------------------------------
            // MIDDLE-LEFT QUAD
            rlTexCoord2f(coordA.x, coordC.y);
            rlVertex2f(vertA.x, vertC.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordB.x, coordC.y);
            rlVertex2f(vertB.x, vertC.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordB.x, coordB.y);
            rlVertex2f(vertB.x, vertB.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordA.x, coordB.y);
            rlVertex2f(vertA.x, vertB.y); // Top-left corner for texture and quad
            if (drawCenter)
            {
                // MIDDLE-CENTER QUAD
                rlTexCoord2f(coordB.x, coordC.y);
                rlVertex2f(vertB.x, vertC.y); // Bottom-left corner for texture and quad
                rlTexCoord2f(coordC.x, coordC.y);
                rlVertex2f(vertC.x, vertC.y); // Bottom-right corner for texture and quad
                rlTexCoord2f(coordC.x, coordB.y);
                rlVertex2f(vertC.x, vertB.y); // Top-right corner for texture and quad
                rlTexCoord2f(coordB.x, coordB.y);
                rlVertex2f(vertB.x, vertB.y); // Top-left corner for texture and quad
            }

            // MIDDLE-RIGHT QUAD
            rlTexCoord2f(coordC.x, coordC.y);
            rlVertex2f(vertC.x, vertC.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordD.x, coordC.y);
            rlVertex2f(vertD.x, vertC.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordD.x, coordB.y);
            rlVertex2f(vertD.x, vertB.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordC.x, coordB.y);
            rlVertex2f(vertC.x, vertB.y); // Top-left corner for texture and quad
        }

        // ------------------------------------------------------------
        // BOTTOM-LEFT QUAD
        rlTexCoord2f(coordA.x, coordD.y);
        rlVertex2f(vertA.x, vertD.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordB.x, coordD.y);
        rlVertex2f(vertB.x, vertD.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordB.x, coordC.y);
        rlVertex2f(vertB.x, vertC.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordA.x, coordC.y);
        rlVertex2f(vertA.x, vertC.y); // Top-left corner for texture and quad
        if (drawCenter)
        {
            // BOTTOM-CENTER QUAD
            rlTexCoord2f(coordB.x, coordD.y);
            rlVertex2f(vertB.x, vertD.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordC.x, coordD.y);
            rlVertex2f(vertC.x, vertD.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordC.x, coordC.y);
            rlVertex2f(vertC.x, vertC.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordB.x, coordC.y);
            rlVertex2f(vertB.x, vertC.y); // Top-left corner for texture and quad
        }

        // BOTTOM-RIGHT QUAD
        rlTexCoord2f(coordC.x, coordD.y);
        rlVertex2f(vertC.x, vertD.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordD.x, coordD.y);
        rlVertex2f(vertD.x, vertD.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordD.x, coordC.y);
        rlVertex2f(vertD.x, vertC.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordC.x, coordC.y);
        rlVertex2f(vertC.x, vertC.y); // Top-left corner for texture and quad
    }
    else if (nPatchInfo.layout == NPATCH_THREE_PATCH_VERTICAL)
    {
        // TOP QUAD
        // -----------------------------------------------------------
        // Texture coords                 Vertices
        rlTexCoord2f(coordA.x, coordB.y);
        rlVertex2f(vertA.x, vertB.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordD.x, coordB.y);
        rlVertex2f(vertD.x, vertB.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordD.x, coordA.y);
        rlVertex2f(vertD.x, vertA.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordA.x, coordA.y);
        rlVertex2f(vertA.x, vertA.y); // Top-left corner for texture and quad
        if (drawCenter)
        {
            // MIDDLE QUAD
            // -----------------------------------------------------------
            // Texture coords                 Vertices
            rlTexCoord2f(coordA.x, coordC.y);
            rlVertex2f(vertA.x, vertC.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordD.x, coordC.y);
            rlVertex2f(vertD.x, vertC.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordD.x, coordB.y);
            rlVertex2f(vertD.x, vertB.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordA.x, coordB.y);
            rlVertex2f(vertA.x, vertB.y); // Top-left corner for texture and quad
        }
        // BOTTOM QUAD
        // -----------------------------------------------------------
        // Texture coords                 Vertices
        rlTexCoord2f(coordA.x, coordD.y);
        rlVertex2f(vertA.x, vertD.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordD.x, coordD.y);
        rlVertex2f(vertD.x, vertD.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordD.x, coordC.y);
        rlVertex2f(vertD.x, vertC.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordA.x, coordC.y);
        rlVertex2f(vertA.x, vertC.y); // Top-left corner for texture and quad
    }
    else if (nPatchInfo.layout == NPATCH_THREE_PATCH_HORIZONTAL)
    {
        // LEFT QUAD
        // -----------------------------------------------------------
        // Texture coords                 Vertices
        rlTexCoord2f(coordA.x, coordD.y);
        rlVertex2f(vertA.x, vertD.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordB.x, coordD.y);
        rlVertex2f(vertB.x, vertD.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordB.x, coordA.y);
        rlVertex2f(vertB.x, vertA.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordA.x, coordA.y);
        rlVertex2f(vertA.x, vertA.y); // Top-left corner for texture and quad
        if (drawCenter)
        {
            // CENTER QUAD
            // -----------------------------------------------------------
            // Texture coords                 Vertices
            rlTexCoord2f(coordB.x, coordD.y);
            rlVertex2f(vertB.x, vertD.y); // Bottom-left corner for texture and quad
            rlTexCoord2f(coordC.x, coordD.y);
            rlVertex2f(vertC.x, vertD.y); // Bottom-right corner for texture and quad
            rlTexCoord2f(coordC.x, coordA.y);
            rlVertex2f(vertC.x, vertA.y); // Top-right corner for texture and quad
            rlTexCoord2f(coordB.x, coordA.y);
            rlVertex2f(vertB.x, vertA.y); // Top-left corner for texture and quad
        }
        // RIGHT QUAD
        // -----------------------------------------------------------
        // Texture coords                 Vertices
        rlTexCoord2f(coordC.x, coordD.y);
        rlVertex2f(vertC.x, vertD.y); // Bottom-left corner for texture and quad
        rlTexCoord2f(coordD.x, coordD.y);
        rlVertex2f(vertD.x, vertD.y); // Bottom-right corner for texture and quad
        rlTexCoord2f(coordD.x, coordA.y);
        rlVertex2f(vertD.x, vertA.y); // Top-right corner for texture and quad
        rlTexCoord2f(coordC.x, coordA.y);
        rlVertex2f(vertC.x, vertA.y); // Top-left corner for texture and quad
    }
    rlEnd();
    rlPopMatrix();

    rlSetTexture(0);
}

#endif