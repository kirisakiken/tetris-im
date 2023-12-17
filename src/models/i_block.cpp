#include "i_block.hpp"

IBlock::IBlock(int cellSize, int rotationState) : Block(cellSize, rotationState) {
  colorCode = 3;

  cells[0] = {Vector2{1, 0}, Vector2{1, 1}, Vector2{1, 2}, Vector2{1, 3}};
  cells[1] = {Vector2{0, 2}, Vector2{1, 2}, Vector2{2, 2}, Vector2{3, 2}};
  cells[2] = {Vector2{2, 0}, Vector2{2, 1}, Vector2{2, 2}, Vector2{2, 3}};
  cells[3] = {Vector2{0, 1}, Vector2{1, 1}, Vector2{2, 1}, Vector2{3, 1}};

  Move(0, -2); // moving extra for proper centering
}
