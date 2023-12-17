#include "common.hpp"

#include <random>

const int WINDOW_WIDTH = 500; // +1 pixel for border
const int WINDOW_HEIGHT = 620; // +1 pixel for border

const int CELL_SIZE = 30;
const int ROW_COUNT = 20;
const int COL_COUNT = 10;

double lastUpdateTime = 0;
double updateRate = 0.2;

const Color darkGrey = {26, 31, 40, 255};
const Color green = {47, 230, 23, 255};
const Color red = {232, 18, 18, 255};
const Color orange = {226, 116, 17, 255};
const Color yellow = {237, 234, 4, 255};
const Color purple = {166, 0, 247, 255};
const Color cyan = {21, 204, 209, 255};
const Color blue = {13, 64, 216, 255};
const Color lightBlue = {59, 85, 162, 255};
const Color darkBlue = {44, 44, 127, 255};

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

bool shouldTrigger(double interval) {
  double curr = GetTime();
  if (curr - lastUpdateTime >= interval) {
    lastUpdateTime = curr;
    return true;
  }

  return false;
}

int generateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(min, max - 1);

    return distribution(generator);
}

int allNotEquals(const std::vector<int>& vec, int x) {
  for (const auto& v : vec) {
    if (v == x) {
      return false;
    }
  }

  return true;
}

void setZeros(std::vector<int>& vec) {
  for (int& v : vec) {
    v -= v;
  }
}
