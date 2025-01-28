#pragma once
#include <cmath>

class vec4 {
public:
    float x, y, z, w;

    vec4() : x(0), y(0), z(0), w(0) { }
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }

    vec4 operator+(const vec4 &r) const {
        return vec4(this->x + r.x, this->y + r.y, this->z + r.z, this->w + r.w);
    }

    vec4 operator-(const vec4 &r) const {
        return vec4(this->x - r.x, this->y - r.y, this->z - r.z, this->w - r.w);
    }

    vec4 operator-() const {
        return vec4(-this->x, -this->y, -this->z, -this->w);
    }

    vec4 operator/(const vec4 &r) const {
        return vec4(this->x / r.x, this->y / r.y, this->z / r.z, this->w / r.w);
    }

    vec4 operator*(const vec4 &r) const {
        return vec4(this->x * r.x, this->y * r.y, this->z * r.z, this->w * r.w);
    }

    float dot(const vec4 &r) const {
        return this->x * r.x + this->y * r.y + this->z * r.z + this->w * r.w;
    }

    float length() const {
        return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }

    float distance(const vec4 &r) const {
        float dx = this->x - r.x;
        float dy = this->y - r.y;
        float dz = this->z - r.z;
        float dw = this->w - r.w;
        return std::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
    }

    vec4 normalize() const {
        float len = length();
        if (len > 0) {
            return vec4(this->x / len, this->y / len, this->z / len, this->w / len);
        }
        return *this;
    }

    vec4 operator*(const matrix4x4& mat) const {
        return {
            x * mat(0, 0) + y * mat(0, 1) + z * mat(0, 2) + w * mat(0, 3),
            x * mat(1, 0) + y * mat(1, 1) + z * mat(1, 2) + w * mat(1, 3),
            x * mat(2, 0) + y * mat(2, 1) + z * mat(2, 2) + w * mat(2, 3),
            x * mat(3, 0) + y * mat(3, 1) + z * mat(3, 2) + w * mat(3, 3)
        };
    }

    std::string to_string(){
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ", " + std::to_string(this->w) + ")";
    }
};