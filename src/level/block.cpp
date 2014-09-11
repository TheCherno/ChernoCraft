#include "block.h"
#include <time.h>

Block::Block(unsigned int ID) {
    this->ID = ID;
    const float SIZE = 16.0f;
    GLfloat vertices[8 * 3] = {
        -SIZE, -SIZE,  SIZE,
         SIZE, -SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE, -SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE
    };
    
    GLuint indices [6 * 6] = {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 1, 5, 5, 4, 0,
        1, 5, 6, 6, 2, 1
    };
    srand(time(NULL));
    vao = new VertexArray(vertices, indices, 8 * 3, 6 * 6);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    color = glm::vec3(r, g, b);
    shader = Shader::BLOCK;
}

void Block::update() {
}

void Block::render(glm::vec3 position) {
    shader->enable();
    glm::mat4 pos = glm::translate(glm::mat4(1.0f), position);
    shader->set_uniform_matrix("ml_matrix", pos);
    shader->set_uniform_float3("block_color", color);
    vao->render();
    shader->disable();
}
