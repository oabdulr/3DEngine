#include <pch.h>

class transform{
public:
    vec3 position;
    quat rotation;

    vec3 get_forward() const {
        return rotation * vec3(0, 0, 1);
    }

    transform() {}
private:
};