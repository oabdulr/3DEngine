#include <pch.h>
#include "engine/engine.h"

int main(int argc, char** argv) {
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;

    
    for (int z = -10; z < 10; z++){
        for (int i = 0; i < 100; i++){
            cube* da_cube = new cube();
            if (!pEngine->create_object(std::string("da_cube") + std::to_string(i) + std::to_string(z), da_cube))
                printf("Cube Creation Failed\n");
            da_cube->Bounds.scale *= {8.f, 1.f, 8.f};
            da_cube->Transform.position = {i * (da_cube->Bounds.scale.x * 2.f), -4.f, z * (da_cube->Bounds.scale.z * 2.f)};
        }
    }

    while (pEngine->isRunning) {
        pEngine->events(); // Inputs

        pEngine->pDrawing->set_draw_color(0, 100, 100, 100);  // Sets Background Color
        pEngine->pDrawing->render_clear(); // Clears with draw color
        pEngine->pDrawing->set_draw_color({0, 0, 0}); // Reset to black so we can draw

        pEngine->camera_render();
        pEngine->event_call();

        pEngine->pDrawing->render_preset();
        printf("FPS: %.2f      \r", pEngine->fps);
    }
    
    pEngine->quit();
    pEngine->pDrawing->implode();
    return EXIT_SUCCESS;
}