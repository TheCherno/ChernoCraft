#pragma once

#include <vector>
#include <OpenGL/gl3.h>

#include "block.h"
#include "../graphics/vertexarray.h"
#include "../graphics/shader.h"
#include "../entity/entity.h"
#include "../entity/player.h"
#include "../utils/glm.h"

class Level {
private:
    VertexArray *floor;
    unsigned short ***blocks;
    glm::mat4 floor_pos, floor_rot;
    std::vector<Entity*> entities;
    
    const int WIDTH = 16;
    const int DEPTH = 16;
    const int HEIGHT = 2;
public:
    Level();
    ~Level();
    void add(Entity *entity);
    void update();
    void render();
};
