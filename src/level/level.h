#pragma once

#include <OpenGL/gl3.h>
#include "../utils/glm.h"
#include "../graphics/vertexarray.h"
#include "../graphics/shader.h"
#include "block.h"

class Level {
private:
    VertexArray *floor;
    Block *block;
    glm::mat4 floor_pos, floor_rot;
public:
    Level();
    void update();
    void render();
};
