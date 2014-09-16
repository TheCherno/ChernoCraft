#include "entity.h"

Entity::Entity() {
    
}

Entity::~Entity() {
    delete model;
}

glm::vec3 Entity::get_position() {
    return position;
}