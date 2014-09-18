#pragma once

#include <vector>
#include <OpenGL/gl3.h>

#include "block/block.h"
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
    const int HEIGHT = 16;
    unsigned short NULL_BLOCK = 0;
    glm::vec3 NULL_COORD = glm::vec3(-1.0, -1.0, -1.0);
    glm::vec3 selected_block;
public:
    Level();
    ~Level();
    void add(Entity *entity);
    void update();
    void select_block(glm::vec3 block);
    unsigned short& get_intersecting_block(Entity *entity);
    unsigned short& get_block(glm::vec3 position);
    unsigned short& raycast_block_id(glm::vec3 position, glm::vec3 &rotation);
    glm::vec3 raycast_block(glm::vec3 position, glm::vec3 &rotation);
    void render();
};
