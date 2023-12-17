#pragma once

#include <vector>
#include <unordered_map>
#include <raylib.h>

#include "common.hpp"

class Grid {
public:
  Grid();

  void Initialize();
  void Draw();

  bool IsCellEmpty(int x, int y);

  std::vector<std::vector<int>> cells{};
private:
  std::unordered_map<int, Color> cellColorMap{
    {0, darkGrey}, // reserved for empty
    {1, green},
    {2, red},
    {3, orange},
    {4, yellow},
    {5, purple},
    {6, cyan},
    {7, blue},
  };
};
