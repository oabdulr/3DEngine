#include <pch.h>
#include "engine/engine.h"

int main(int argc, char** argv) {
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;

    cube da_cube = cube();
    if (!pEngine->create_object("da_cube", &da_cube))
        printf("Cube Creation Failed\n");

    while (pEngine->isRunning) {
        //pEngine->mesure_ticks(false);
        pEngine->events();

        //if (!pEngine->should_limit()){
            //pEngine->mesure_fps(false);

            pEngine->pDrawing->set_draw_color(0, 100, 100, 100);
            pEngine->pDrawing->render_clear();
            pEngine->pDrawing->set_draw_color({0, 0, 0});

            pEngine->camera_render();

            //da_cube.Transform.rotation = da_cube.Transform.rotation * rotate_by_1;
            //da_cube.Transform.rotation *= rotate_by_1_z;
            //da_cube.Bounds.position += vec3(0.5f, 0.5f, 0.f);

            //pEngine->mesure_fps(true);
            //printf("FPS: %.2f      \r", pEngine->fps);
        //}

        pEngine->pDrawing->render_preset();
        //pEngine->mesure_ticks(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    pEngine->quit();
    pEngine->pDrawing->implode();
    return EXIT_SUCCESS;
}