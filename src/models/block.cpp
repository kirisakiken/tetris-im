#include "block.hpp"

#include <raymath.h>
#include "../common.hpp"

Block::Block() {}

Block::Block(int cellSize, int rotationState) : cellSize(cellSize), rotationState(rotationState) {
  // spawn the block in the middle
  Move(3, 0);
}

void Block::Draw() {
  std::vector<Vector2> tiles = GetCellPositions();
  for (const auto& tile : tiles) {
    DrawRectangle(tile.x * cellSize + 1, tile.y * cellSize + 1, cellSize - 1, cellSize - 1, cellColorMap[colorCode]);
  }
}

void Block::DrawWithOffset(int x, int y) {
  switch (colorCode) {
    case 3: // I block
      x -= 5;
      y += 38;
      break;
    case 4: // O block
      x -= 18;
      y += 10;
      break;
    default:
      break;
  }
  std::vector<Vector2> cells = GetCellPositions();
  for (const auto& c : cells) {
    DrawRectangle(c.x * CELL_SIZE + x, c.y * CELL_SIZE + y, CELL_SIZE - 1, CELL_SIZE - 1, cellColorMap[colorCode]);
  }
}

void Block::Rotate(bool clockwise)
{
  int dir = clockwise ? 1 : -1;
  rotationState = (rotationState + dir) % 4;
}

void Block::Move(int rows, int columns) {
  offset.x += rows;
  offset.y += columns;
}

/// @brief returns offset applied occupied cell positions
std::vector<Vector2> Block::GetCellPositions() {
  std::vector<Vector2> rawCells = cells[rotationState];
  std::vector<Vector2> result{};
  for (const auto& cell : rawCells) {
    result.push_back(Vector2Add(cell, offset));
  }

  return result;
}
