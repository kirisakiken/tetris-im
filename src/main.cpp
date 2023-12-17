#include <raylib.h>

#include "common.hpp"
#include "game.hpp"

int main() {
  SetTargetFPS(60);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Im!");

  Game game = Game();

  while (!WindowShouldClose()) {
    // -- Logical Ops

    game.HandleInput();
    
    if (shouldTrigger(updateRate)) {
      game.Update();
    }

    // -- Drawing
    BeginDrawing();
    ClearBackground(lightBlue);

    game.Draw();

    EndDrawing();
    // -- EndDrawing
  }

  CloseWindow();
  return 0;
}
