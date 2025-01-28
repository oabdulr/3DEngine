#include <pch.h>

class transform{
public:
    vec3 position {0.f, 0.f, 0.f};
    vec3 rotation {0.f, 0.f, 0.f};

    vec3 get_forward() const {
        return rotation * vec3(0, 0, 1);
    }

    transform() {}
private:
};