#pragma once

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Math {
public:
    static float to_radians(float degrees) {
        return degrees * M_PI / 180.0f;
    }
};