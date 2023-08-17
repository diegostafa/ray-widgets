#ifndef RAY_DIALOG_BOX_HPP
#define RAY_DIALOG_BOX_HPP

#include "../../core/ray_core_widgets.hpp"
#include "../../extra/include/ray_text_button.hpp"
#include <functional>
#include <iostream>

struct RayDialogBoxState
{
    std::vector<std::pair<std::string, std::string>> script = {};

    RayCol*   dialogUi      = new RayCol;
    RayRow*   dialogInfo    = new RayRow;
    RayLabel* dialogTitle   = new RayLabel;
    RayCol*   dialogContent = new RayCol;
    RayLabel* dialogText    = new RayLabel;
};

class RayDialogBox : public RayBox
{
private:
    int dialogIndex = -1;

    void updateDialog();

public:
    RayDialogBoxState dialogBoxState = {};

    std::function<void()> onDialogStart = nullptr;
    std::function<void()> onDialogEnd   = nullptr;

    RayDialogBox();

    bool isOver();
    void restart();

    virtual void          init() override;
    virtual void          preUpdate() override;
    virtual void          preDraw() override;
    virtual RayDialogBox* clone() const override;
};

#endif