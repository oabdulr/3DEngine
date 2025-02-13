#pragma once
#include <pch.h>

class camera : public gameobject {
public:
    camera(rect* pWinSize, drawing* pDrawing) : pWinSize(pWinSize), pDrawing(pDrawing)
    { 
        this->add_keymap("forward", {SDL_SCANCODE_W});
        this->add_keymap("back",    {SDL_SCANCODE_S});
        this->add_keymap("right",   {SDL_SCANCODE_D});
        this->add_keymap("left",    {SDL_SCANCODE_A});

        this->add_keymap("view_left",     {SDL_SCANCODE_LEFT});
        this->add_keymap("view_right",    {SDL_SCANCODE_RIGHT});
        this->add_keymap("view_up",    {SDL_SCANCODE_UP});
        this->add_keymap("view_down",    {SDL_SCANCODE_DOWN});

        this->set_fov(this->fov); 
    }
    
    
    vec2 w2s(vec3 pos, float scale = 1.0f);

    void rotate(float y, float p, bool set = false);
    void update();
    void render(std::unordered_map<std::string, gameobject*> &objs);
    void set_fov(float fov);
    void renderTriangleWithDepth(const vec3& v0, const vec3& v1, const vec3& v2, std::vector<float>& depthBuffer);
    float computeDepth(float x, float y, const vec3& top, const vec3& mid, const vec3& bot);
    void event_input(int event_type, SDL_Event event); // override
private:
    static constexpr float radians = (3.14159265f / 180.0f);

    float fov = 90.f;
    float rad_fov = 0.f;
    float near_plane = 0.1f;
    float far_plane = 1000.f;

    float yaw = 1.5f;
    float pitch = 0.f;

    vec3 looking_direction {};
    vec3 right {};
    vec3 up {};

    matrix4x4 view_matrix {};
    matrix4x4 proj_matrix {};

    rect* pWinSize;
    drawing* pDrawing;

    std::vector<float> tile_min_depth;
    std::vector<float> z_buffer;
    std::vector<draw_data> draw_buffer {};
};

