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
    
    floor = new VertexArray(vertices, indices, 6);
    shader = new Shader("shaders/shader.vert", "shaders/shader.frag");
    shader->enable();
    shader->set_uniform_matrix("pr_matrix", glm::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
    shader->set_uniform_matrix("vw_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -500.0f)));
    shader->disable();
    
    floor_pos = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, -5.0f));
}

float angle;

void Level::update() {
    angle++;
}

void Level::render() {
    shader->enable();
    floor_rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
    shader->set_uniform_matrix("ml_matrix", floor_rot * floor_pos);
    floor->render();
    shader->disable();
}

