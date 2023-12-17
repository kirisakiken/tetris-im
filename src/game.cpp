#include "game.hpp"

#include <random>
#include "common.hpp"
#include "models/i_block.hpp"
#include "models/j_block.hpp"
#include "models/l_block.hpp"
#include "models/o_block.hpp"
#include "models/s_block.hpp"
#include "models/t_block.hpp"
#include "models/z_block.hpp"

Game::Game() : sfxManager(SfxManager()), grid(Grid()) {
  grid.Initialize();

  blockPool = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
}

void Game::Update() {
  if (gameState == Game_State_Over) {
    return;
  }

  MoveBlock(0, 1);

  if (BlockCollidesWithAnotherBlock(currentBlock)) {
    currentBlock.Move(0, -1); // move up once
    PutCurrentBlock();
  } else if (BlockCollidesWithBottom(currentBlock)) {
    PutCurrentBlock();
  }
}

void Game::Draw() {
  grid.Draw();
  currentBlock.Draw();

  // -- UI --

  // Draw Score
  DrawText("Score", 345, 15, 38, WHITE);
  // -- background
  DrawRectangleRounded({315, 55, 170, 60}, 0.3, 6, darkBlue);
  // -- text
  const char* scoreArr = strScore.c_str();
  int scoreWidth = MeasureText(scoreArr, 28);
  DrawText(scoreArr, 315 + (170 - scoreWidth) / 2, 72, 28, WHITE);

  // Next Block
  // -- background
  DrawRectangleRounded({315, 420, 170, 180}, 0.3, 6, darkBlue);
  // -- item
  nextBlock.DrawWithOffset(270, 470);

  // Game Over Text
  if (gameState == Game_State_Over) {
    DrawText("Game Over !", 325, 300, 28, WHITE);
    DrawText("Play Again: SPACE", 309, 350, 20, WHITE);
  }
}

void Game::HandleInput() {
  int pressedKey = GetKeyPressed();

  // restart if game is over and user pressed SPACE
  if (gameState == Game_State_Over && pressedKey == KEY_SPACE) {
    Restart();
  }

  switch (pressedKey) {
    case KEY_LEFT: {
      MoveBlock(-1, 0);
      if (BlockCollidesWithAnotherBlock(currentBlock)) {
        MoveBlock(1, 0);
      }
      break;
    }
    case KEY_RIGHT:
      MoveBlock(1, 0);
      if (BlockCollidesWithAnotherBlock(currentBlock)) {
        MoveBlock(-1, 0);
      }
      break;
    case KEY_UP:
      RotateCurrentBlock();
      break;
    case KEY_DOWN:
      MoveBlock(0, 1);
      if (BlockCollidesWithAnotherBlock(currentBlock)) {
        MoveBlock(0, -1);
      }
      break;
    default:
      return;
    }
}

void Game::MoveBlock(int x, int y) {
  if (gameState == Game_State_Over) {
    return;
  }

  currentBlock.Move(x, y);

  if (IsBlockOutsideBounds(currentBlock)) {
    // move block back into bounds
    currentBlock.Move(-x, -y);
  }
}

void Game::RotateCurrentBlock() {
  if (gameState == Game_State_Over) {
    return;
  }

  bool dir = true;
  if (!CanRotate(currentBlock, dir)) {
    // can't rotate if rotation will cause overlap with filled grid
    return;
  }

  currentBlock.Rotate(dir);

  sfxManager.PlayRotateSound();

  Vector2 outsideCell = GetFirstOutsideCell(currentBlock);
  // if (outsideCell.x == -1 && outsideCell.y == -1) {
  if (outsideCell.y < 0) {
    return;
  }

  // move block back into bounds
  if (outsideCell.x < 0) { // overflowing on the left bound
    currentBlock.Move(1, 0);
  } else if (outsideCell.x >= COL_COUNT) { // overflowing on the right bound
    do { // while -> because multiple cell may overflow on the right
      currentBlock.Move(-1, 0);
    } while (IsBlockOutsideBounds(currentBlock));
  }
}

void Game::Restart() {
  grid.Initialize();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
  gameState = Game_State_Running;
}

