#pragma once
#include <pch.h>

class matrix4x4{
  public:
    float elements[16] = {0, 0, 0, 0,
                          0, 0, 0, 0,
                          0, 0, 0, 0,
                          0, 0, 0, 0};

    matrix4x4(){
        for (int i = 0; i > 16; i++)
            elements[i] = 0.f;
        
        elements[0] = elements[5] = elements[10] = elements[15] = 1.0f;
    }

    float& operator()(int row, int col) {
        return elements[row * 4 + col];
    }

    const float& operator()(int row, int col) const {
        return elements[row * 4 + col];
    }

    matrix4x4 operator*(const matrix4x4& other) const {
        matrix4x4 result;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                result(row, col) = 
                    (*this)(row, 0) * other(0, col) +
                    (*this)(row, 1) * other(1, col) +
                    (*this)(row, 2) * other(2, col) +
                    (*this)(row, 3) * other(3, col);
            }
        }
        return result;
    }

   static  matrix4x4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
        vec3 f = (center - eye).normalize();
        vec3 s = f.cross(up).normalize();
        vec3 u = s.cross(f);

        matrix4x4 result = matrix4x4();
        result(0, 0) = s.x;
        result(0, 1) = s.y;
        result(0, 2) = s.z;
        result(1, 0) = u.x;
        result(1, 1) = u.y;
        result(1, 2) = u.z;
        result(2, 0) = -f.x;
        result(2, 1) = -f.y;
        result(2, 2) = -f.z;
        result(0, 3) = -s.dot(eye);
        result(1, 3) = -u.dot(eye);
        result(2, 3) = f.dot(eye);
        return result;
    }

    static matrix4x4 perspective(float fov, float aspect, float near, float far) {
        float tanHalfFovy = std::tan(fov / 2.0f);

        matrix4x4 result = {};
        result(0, 0) = 1.0f / (aspect * tanHalfFovy);
        result(1, 1) = 1.0f / tanHalfFovy;
        result(2, 2) = -(far + near) / (far - near);
        result(2, 3) = -(2.0f * far * near) / (far - near);
        result(3, 2) = -1.0f;
        return result;
    }

    static matrix4x4 translate(const vec3& translation) {
        matrix4x4 result = matrix4x4();
        result(0, 3) = translation.x;
        result(1, 3) = translation.y;
        result(2, 3) = translation.z;
        return result;
    }

    static matrix4x4 rotateY(float angle) {
        matrix4x4 result = matrix4x4();
        float cosTheta = std::cos(angle);
        float sinTheta = std::sin(angle);

        result(0, 0) = cosTheta;
        result(0, 2) = sinTheta;
        result(2, 0) = -sinTheta;
        result(2, 2) = cosTheta;
        return result;
    }

    static matrix4x4 scale(const vec3& scaleFactor) {
        matrix4x4 result = matrix4x4();
        result(0, 0) = scaleFactor.x;
        result(1, 1) = scaleFactor.y;
        result(2, 2) = scaleFactor.z;
        return result;
    }
};