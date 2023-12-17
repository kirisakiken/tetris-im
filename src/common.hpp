#pragma once

#include <raylib.h>
#include <unordered_map>
#include <vector>

enum GameState {
  Game_State_Unknown = 0,
  Game_State_PreStart = 1,
  Game_State_Running = 2,
  Game_State_Paused = 3,
  Game_State_Over = 4,
};

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const int CELL_SIZE;
extern const int ROW_COUNT;
extern const int COL_COUNT;

extern double lastUpdateTime;
extern double updateRate;

extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color lightBlue;
extern const Color darkBlue;

extern std::unordered_map<int, Color> cellColorMap;

/// @brief given interval time and current time,
/// check if an event should be triggered
/// @param interval event trigger rate
/// @note depends on frame rate
extern bool shouldTrigger(double interval);

/// @brief generates and returns a random integer between min-max
/// @param min inclusive 
/// @param max exclusive
extern int generateRandomInt(int min, int max);

/// @brief given x; returns true if all elements of vector not equal
/// to x, false otherwise
extern int allNotEquals(const std::vector<int>& vec, int x);

/// @brief sets elements of vector to zeros
extern void setZeros(std::vector<int>& vec);