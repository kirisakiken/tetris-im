#pragma once

#include <unordered_map>
#include <vector>
#include <raylib.h>

#include "../common.hpp"

class Block {
public:
  Block();
  Block(int cellSize, int rotationState);

  int colorCode;
  std::unordered_map<int, std::vector<Vector2>> cells{};

  void Draw();
  void DrawWithOffset(int x, int y);
  void Rotate(bool clockwise);
  void Move(int rows, int columns);
  std::vector<Vector2> GetCellPositions();
private:
  int cellSize;
  int rotationState;
  Vector2 offset{Vector2{0, 0}};
};
