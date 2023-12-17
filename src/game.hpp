#pragma once

#include "sfx_manager.hpp"
#include "grid.hpp"
#include "models/block.hpp"
#include <vector>
#include <queue>
#include <string>

class Game {
public:
  Game();

  GameState gameState = Game_State_Running;
  int score = 0;
  std::string strScore = "0";

  void Update();
  void Draw();
  void HandleInput();
  void MoveBlock(int x, int y);
  void RotateCurrentBlock();
private:
  SfxManager sfxManager;
  Grid grid;
  std::vector<Block> blockPool;

  int blockCount = 0;
  Block currentBlock;
  Block nextBlock;

  void Restart();
  void UpdateScore(int rowCount);

  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();

  bool IsBlockOutsideBounds(Block& block);
  const Vector2 GetFirstOutsideCell(Block& block);
  bool IsCellOutsideBounds(int x, int y);

  bool CanRotate(Block& block, bool dir);
  bool BlockCollidesWithBottom(Block &block);
  bool BlockCollidesWithAnotherBlock(Block &block);
  void PutCurrentBlock();
};
