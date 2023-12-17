#include "s_block.hpp"

SBlock::SBlock(int cellSize, int rotationState) : Block(cellSize, rotationState) {
  colorCode = 5;

  cells[0] = {Vector2{0, 1}, Vector2{0, 2}, Vector2{1, 0}, Vector2{1, 1}};
  cells[1] = {Vector2{0, 1}, Vector2{1, 1}, Vector2{1, 2}, Vector2{2, 2}};
  cells[2] = {Vector2{1, 1}, Vector2{1, 2}, Vector2{2, 0}, Vector2{2, 1}};
  cells[3] = {Vector2{0, 0}, Vector2{1, 0}, Vector2{1, 1}, Vector2{2, 1}};
}
