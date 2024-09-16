#pragma once
#include <pch.h>

class bound {
public:
    float w, h = 0;
    vec3 position;
    float scale = 10.f;
    
    bound() {}
    bound(float x, float y, float z, float w, float h) : w(w), h(h), position(x, y, z) {}

    bool is_inside( vec3 point )
    {
        // Calculate the minimum and maximum extents of the bounding box
        vec3 minExtent = position + VERTEX[0];
        vec3 maxExtent = position + VERTEX[0];

        for (const auto& vertex : VERTEX) {
            vec3 worldVertex = position + vertex; // Transform vertex to world coordinates
            minExtent.x = std::min(minExtent.x, worldVertex.x);
            minExtent.y = std::min(minExtent.y, worldVertex.y);
            minExtent.z = std::min(minExtent.z, worldVertex.z);
            maxExtent.x = std::max(maxExtent.x, worldVertex.x);
            maxExtent.y = std::max(maxExtent.y, worldVertex.y);
            maxExtent.z = std::max(maxExtent.z, worldVertex.z);
        }

        // Check if the point is inside the bounding box
        return (point.x >= minExtent.x && point.x <= maxExtent.x &&
                point.y >= minExtent.y && point.y <= maxExtent.y &&
                point.z >= minExtent.z && point.z <= maxExtent.z);
    }

    std::vector<vec3> VERTEX {};
    std::vector<std::pair<int, int>> EDGES {};
};