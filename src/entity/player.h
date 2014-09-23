#pragma once

#include "entity.h"
#include "../input.h"

class Player : public Entity {
private:
    glm::vec3 rotation;
    float mouse_sensitivity = 0.2f;
    float dy = 0.0f;
    const float JUMP_HEIGHT = 1.5f;
    bool jumping = false;
    bool light = true;
    float speed = 0.7f;
    VertexArray *target;
public:
    Player(glm::vec3 spawn);
    void update();
    void render();
};