#include "t_block.hpp"

TBlock::TBlock(int cellSize, int rotationState) : Block(cellSize, rotationState) {
  colorCode = 6;

  cells[0] = {Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}, Vector2{1, 2}};
  cells[1] = {Vector2{0, 1}, Vector2{1, 1}, Vector2{1, 2}, Vector2{2, 1}};
  cells[2] = {Vector2{1, 0}, Vector2{1, 1}, Vector2{1, 2}, Vector2{2, 1}};
  cells[3] = {Vector2{0, 1}, Vector2{1, 0}, Vector2{1, 1}, Vector2{2, 1}};
}
