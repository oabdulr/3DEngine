#pragma once
#include <pch.h>


class quat : public vec4 {
public:
    quat() : vec4(0, 0, 0, 1) {}
    quat(float w, float x, float y, float z) : vec4(x, y, z, w) {}

    void normalize() {
        float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
        if (magnitude > 0.0f) {
            w /= magnitude;
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }

    static quat from_axis_angle(float degrees, const vec3& axis) {
        float radians = degrees * M_PI / 180.0f;
        float halfAngle = radians / 2.0f;
        float sinHalfAngle = std::sin(halfAngle);

        return quat(
            std::cos(halfAngle),
            axis.x * sinHalfAngle,
            axis.y * sinHalfAngle,
            axis.z * sinHalfAngle
        );
    }

    quat operator*(const quat& q) const {
        return quat(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    quat operator*=(const quat& q) {
        this->w = w * q.w - x * q.x - y * q.y - z * q.z;
        this->x = w * q.x + x * q.w + y * q.z - z * q.y;
        this->y = w * q.y - x * q.z + y * q.w + z * q.x;
        this->z = w * q.z + x * q.y - y * q.x + z * q.w;

        this->normalize();
        return *this;
    }

    vec3 operator*(const vec3& v) const {
        quat v_quat(0, v.x, v.y, v.z);
        quat result = (*this) * v_quat * conjugate();
        return vec3(result.x, result.y, result.z);
    }

    quat conjugate() const {
        return quat(w, -x, -y, -z);
    }
};