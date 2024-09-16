#pragma once
#include <pch.h>


class quat : public vec4 {
public:
    quat() : vec4(0, 0, 0, 1) {}
    quat(float w, float x, float y, float z) : vec4(x, y, z, w) {}

    void normalize() {
        float magnitude = std::sqrt(w * w + x * x + y * y + z * z);
        w /= magnitude;
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
    }

    vec3 operator*(const vec3& point) const {
        float xx = x * x;
        float yy = y * y;
        float zz = z * z;
        float xy = x * y;
        float xz = x * z;
        float yz = y * z;
        float wx = w * x;
        float wy = w * y;
        float wz = w * z;

        vec3 result;
        result.x = (1.0f - 2.0f * (yy + zz)) * point.x + 2.0f * (xy - wz) * point.y + 2.0f * (xz + wy) * point.z;
        result.y = 2.0f * (xy + wz) * point.x + (1.0f - 2.0f * (xx + zz)) * point.y + 2.0f * (yz - wx) * point.z;
        result.z = 2.0f * (xz - wy) * point.x + 2.0f * (yz + wx) * point.y + (1.0f - 2.0f * (xx + yy)) * point.z;

        return result;
    }

    quat operator*(const quat& q) const {
        return quat(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    quat operator*= (quat& q) {
        w = w * q.w - x * q.x - y * q.y - z * q.z;
        x = w * q.x + x * q.w + y * q.z - z * q.y;
        y = w * q.y - x * q.z + y * q.w + z * q.x;
        z = w * q.z + x * q.y - y * q.x + z * q.w;
        return *this;
    }

    // Inverse of the quaternion
    quat inverse() const {
        float norm = w*w + x*x + y*y + z*z;
        return quat(w / norm, -x / norm, -y / norm, -z / norm);
    }

    // Rotate a vector using this quaternion
    vec3 rotate(const vec3& v) const {
        quat qv(0, v.x, v.y, v.z);
        quat result = (*this) * qv * this->inverse();
        return vec3(result.x, result.y, result.z);
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
};