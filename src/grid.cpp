#include "grid.hpp"

#include "common.hpp"

Grid::Grid() = default;

void Grid::Initialize() {
  cells.clear();
  for (int i = 0; i < ROW_COUNT; ++i) {
    cells.push_back({});
    for (int j = 0; j < COL_COUNT; ++j) {
      cells[i].push_back(0);
    }
  }
}

void Grid::Draw() {
  for (int row = 0; row < ROW_COUNT; ++row) {
    for (int col = 0; col < COL_COUNT; ++col) {
      int cellValue = cells[row][col];
      // using -+1 for grid effect
      DrawRectangle(col * CELL_SIZE + 1, row * CELL_SIZE + 1, CELL_SIZE - 1, CELL_SIZE - 1, cellColorMap[cellValue]);
    }
  }
}

bool Grid::IsCellEmpty(int x, int y) {
  return cells[y][x] == 0;
}
