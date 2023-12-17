#include "o_block.hpp"

OBlock::OBlock(int cellSize, int rotationState) : Block(cellSize, rotationState) {
  colorCode = 4;

  cells[0] = {Vector2{0, 0}, Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}};
  cells[1] = {Vector2{0, 0}, Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}};
  cells[2] = {Vector2{0, 0}, Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}};
  cells[3] = {Vector2{0, 0}, Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}};

  Move(1, 0); // moving extra for proper centering
}
