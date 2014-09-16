#pragma once

#include "../graphics/vertexarray.h"
#include "../graphics/shader.h"
#include "../utils/glm.h"

class Level;

class Entity {
protected:
    VertexArray *model;
    Shader *shader;
    glm::vec3 position;
    Level *level;
public:
    Entity();
    virtual ~Entity();
    void init(Level *level);
    glm::vec3 get_position();
    virtual void update() = 0;
    virtual void render() = 0;
};
