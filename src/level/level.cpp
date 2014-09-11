#include "level.h"

Level::Level() {
    GLfloat vertices [3 * 4] = {
        -100.0f, -100.0f, 0.0f,
         100.0f, -100.0f, 0.0f,
         100.0f,  100.0f, 0.0f,
        -100.0f,  100.0f, 0.0f
    };
    
    GLuint indices [6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    floor = new VertexArray(vertices, indices, 12, 6);
    
    floor_pos = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, -500.0f));
    block = new Block(0);
}

float angle = 0.0f;

void Level::update() {
    angle++;
}

glm::mat4 rot;

void Level::render() {
    Shader::BLOCK->enable();
    block->update();
    rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    rot *= glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
    Shader::BLOCK->set_uniform_matrix("vw_matrix", floor_pos * rot);
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            block->render(glm::vec3(x * 46.0f, y * 46.0f, x * 16.0f + y * 16.0f));
        }
    }
    Shader::BLOCK->disable();
}

