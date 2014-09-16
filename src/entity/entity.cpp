#include "entity.h"
#include "../level/level.h"

Entity::Entity() {
    
}

Entity::~Entity() {
    delete model;
}

void Entity::init(Level *level) {
    this->level = level;
}

glm::vec3 Entity::get_position() {
    return position;
}