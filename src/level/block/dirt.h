#pragma once

#include "block.h"

class AirBlock : public Block {
private:
public:
    AirBlock(unsigned int ID);
    void render(glm::vec3 position);
};