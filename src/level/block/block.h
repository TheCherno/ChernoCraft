#pragma once

#include "../../graphics/vertexarray.h"
#include "../../utils/glm.h"
#include "../../graphics/texture.h"
#include "../../graphics/shader.h"

class Block {
public:
    static Block *air, *dirt, *stone;
    const static float SIZE;
protected:
    unsigned short ID;
    static VertexArray *vao;
    Shader *shader;
    glm::vec3 color;
    Texture *texture;
public:
    Block(unsigned short ID);
    static void CREATE_ALL();
    virtual void update();
    virtual void render(glm::vec3 position);
private:
    void init();
};