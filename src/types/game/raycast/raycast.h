#include <pch.h>

class raycast{
public:
    vec3 position;
    vec3 direction;
    float distance;

    raycast(vec3 position, float distance) : position(position), distance(distance) 
    {
        this->direction = position.normalize();
    }

    raycast(vec3 position, vec3 to, float distance) : position(position), distance(distance) 
    {
        this->direction = (to - position).normalize();
    }

private:
};