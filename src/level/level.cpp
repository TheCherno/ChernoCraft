#include "level.h"

Level::Level() {
    add(new Player(glm::vec3(0, 48.0f, 0)));
    unsigned long i = 0;
    blocks = new unsigned short**[WIDTH];
    for (unsigned int x = 0; x < WIDTH; x++) {
        blocks[x] = new unsigned short*[DEPTH];
        for (unsigned int y = 0; y < DEPTH; y++) {
            std::cout << "Created block " << i++ << std::endl;
            blocks[x][y] = new unsigned short[HEIGHT];
        }
    }
    i = 0;
    for (unsigned int z = 0; z < HEIGHT; z++) {
        for (unsigned int y = 0; y < DEPTH; y++) {
            for (unsigned int x = 0; x < WIDTH; x++) {
                std::cout << "Assigned block " << i++ << std::endl;
                blocks[x][y][z] = 1;
            }
        }
    }
    Block::CREATE_ALL();
}

Level::~Level() {
    for (unsigned int y = 0; y < DEPTH; y++) {
        delete [] blocks[y];
    }
    delete [] blocks;
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
    for (int z = 0; z < HEIGHT; z++) {
        for (int y = 0; y < DEPTH; y++) {
            for (int x = 0; x < WIDTH; x++) {
                Block *block = Block::air;
                switch (blocks[x][y][z]) {
                    case 1:
                        block = Block::stone;
                        break;
                    case 2:
                        block = Block::dirt;
                        break;
                }
                block->render(glm::vec3(x * 34.0f, z * 34.0f, y * 34.0f));
            }
        }
    }
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render();
    }
    Shader::BLOCK->disable();
}