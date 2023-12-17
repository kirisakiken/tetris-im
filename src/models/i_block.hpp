#pragma once

#include "block.hpp"

class IBlock : public Block {
public:
  IBlock(int cellSize, int rotationState);
};
