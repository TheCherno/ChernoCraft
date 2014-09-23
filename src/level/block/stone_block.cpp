#include "stone_block.h"

StoneBlock::StoneBlock(unsigned short ID) : Block(ID) {
    texture = Texture::stone;
}