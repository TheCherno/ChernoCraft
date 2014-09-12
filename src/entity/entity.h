#pragma once

#include "../graphics/vertexarray.h"
#include "../graphics/shader.h"
#include "../utils/glm.h"

class Entity {
protected:
    VertexArray *model;
    Shader *shader;
    glm::vec3 position;
public:
    Entity();
    virtual ~Entity();
    glm::vec3 get_position();
    virtual void update() = 0;
    virtual void render() = 0;
};