void Game::UpdateScore(int rowCount) {
  if (rowCount < 1) {
    return;
  }

  int sum = 0;
  switch (rowCount) {
    case 1:
      sum += 97;
      break;
    case 2:
      sum += 204;
      break;
    default:
      sum += 309;
      break;
  }

  sum *= blockCount;
  score += sum;

  strScore = std::to_string(score);

  sfxManager.PlayScoreSound();
}

Block Game::GetRandomBlock()
{
  if (blockPool.empty()) {
    // re-populate blocks
    blockPool = GetAllBlocks();
  }

  // this way, we don't re-create the same block,
  // until all other types of blocks created
  int index = generateRandomInt(0, blockPool.size());
  Block block = blockPool[index];
  blockPool.erase(blockPool.begin() + index);
  return block;
}

std::vector<Block> Game::GetAllBlocks() {
  return {
    IBlock(CELL_SIZE, 0),
    JBlock(CELL_SIZE, 0),
    LBlock(CELL_SIZE, 0),
    OBlock(CELL_SIZE, 0),
    SBlock(CELL_SIZE, 0),
    TBlock(CELL_SIZE, 0),
    ZBlock(CELL_SIZE, 0),
  };
}

/// @brief return Vector2(-1, -1) if the block is in bounds
/// return the cell otherwise 
const Vector2 Game::GetFirstOutsideCell(Block &block) {
  std::vector<Vector2> cells = block.GetCellPositions();
  for (const Vector2& cell : cells) {
    if (IsCellOutsideBounds(cell.x, cell.y)) {
      return cell;
    }
  }

  return Vector2{-1, -1};
}

bool Game::IsBlockOutsideBounds(Block &block) {
  std::vector<Vector2> cells = block.GetCellPositions();
  for (const Vector2& cell : cells) {
    if (IsCellOutsideBounds(cell.x, cell.y)) {
      return true;
    }
  }

  return false;
}

bool Game::IsCellOutsideBounds(int x, int y)
{
  if (x >= 0 && x < COL_COUNT && y < ROW_COUNT) { // excluding y = 0
    return false;
  }

  return true;
}

bool Game::CanRotate(Block &block, bool dir) {
  block.Rotate(dir);
  if (BlockCollidesWithAnotherBlock(block)) {
    block.Rotate(!dir);
    return false;
  }

  block.Rotate(!dir);
  return true;
}

bool Game::BlockCollidesWithBottom(Block& block) {
  std::vector<Vector2> cells = block.GetCellPositions();
  for (const auto& cell : cells) {
    if (cell.y < 0 || cell.x < 0 || cell.x >= COL_COUNT) {
      continue;
    }

    if (cell.y == ROW_COUNT - 1) {
      return true;
    }
  }

  return false;
}

bool Game::BlockCollidesWithAnotherBlock(Block& block) {
  std::vector<Vector2> cells = block.GetCellPositions();
  for (const auto& cell : cells) {
    if (cell.y < 0 || cell.x < 0 || cell.x >= COL_COUNT) {
      continue;
    }

    if (!grid.IsCellEmpty(cell.x, cell.y)) {
      return true;
    }
  }

  return false;
}

void Game::PutCurrentBlock() {
  std::vector<Vector2> cells = currentBlock.GetCellPositions();
  for (const auto& cell : cells) {
    if (cell.y < 0) {
      continue;
    }

    grid.cells[cell.y][cell.x] = currentBlock.colorCode;
  }

  sfxManager.PlayPutSound();
  
  ++blockCount;

  // manage completed rows
  int completeCount = 0;
  for (int row = ROW_COUNT - 1; row >= 0; --row) { // iter all rows
    if (allNotEquals(grid.cells[row], 0)) { // row completed
      // clear row
      for (int col = 0; col < COL_COUNT; ++col) {
        grid.cells[row][col] = 0;
      }

      ++completeCount;
    } else {
      if (completeCount == 0) {
        continue;
      }

      // move row down by 'completedCount'
      for (int col = 0; col < COL_COUNT; ++col) {
        grid.cells[row + completeCount][col] = grid.cells[row][col];
        grid.cells[row][col] = 0;
      }
    }
  }

  UpdateScore(completeCount);

  currentBlock = nextBlock;
  nextBlock = GetRandomBlock();

  // if newly spawned block collides with another block,
  // game should fin
  if (BlockCollidesWithAnotherBlock(currentBlock)) {
    sfxManager.PlayGameOverSound();
    gameState = Game_State_Over;
  }
}
