#include "level.h"

unsigned short Level::NULL_BLOCK = 0;

Level::Level() {
    add(new Player(glm::vec3(-45.0f, 48.0f, -45.0f)));
    blocks = new unsigned short**[WIDTH];
    for (unsigned int x = 0; x < WIDTH; x++) {
        blocks[x] = new unsigned short*[DEPTH];
        for (unsigned int y = 0; y < DEPTH; y++) {
            blocks[x][y] = new unsigned short[HEIGHT];
        }
    }
    
    srand((unsigned int) time(NULL));
    for (unsigned int z = 0; z < HEIGHT; z++) {
        for (unsigned int y = 0; y < DEPTH; y++) {
            for (unsigned int x = 0; x < WIDTH; x++) {
                if (z < 1) {
                    blocks[x][y][z] = 2;
                } else if (z < 4 && rand() % 3 == 0) {
                    blocks[x][y][z] = 3;
                } else if (z < 4) {
                    blocks[x][y][z] = 2;
                } else if (z < 5) {
                    blocks[x][y][z] = 3;
                } else if (z < 10 && rand() % 30 == 0) {
                    blocks[x][y][z] = 2;
                } else {
                    blocks[x][y][z] = 1;
                }
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
    Block::DESTROY();
}

void Level::add(Entity *entity) {
    entity->init(this);
    entities.push_back(entity);
}

void Level::update() {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update();
    }
}

void Level::select_block(glm::vec3 block) {
    this->selected_block = block;
}

unsigned short& Level::get_intersecting_block(Entity *entity) {
    glm::vec3 position = -entity->get_position() / Block::SIZE;
    if (position.x < 0 || position.y < 0 || position.z < 0) return NULL_BLOCK;
    if (position.x >= WIDTH || position.y >= HEIGHT || position.z >= DEPTH) return NULL_BLOCK;
    return blocks[(short) position.x][(short) position.z][(short) position.y];
}

unsigned short& Level::get_block(glm::vec3 position) {
    position /= Block::SIZE;
    if (position.x < 0 || position.y < 0 || position.z < 0) return NULL_BLOCK;
    if (position.x >= WIDTH || position.y >= HEIGHT || position.z >= DEPTH) return NULL_BLOCK;
    return blocks[(short) position.x][(short) position.z][(short) position.y];
}

glm::vec3 Level::raycast_block(glm::vec3 position, glm::vec3 &rotation) {
    position = -position;
    glm::vec3 ray_vector = glm::vec3(cos(Math::to_radians(rotation.y - 90.0f)), -tan(Math::to_radians(rotation.x)), sin(Math::to_radians(rotation.y - 90.0f)));
    const float MAX_DISTANCE = 32.0f;
    const float ITERATION = 0.5f;
    float distance = 0.0f;
    while (distance < MAX_DISTANCE) {
        position += ray_vector * ITERATION;
        unsigned short &result = get_block(position);
        if (result != 1 && result != NULL_BLOCK) return glm::vec3((short) (position.x / Block::SIZE), (short) (position.z / Block::SIZE), (short) (position.y / Block::SIZE));
        distance += ITERATION;
    }
    return NULL_COORD;
}

unsigned short& Level::raycast_block_id(glm::vec3 position, glm::vec3 &rotation) {
    position = -position;
    glm::vec3 ray_vector = glm::vec3(cos(Math::to_radians(rotation.y - 90.0f)), -tan(Math::to_radians(rotation.x)), sin(Math::to_radians(rotation.y - 90.0f)));
    const float MAX_DISTANCE = 32.0f;
    const float ITERATION = 0.5f;
    float distance = 0.0f;
    while (distance < MAX_DISTANCE) {
        position += ray_vector * ITERATION;
        unsigned short &result = get_block(position);
        if (result != 1 && result != NULL_BLOCK) return result;
        distance += ITERATION;
    }
    return NULL_BLOCK;
}

unsigned short& Level::raycast_collision(glm::vec3 position, glm::vec3 rotation) {
    position = -position;
    const float MAX_DISTANCE = 2.0f;
    const float ITERATION = 0.5f;
    float distance = 0.0f;
    while (distance < MAX_DISTANCE) {
        position += rotation * ITERATION;
        unsigned short &result = get_block(position);
        if (result != 1 && result != NULL_BLOCK) return result;
        distance += ITERATION;
    }
    return NULL_BLOCK;
}

unsigned short& Level::raycast_pre_block_id(glm::vec3 position, glm::vec3 &rotation) {
    position = -position;
    glm::vec3 ray_vector = glm::vec3(cos(Math::to_radians(rotation.y - 90.0f)), -tan(Math::to_radians(rotation.x)), sin(Math::to_radians(rotation.y - 90.0f)));
    const float MAX_DISTANCE = 32.0f;
    const float ITERATION = 0.5f;
    float distance = 0.0f;
    while (distance < MAX_DISTANCE) {
        position += ray_vector * ITERATION;
        unsigned short &result = get_block(position);
        if (result != 1 && result != NULL_BLOCK) return get_block(position - ray_vector * ITERATION);
        distance += ITERATION;
    }
    return NULL_BLOCK;
}

void Level::render() {
    Shader::BLOCK->enable();
    for (int z = 0; z < HEIGHT; z++) {
        for (int y = 0; y < DEPTH; y++) {
            for (int x = 0; x < WIDTH; x++) {
                Block *block = Block::air;
                switch (blocks[x][y][z]) {
                    case 2:
                        block = Block::stone;
                        break;
                    case 3:
                        block = Block::dirt;
                        break;
                }
                Shader::BLOCK->enable();
//                std::cout << z << ": " << selected_block.z << std::endl;
                if (glm::vec3(x, y, z) == selected_block) {
                    Shader::BLOCK->set_uniform_float1("selected", 1.0f);
                } else {
                    Shader::BLOCK->set_uniform_float1("selected", 0.0f);
                }
                Shader::BLOCK->disable();
                block->render(glm::vec3(x * Block::SIZE + 2.0f, z * Block::SIZE + 2.0f, y * Block::SIZE + 2.0f));
            }
        }
    }
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->render();
    }
    Shader::BLOCK->disable();
}