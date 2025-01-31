#pragma once

#include <cmath>

class vec2 {
public:
    float x, y;

    vec2() : x(0), y(0) { }
    vec2(float x, float y) : x(x), y(y) { }

    vec2 operator+(const vec2 &r) const {
        return vec2(this->x + r.x, this->y + r.y);
    }

    vec2 operator-(const vec2 &r) const {
        return vec2(this->x - r.x, this->y - r.y);
    }

    vec2 operator-() const {
        return vec2(-this->x, -this->y);
    }

    vec2 operator/(const vec2 &r) const {
        return vec2(this->x / r.x, this->y / r.y);
    }

    vec2 operator*(const vec2 &r) const {
        return vec2(this->x * r.x, this->y * r.y);
    }

    float dot(const vec2 &r) const {
        return this->x * r.x + this->y * r.y;
    }

    float length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    float distance(const vec2 &r) const {
        float dx = this->x - r.x;
        float dy = this->y - r.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    vec2 normalize() const {
        float len = length();
        if (len > 0) {
            return vec2(this->x / len, this->y / len);
        }
        return *this;
    }

    std::string to_string(){
        const int SIZE = 10;
        char bufferx[SIZE];
        char buffery[SIZE];
        std::snprintf(bufferx, SIZE, "%.1f", this->x);
        std::snprintf(buffery, SIZE, "%.1f", this->y);

        return "(" + std::string(bufferx) + ", " + std::string(buffery) + ")";
    }
};