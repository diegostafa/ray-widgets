#include "../core/ray_core_widgets.hpp"
#include "../extra/ray_extra_widgets.hpp"

#include <raylib.h>

int
main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 700, "ray-widgets example");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    RayWidget* ui      = nullptr;
    auto       mainCol = new RayCol;
    auto       slider  = new RaySlider;
    auto       button  = new RayTextButton("Click Meeeeeeeeeeeeeeeee");

    ui = mainCol->add({
        slider,
        button,
    });

    RayWidgetState{
        .border = {GRAY, 1}}
        .applyTo({slider, button});

    mainCol->widgetState.bbox            = {0, 0, 0.5, 0.5};
    mainCol->widgetState.backgroundColor = {20, 20, 20, 100};
    mainCol->layoutState.padding         = {20, 20, 20, 20};
    mainCol->layoutState.spacing         = 10;

    slider->widgetState.bbox  = {0, 0, 0.8, 0.5};
    slider->barState.minValue = 0.0f;
    slider->barState.maxValue = 1.0f;
    slider->barState.step     = 0.02f;
    slider->barState.value    = 0.5f;
    slider->onSlide           = [button](double slideValue)
    { button->widgetState.bbox.width = slideValue; };

    button->widgetState.bbox            = {0, 0, 0.8, 0.5};
    button->widgetState.backgroundColor = WHITE;
    button->buttonEvents.onClick        = [mainCol]()
    {
        mainCol->widgetState.backgroundColor = {
            (unsigned char)(rand() % 255),
            (unsigned char)(rand() % 255),
            (unsigned char)(rand() % 255),
            (unsigned char)(rand() % 255),
        };
    };

    while (!WindowShouldClose())
    {
        auto sw = (float)GetScreenWidth();
        auto sh = (float)GetScreenHeight();

        BeginDrawing();
        ClearBackground(WHITE);

        ui->setSurface({0, 0, sw, sh});
        ui->run();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}