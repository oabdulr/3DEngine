#pragma once
#include <pch.h>


class draw_data {
public:
    color4 col;
    float x, y;

    draw_data() {}
    draw_data(float x, float y, color4 col) : col(col), x(x), y(y) {}
};