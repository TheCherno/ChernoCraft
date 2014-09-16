#include "block.h"

#include "air_block.h"
#include "dirt_block.h"
#include "stone_block.h"

const float Block::SIZE = 8.0f;
Block* Block::air = (Block*) NULL;
Block* Block::stone = (Block*) NULL;
Block* Block::dirt = (Block*) NULL;
VertexArray* Block::vao = (VertexArray*) NULL;

Block::Block(unsigned short ID) {
    this->ID = ID;
    if (vao == (VertexArray*) NULL) {
        std::cout << "Initializing block...";
        init();
        std::cout << " done." << std::endl;
    }
    srand((unsigned int) time(NULL));
    color = glm::vec3(0.3, 0.6, 0.2);
    shader = Shader::BLOCK;
    std::cout << "Creating block..." << std::endl;
}

void Block::CREATE_ALL() {
    air = new AirBlock(0);
    stone = new StoneBlock(1);
    dirt = new DirtBlock(2);
}

void Block::init() {
    GLfloat vertices[8 * 3] = {
        -SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f,
         SIZE / 2.0f, -SIZE / 2.0f,  SIZE / 2.0f,
         SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f,
        -SIZE / 2.0f,  SIZE / 2.0f,  SIZE / 2.0f,
        -SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f,
         SIZE / 2.0f, -SIZE / 2.0f, -SIZE / 2.0f,
         SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f,
        -SIZE / 2.0f,  SIZE / 2.0f, -SIZE / 2.0f
    };
    
    GLuint indices [6 * 6] = {
        0, 1, 2, 2, 3, 0,
        3, 2, 6, 6, 7, 3,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        0, 5, 1, 5, 0, 4, // Bottom
        1, 5, 6, 6, 2, 1
    };
    vao = new VertexArray(vertices, indices, 8 * 3, 6 * 6);
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
