#include "dirt_block.h"

DirtBlock::DirtBlock(unsigned short ID) : Block(ID) {
    texture = Texture::dirt;
}