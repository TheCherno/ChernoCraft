#pragma once

#include <OpenGL/gl3.h>
#include "../utils/glm.h"
#include "../graphics/vertexarray.h"
#include "../graphics/shader.h"

class Level {
private:
    VertexArray *floor;
    Shader *shader;
    glm::mat4 floor_pos, floor_rot;
public:
    Level();
    void update();
    void render();
};
