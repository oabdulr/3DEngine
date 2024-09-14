#pragma once

#include <cmath>

class vec3 {
public:
    float x, y, z;

    vec3() : x(0), y(0), z(0) { }
    vec3(float x, float y, float z) : x(x), y(y), z(z) { }

    vec3 operator+(const vec3 &r) const {
        return vec3(this->x + r.x, this->y + r.y, this->z + r.z);
    }

    vec3 operator-(const vec3 &r) const {
        return vec3(this->x - r.x, this->y - r.y, this->z - r.z);
    }

    vec3 operator-() const {
        return vec3(-this->x, -this->y, -this->z);
    }

    vec3 operator/(const vec3 &r) const {
        return vec3(this->x / r.x, this->y / r.y, this->z / r.z);
    }

    vec3 operator*(const vec3 &r) const {
        return vec3(this->x * r.x, this->y * r.y, this->z * r.z);
    }

    float dot(const vec3 &r) const {
        return this->x * r.x + this->y * r.y + this->z * r.z;
    }

    float length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    float distance(const vec3 &r) const {
        float dx = this->x - r.x;
        float dy = this->y - r.y;
        float dz = this->z - r.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    vec3 normalize() const {
        float len = length();
        if (len > 0) {
            return vec3(this->x / len, this->y / len, this->z / len);
        }
        return *this;
    }
};