#pragma once

#include <cmath>

class vec3 {
public:
    float x, y, z;

    vec3() : x(0), y(0), z(0) { }
    vec3(float x, float y, float z) : x(x), y(y), z(z) { }
    vec3(int x, int y, int z) : x(x), y(y), z(z) { }

    bool is_zero() { return this->x == 0 && this->y == 0 && this-> z == 0; }

    operator bool() {
        return !this->is_zero();
    }
    
    vec3 operator+(const vec3 &r) const {
        return vec3(this->x + r.x, this->y + r.y, this->z + r.z);
    }

    vec3& operator+=(const vec3& r) {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
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

    vec3 operator*(float &r) const {
        return vec3(this->x * r, this->y * r, this->z * r);
    }

    vec3 operator*(const float &r) const {
        return vec3(this->x * r, this->y * r, this->z * r);
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

    vec3 cross(const vec3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    std::string to_string(){
        const int SIZE = 10;
        char bufferx[SIZE];
        char buffery[SIZE];
        char bufferz[SIZE];
        std::snprintf(bufferx, SIZE, "%.1f", this->x);
        std::snprintf(buffery, SIZE, "%.1f", this->y);
        std::snprintf(bufferz, SIZE, "%.1f", this->z);

        return "(" + std::string(bufferx) + ", " + std::string(buffery) + ", " + std::string(bufferz) + ")";
    }

};