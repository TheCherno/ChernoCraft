#pragma once

#include "entity.h"
#include "../input.h"

class Player : public Entity {
private:
    glm::vec3 rotation;
    float mouse_sensitivity = 0.2f;
public:
    Player(glm::vec3 spawn);
    void update();
    void render();
};