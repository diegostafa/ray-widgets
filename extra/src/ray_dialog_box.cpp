#include "../include/ray_dialog_box.hpp"
#include "../../core/ray_core_widgets.hpp"
#include "../../extra/include/ray_text_button.hpp"
#include <functional>
#include <iostream>

RayDialogBox::RayDialogBox()
{
    child =
        dialogBoxState.dialogUi->add({
            dialogBoxState.dialogInfo->add({dialogBoxState.dialogTitle}),
            dialogBoxState.dialogContent->add({dialogBoxState.dialogText}),
        });
}

bool
RayDialogBox::isOver()
{
    return dialogIndex >= dialogBoxState.script.size();
}

void
RayDialogBox::restart()
{
    dialogIndex = -1;
    updateDialog();
}

void
RayDialogBox::updateDialog()
{
    dialogIndex++;

    auto& state = dialogBoxState;

    if (dialogIndex == 0 && onDialogStart)
        onDialogStart();

    if (isOver())
    {
        if (onDialogEnd)
            onDialogEnd();
        return;
    }

    state.dialogTitle->text = state.script[dialogIndex].first;
    state.dialogText->text  = state.script[dialogIndex].second;
}

void
RayDialogBox::init()
{
    RayBox::init();

    input.onMouseClick = [this]()
    { updateDialog(); };
}

void
RayDialogBox::preUpdate()
{
    RayBox::preUpdate();
    input.scan(surface);
}

void
RayDialogBox::preDraw()
{
    RayBox::preDraw();
    child->setSurface(surface);
    child->run();
}

RayDialogBox*
RayDialogBox::clone() const
{
    return new RayDialogBox(*this);
}