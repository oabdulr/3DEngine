#include <pch.h>
#include "engine/engine.h"

int main(int argc, char** argv) {
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;
    srand(time(0));
    
    for (int z = -5; z < 5; z++){
        for (int i = 0; i < 5; i++){
            cube* da_cube = new cube();
            if (!pEngine->create_object(std::string("da_cube") + std::to_string(i) + std::to_string(z), da_cube))
                printf("Cube Creation Failed\n");
            da_cube->Bounds.scale *= {8.f, 1.f, 8.f};
            da_cube->Transform.position = {i * (da_cube->Bounds.scale.x * 2.f), -4.f, z * (da_cube->Bounds.scale.z * 2.f)};
            da_cube->col = {1 + (rand() % 255), 1 + (rand() % 255), 1 + (rand() % 255)};
        }
    }

    pEngine->get_pCamera()->Transform.position = {0.f, 40.f, -200.f};

    while (pEngine->isRunning) {
        pEngine->measure_ticks(false);
        pEngine->events();

        pEngine->pDrawing->set_draw_color(28, 28, 28, 255);  // Sets Background Color
        pEngine->pDrawing->render_clear(); // Clears with draw color
        pEngine->pDrawing->set_draw_color({0, 0, 0}); // Reset to black so we can draw

        pEngine->camera_render();
        pEngine->event_call();


        pEngine->pDrawing->render_fostring({10.f, 10.f}, std::string("FPS: ") + std::to_string((int)pEngine->fps), {255.f, 255.f, 255.f, 255.f});
        pEngine->pDrawing->render_preset();
        pEngine->measure_ticks(true);
    }
    
    pEngine->quit();
    pEngine->pDrawing->implode();
    return EXIT_SUCCESS;
}