#include <pch.h>
#include "engine/engine.h"

int main(int argc, char** argv) {
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;

    
    for (int z = -10; z < 10; z++){
        for (int i = 0; i < 10; i++){
            cube* da_cube = new cube();
            if (!pEngine->create_object(std::string("da_cube") + std::to_string(i) + std::to_string(z), da_cube))
                printf("Cube Creation Failed\n");
            da_cube->Transform.position = {i * (2.f), -4.f, z * (2.f)};
        }
    }

    while (pEngine->isRunning) {
        //pEngine->mesure_ticks(false);
        pEngine->events();

        //if (!pEngine->should_limit()){
            //pEngine->mesure_fps(false);


            pEngine->pDrawing->set_draw_color(0, 100, 100, 100);
            pEngine->pDrawing->render_clear();
            pEngine->pDrawing->set_draw_color({0, 0, 0});

            pEngine->camera_render();
            pEngine->event_call();

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