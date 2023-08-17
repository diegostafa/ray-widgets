#ifndef INPUT_SCANNER_HPP
#define INPUT_SCANNER_HPP

#include <cmath>
#include <functional>
#include <raylib.h>

class InputScanner
{
private:
    Rectangle surface    = {};
    Vector2   currPos    = {};
    Vector2   lastPos    = {};
    int       clicks     = 0;
    bool      isDragging = false;
    bool      prevPress  = false;

    bool isMouseHovering() const;
    bool isMouseEntering() const;
    bool isMouseLeaving() const;

public:
    std::function<void(Vector2 pos)>      onMouseHover;
    std::function<void(Vector2 pos)>      onMousePress;
    std::function<void()>                 onMouseClick;
    std::function<void()>                 onMouseEnter;
    std::function<void()>                 onMouseLeave;
    std::function<void(float direction)>  onMouseScrollV;
    std::function<void(float direction)>  onMouseScrollH;
    std::function<void(Vector2 startPos)> onMouseDragStart;
    std::function<void(Vector2 pos)>      onMouseDrag;
    std::function<void(Vector2 endPos)>   onMouseDragEnd;

    void detachAllEvents();
    void scan(Rectangle area);
};

#endif