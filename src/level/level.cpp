#include "level.h"

Level::Level() {
    block = new Block(0);
    add(new Player(glm::vec3(0, 48.0f, 0)));
}

void Level::update() {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update();
    }
}

void Level::add(Entity *entity) {
    entities.push_back(entity);
}

void Level::render() {
    Shader::BLOCK->enable();
    block->update();
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            block->render(glm::vec3(x * 42.0f, 0.0f, y * 42.0f));
        }
    }
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render();
    }
    Shader::BLOCK->disable();
}

